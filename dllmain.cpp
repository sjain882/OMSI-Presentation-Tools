/* OMSI Presentation Tools
*  C++17, Windows Forms
*  Created by sjain (https://github.com/sjain882)
*  Issues at https://github.com/sjain882/OMSI-Presentation-Tools/issues
*  Suggestions at https://github.com/sjain882/OMSI-Presentation-Tools/pull
*/


/* Imports */
#include <iostream>
#include "MyForm.h"
#include "OMSIPresToolsCLR.h"
#include "lib/AOBScanner.h"
#include "lib/SimpleIni.h"
#include "lib/ConvertUTF.h"
#include <thread>
#include <iostream>
#include <fstream>


/* Pragma lib includes */
#pragma comment(lib,"user32.lib")


/* Definitions for TProgMan.NewSituationand game version checks */

#define OMSI_22032_HOOK_RELADDR 0x002E62B8
#define OMSI_23004_HOOK_RELADDR 0x002E6392
#define OMSI_TCAMERA_FOV_OFFSET 0x38
// Version scan: starts at 2.2.032, ends at 2.3.004, total range 312 bytes
#define OMSI_VERSIONCHECK_START_ADDR 0x0072DFE0
#define OMSI_VERSIONCHECK_END_ADDR 0x0072E12F
#define OMSI_VERSIONCHECK_START_RELADDR 0x0032DFE0
#define OMSI_VERSIONCHECK_END_RELADDR 0x0032E12F
#define OMSI_22032_ANSI "32 00 2E 00 32 00 2E 00 30 00 33 00 32"
#define OMSI_23004_ANSI "32 00 2E 00 33 00 2E 00 30 00 30 00 34"



/* Unused definitions, but useful to keep here for reference
OMSI_22032_HOOK_ADDR 0x006E62B8
OMSI_23004_HOOK_ADDR 0x006E6392
OMSI_NEWSITUATION_IDA_SIG \x55\x8B\xEC\x51\xB9\x56\x00\x00\x00
OMSI_22032_ANSI_HEX "\x32\x00\x2E\x00\x32\x00\x2E\x00\x30\x00\x33\x00\x32"
OMSI_23004_ANSI_HEX "\x32\x00\x2E\x00\x33\x00\x2E\x00\x30\x00\x30\x00\x34"
OMSI_VERSION_ANSI_MASK "xxxxxxxxxxxxx" */



/* Export standard OMSI functions so OMSI can call them.
*  This prevents the linker from obfustucating function names.
*  Also via Project Properties > All Configurations > Linker
*  > Input > type "OMSIDLL.def" for external export list. */

extern "C" __declspec(dllexport)void __stdcall PluginStart(void* aOwner);
extern "C" __declspec(dllexport)void __stdcall PluginFinalize();



/* Foward declarations */

DWORD WINAPI MainThread(LPVOID param);
void InitForm();
int InitConfigValues();
int GetGameVersion();
bool ScanForGameVersion(const char* searchString);
bool CalculateFovOffset();
bool Hook(void* toHook, void* localFunc, int length);



/* Instantiate variables */

// Internal
DWORD moduleBaseAddress;
DWORD oldProtection;
bool isF4FovEnabled;
bool mapJustLoaded;
char* f4FovPtrChar;
float newf4FovValue;
float* f4FovPtr;

// Hooking
DWORD hookAddress;
DWORD jumpBackAddress;
DWORD versionSearchStart;
DWORD* f4Addy;
bool hookStatus;
char* versionSearchStartChar;

// .ini File
CSimpleIniA ini;
SI_Error rc;

// Console output (disabled)
FILE* fDummy;
HANDLE mhStdOutput;



/* Constants */

const float DEFAULT_F4_FOV_VALUE = (float)45.0;

const int FLOAT_BYTE_LENGTH = 4;

const int GUI_F4_FOV_INIT_VAL = 450;

const char* MSG_GAME_VERSION_FAILED = "Falied to determine game version.\nQuit and restart OMSI.";

const char* MSG_DEFAULT_TITLE = "OMSI Presentation Tools";

const char* MSG_INI_SAVE_FAILED = "Failed to save to the ini file.";

const char* INI_FIELD_NAME = "Settings";

const char* INI_FIRST_LAUNCH_ENTRY_NAME = "isFirstLaunch";

const char* INI_FIRST_LAUNCH_FALSE_VAL = "0";

const char* INI_FIRST_LAUNCH_TRUE_VAL = "1";

const char* MSG_INI_LOAD_FAILED = "Failed to load from the ini file.";

const char* MSG_FIRST_LAUNCH_TITLE = "First Launch";

const char* INI_FILE_RELATIVE_PATH = ".\\plugins\\OMSIPresentationTools.ini";

const std::string LOG_FILE_MAP_CAM_LOADED = "Information: Map camera loaded";

const std::string LOG_FILE_CLOSING_MAP = "Information: Closing actual map...";

const std::string LOG_FILE_FILENAME = "logfile.txt";

const char* MSG_FIRST_LAUNCH = "Thank you for using OMSI Presentation Tools!\n\n"
"If you have any games open that have anti - cheats, please close them immediately!\n\n"
"See the GitHub Readme or Steam guide for more info.\n\n"
"You will not be reminded next time!\n\n"
"If you can't see OMSI Presentation Tools, it may be behind OMSI 2, find it in the ALT+TAB menu.";



/* DLL Entrypoint - OMSI will use LoadLibrary to attach .dll plugins
 * so we can take advantage of that, skipping PluginStart() */

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        // Start the MainThread() main function in a new thread
        CreateThread(0, 0, MainThread, hModule, 0, 0);

        // Detach it from the GUI thread (this does not terminate the thread)
        CloseHandle(0);

        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}



/* Detoured function - this is where our hooked code will jump to.
*
*  Line 1: The instruction we overwrote with the jmp instruction to this detour.
*
*  Line 2: Move the memory address of the Free Map Camera (F4)'s TCamera struct
*          (a DWORD pointer stored in the edx register at this point) into f4Addy.
*
*  Line 3: The instruction right after the patched instruction is repeated here
*          as the jmp instruction to this detour had to overwrite it due to it's byte length.
*
*  Line 4: Jump back to where we detoured / trampoline hooked from to continue execution. 
*
*  __declspec(naked): Do not add function prologue or epilogue when compiling.
*  This preserves the register states from the function we are hooking. */

void __declspec(naked) localFunc() {

    __asm {
        mov edx, [esi + 0x14]
        mov f4Addy, edx
        mov[eax], edx
        jmp[jumpBackAddress]
    }

}



/* Main function of this program, called when this .dll is attached to a process */

DWORD WINAPI MainThread(LPVOID param) {

    f4FovActValue = DEFAULT_F4_FOV_VALUE;
    f4FovHoldValue = DEFAULT_F4_FOV_VALUE;
    f4FovUI = GUI_F4_FOV_INIT_VAL;
    hasFoundAddress = false;
    isF4FovEnabled = false;
    isMapCurrentlyLoaded = false;
    isProcessActive = true;
    justEnabledFOVApplication = false;
    justScrolled = false;
    mapJustLoaded = false;
    std::ifstream inputFileStream(LOG_FILE_FILENAME.c_str());
    std::streamoff logFileCursorPos = 0;
    std::string logFileCurrentLine;


    /* Console output (disabled) */

    // Initialise the console
    AllocConsole();

    // Set the stdout handle
    mhStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    // Re-assign handles to this window
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

    // Set the console window title
    SetConsoleTitleA("OMSI Presentation Tools Console Debug");

    // Start the GUI in a new thread
    std::thread initFormThread(InitForm);

    // Detach this thread from the main OMSI process
    initFormThread.detach();

    // Get settings from the .ini file
    int configStatus = InitConfigValues();


    /* If the .ini file reports this is the first use of
     * this tool, or if the ini file could not be read... */
    if (configStatus > 1) {

        // ...display the first launch message and set it to "Always on top" so it can't get hidden behind OMSI
        MessageBoxA(0, MSG_FIRST_LAUNCH, MSG_FIRST_LAUNCH_TITLE, MB_OK | MB_ICONWARNING | MB_TOPMOST);

        // Save the fact that the first launch has passed to the .ini
        rc = ini.SetValue(INI_FIELD_NAME, INI_FIRST_LAUNCH_ENTRY_NAME, INI_FIRST_LAUNCH_FALSE_VAL);

        // If there was an error saving to the file, display an error message, otherwise write to the file
        if (rc < 0) {
            MessageBoxA(0, MSG_INI_SAVE_FAILED, MSG_DEFAULT_TITLE, MB_OK | MB_ICONERROR);
        }
        else {
            ini.SaveFile(INI_FILE_RELATIVE_PATH);
        }

    }


    /* Get the module base address of OMSI's process internally.
    *  By passing NULL here, it defaults to the main Omsi module.
    *  This stops it from breaking when OMSI's filename isn't Omsi.exe.
    *  Important for users using the "Tram" 2.2.032 patch named as Omsi_older.exe */
    moduleBaseAddress = (DWORD)GetModuleHandleA(NULL);


    // Get the game version
    int gameVersionStatus = GetGameVersion();


    /* Determine which memory address to hook based on this
    *  Although most users will have plenty of free memory for OMSI
    *  to load into it's preferred base address of 0x00400000, this might not
    *  always be the case so we must base this off the module base address */
    switch (gameVersionStatus)
    {

        // Failed to get the game version
    case 0:
        MessageBoxA(0, MSG_GAME_VERSION_FAILED, MSG_DEFAULT_TITLE, MB_OK | MB_ICONERROR);
        break;

        // Detected OMSI 2 v2.2.032 successfully
    case 1:
        hookAddress = (DWORD)moduleBaseAddress + (DWORD)OMSI_22032_HOOK_RELADDR;
        break;

        // Detected OMSI 2 v2.3.004 successfully
    case 2:
        hookAddress = (DWORD)moduleBaseAddress + (DWORD)OMSI_23004_HOOK_RELADDR;
        break;

    default:
        break;
    }


    // If the game version check was successful, continue with the hook
    if (gameVersionStatus > 0) {


        /* The length of the jmp instruction is 5.
        *  Thus, we must overwite the instructions at 0x006E6392 and 0x006E6395 (v2.3.004 reference) */
        int hookLength = 5;

        /* Where we jump back to from the end of the target function to detour to:
        *  the address of the original instruction we hooked at + the length of the jmp instruction we will write there. */
        jumpBackAddress = hookAddress + hookLength;

        // Perform the hook
        hookStatus = Hook((void*)hookAddress, localFunc, hookLength);

        // Not terminating the thread here as this destroys the code to be jumped to
        // FreeLibraryAndExitThread((HMODULE)param, 0);

    }


    // If a map is currently loaded, enter the main program loop
    while (isProcessActive) {

        // OMSI 2 Logfile watcher - to determine if a map is currently loaded

        inputFileStream.seekg(logFileCursorPos);
        while (getline(inputFileStream, logFileCurrentLine))
        {
            // "Map camera loaded" event
            if (logFileCurrentLine.find(LOG_FILE_MAP_CAM_LOADED) != std::string::npos) {
                isMapCurrentlyLoaded = true;
                mapJustLoaded = true;
            }

            // "Map closing" event
            if (logFileCurrentLine.find(LOG_FILE_CLOSING_MAP) != std::string::npos) {
                isMapCurrentlyLoaded = false;
            }

            if (inputFileStream.tellg() == -1) logFileCursorPos = logFileCursorPos + logFileCurrentLine.size();
            else logFileCursorPos = inputFileStream.tellg();
        }
        inputFileStream.clear();


        /* If a map just loaded, calculate a pointer to the FoV of the
        *  F4 camera based off the address we grabbed in the f4Addy variable */
        if (mapJustLoaded && isMapCurrentlyLoaded) {
            mapJustLoaded = false;
            CalculateFovOffset();
        }


        // If a map is currently loaded, write to the F4 Camera's FOV value
        if (isMapCurrentlyLoaded) {

            // If FOV application is currently enabled in the GUI
            if (isF4FovEnabled) {

                newf4FovValue = (float)f4FovActValue;
                *(float*)f4FovPtr = newf4FovValue;

                // *(float*)f4FovPtr: cast the f4FovPtr to a float pointer (4 bytes) then dereference it
            }

            // If FOV application is currently disabled in the GUI
            else {
                *(float*)f4FovPtr = DEFAULT_F4_FOV_VALUE;
            }

        }

    }

}



// Initialises the main GUI

void InitForm() {

    System::Windows::Forms::Application::EnableVisualStyles();
    System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
    OMSIPresToolsCLR::MyForm form;  // Initialise the form object
    form.MaximizeBox = false;       // Prevent maximising
    form.AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
    System::Windows::Forms::Application::Run(% form);   // Run the form

}



/* Gets the initialisation values from the .ini file.
*  Returns a non-zero value indicating the status of the ini values. */

int InitConfigValues() {

    int isFirstLaunchOPL;
    int funcStatus = 0;
    ini.SetUnicode();
    rc = ini.LoadFile(INI_FILE_RELATIVE_PATH);

    // If the .ini file was loaded sucessfully
    if (rc >= 0) {

        // Get the isFirstLaunch as a char and convert it to an int
        isFirstLaunchOPL = atoi(ini.GetValue(INI_FIELD_NAME, INI_FIRST_LAUNCH_ENTRY_NAME));

        switch (isFirstLaunchOPL) {

            // Not the first launch
        case 0:
            funcStatus = 1;
            break;

            // Confirmed to be the first launch
        case 1:
            funcStatus = 2;
            break;

        default:
            break;

        }
    }
    else {

        // If the .ini file could not be loaded, display an error message
        MessageBoxA(0, MSG_INI_LOAD_FAILED, MSG_DEFAULT_TITLE, MB_OK | MB_ICONERROR);

        // This condition still has a unique return value above 0
        funcStatus = 3;

    }

    return funcStatus;
}



/* Determines the game version by calling a scanner.
*  Returns 0 if unsuccesful, 1 for OMSI 2 v2.2.032 and 2 for OMSI 2 v2.3.004. */

int GetGameVersion() {

    int result = 0;
    bool scanStatus23032 = false;
    bool scanStatus23004 = false;

    // If we already determined game version v2.2.032, skip scanning for v2.3.004
    if (ScanForGameVersion(OMSI_22032_ANSI)) {

        result = 1;

    }
    else {

        // Only scan for v2.3.004 if we haven't determined v2.3.032 already
        if (ScanForGameVersion(OMSI_23004_ANSI)) {
            result = 2;
        }
    }

    return result;

}



/* Scans for char* searchString in a specific region of memory with an AOBScanner instance.
*  The region of memory used here contains OMSI's program version indication
*  strings that are written to the top of map timetable files (.ttp, .ttl, .ttr) 
*  Returns true if successful, false if unsuccessful. */

bool ScanForGameVersion(const char* searchString)
{

    bool scanSuccess = false;
    uintptr_t scanStart = (uintptr_t)moduleBaseAddress + (uintptr_t)OMSI_VERSIONCHECK_START_RELADDR;
    uintptr_t scanEnd = (uintptr_t)moduleBaseAddress + (uintptr_t)OMSI_VERSIONCHECK_END_RELADDR;
    BYTE* foundAddress;

    // External Array of Byte memory scanner by rev_eng_e
    AOBScanner scanner(scanStart, scanEnd);
    foundAddress = scanner.Scan(searchString);

    if (foundAddress)
    {
        scanSuccess = true;
    }

    return scanSuccess;

}



/* Calculates the offset of the 4 byte FoV float from the base address
*  of the TCamera struct and stores it in the globally defined f4FovPtr. */

bool CalculateFovOffset() {

    // Cast the pointer to a char pointer to allow for single byte pointer arithmetic
    (char*)f4FovPtrChar = (char*)f4Addy + OMSI_TCAMERA_FOV_OFFSET;

    // Cast it back to a float pointer (4 bytes)
    f4FovPtr = (float*)f4FovPtrChar;

    // Set memory permissions on the FoV value
    VirtualProtect((void*)f4FovPtr, FLOAT_BYTE_LENGTH, PAGE_EXECUTE_READWRITE, &oldProtection);

    return true;

}



/* Mechanism to detour / trampoline hook into OMSI 2.
*  void* toHook: the memory address (of an instruction) to hook at.
*  void* localFunc: the memory address of a our function to jump to.
*  int length: the length of the instruction to be written to for the hook.
*  Constructs a jmp instruction to localFunc and writes it to toHook. */

bool Hook(void* toHook, void* localFunc, int length) {

    // Stop if there isn't enough space for a jmp to be written
    if (length < 5) return false;

    // Set memory permissions
    DWORD oldProtection;
    VirtualProtect(toHook, length, PAGE_EXECUTE_READWRITE, &oldProtection);

    // Populate the memory with nop for a clean start, to avoid conflicts if anything is left over
    memset(toHook, 0x90, length);

    // Offset from where we write jmp to the destination, including the size of the jmp (5)
    DWORD relativeAddress = ((DWORD)localFunc - (DWORD)toHook) - 5;

    // Convert toHook to byte pointer and dereference
    // 0xE9: first opcode of a jmp
    *(BYTE*)toHook = 0xE9;

    // Convert to DWORD pointer and offset by 1 to avoid overwriting 0xE9
    *(DWORD*)((DWORD)toHook + 1) = relativeAddress;

    // Restore the old memory permissions
    DWORD tmp;
    VirtualProtect(toHook, length, oldProtection, &tmp);

    return true;

}



// Called by the UI, inverts the enabled status of the FoV application.

void ToggleF4FovEnabled() {
    isF4FovEnabled = !isF4FovEnabled;
}



/* --- OMSI Functions Start --- */


// Called on OMSI startup (just before main menu appears)

void __stdcall PluginStart(void* aOwner)
{
}



// Called on OMSI quit (when the user clicks "Yes" on the confirmation)

void __stdcall PluginFinalize()
{
    // Stop the main program loop
    isProcessActive = false;

    // Restore original memory permissions on the F4 FoV value
    DWORD tmp;
    VirtualProtect((void*)f4FovPtr, FLOAT_BYTE_LENGTH, oldProtection, &tmp);
}


/* --- OMSI Functions End --- */
