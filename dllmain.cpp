/* OMSI Presentation Tools
*  C++17, Windows Forms
*  Created by sjain (https://github.com/sjain882)
*  Issues at https://github.com/sjain882/OMSI-Presentation-Tools/issues
*  Suggestions at https://github.com/sjain882/OMSI-Presentation-Tools/pulls
*/


/* Imports */
#include <iostream>
#include <codecvt>
#include <vector>
#include <math.h>
#include <intrin.h>
#include <windows.h>
#include <TlHelp32.h>
#include <memoryapi.h>
#include <winuser.h>
#include "MyForm.h"
#include "OMSIPresToolsCLR.h"
#include "lib/AOBScanner.h"
#include "lib/SimpleIni.h"
#include "lib/ConvertUTF.h"
#include <thread>
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>


/* Pragma lib includes */
#pragma comment(lib,"user32.lib")


/* Definitions for TProgMan.NewSituationand game version checks */
#define OMSI_22032_HOOK_RELADDR 0x002E62B8
#define OMSI_23004_HOOK_RELADDR 0x002E6392
// Starts at 2.2.032, ends at 2.3.004, total range 312 bytes
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
float* f4FovPtr;
char* f4FovPtrChar;
DWORD procId;
char* moduleBaseChar;
bool isF4FovEnabled;
uintptr_t f4FovAddress;
float newf4FovValue;
bool isProcessActive;
int isFirstLaunchOPL;
CSimpleIniA ini;
SI_Error rc;
int floatLength;
DWORD oldProtection;
bool mapJustLoaded;
bool isFovWritingEnabled;
bool addy;


// Hooking

DWORD *f4Addy;
DWORD hookAddress;
DWORD jumpBackAddress;
DWORD moduleBaseAddress;
bool hookStatus;
DWORD versionSearchStart;
char* versionSearchStartChar;


// SHIT

FILE* fDummy;
HANDLE mhStdOutput;



/* DLL Entrypoint - OMSI will use LoadLibrary to attach .dll plugins
 * so we can take advantage of that, skipping PluginStart() */

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        // Start the MainThread() main function in a new thread
        CreateThread(0, 0, MainThread, hModule, 0, 0);

        // Detach it from other threads (this does not terminate the thread)
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
*  Line 4: Jump back to where we detoured / trampoline hooked from to continue execution. */

void __declspec(naked) localFunc() {

    __asm {
        mov edx, [esi + 0x14]
        mov f4Addy, edx
        mov [eax], edx
        jmp [jumpBackAddress]
    }

}



/* Main function of this code, called when this .dll is attached to a process */

DWORD WINAPI MainThread(LPVOID param) {

    isProcessActive = true;
    isF4FovEnabled = false;
    f4FovUI = 450;
    f4FovActValue = (float)45.0;
    f4FovHoldValue = (float)45.0;
    justEnabledFOVApplication = false;
    justScrolled = false;
    hasFoundAddress = false;
    isMapCurrentlyLoaded = false;
    mapJustLoaded = false;
    isFovWritingEnabled = false;
    float defaultF4FovValue = (float)45.0;
    addy = false;
    floatLength = 4;
    std::string logFileStatus_MapCamLoaded = "Information: Map camera loaded";
    std::string logFileStatus_ClosingMap = "Information: Closing actual map...";
    std::string log;
    std::string logFile = "logfile.txt";
    std::streamoff p = 0;
    std::ifstream ifs(logFile.c_str());

    AllocConsole();
    mhStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
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
        MessageBoxA(0, "Thank you for using OMSI Presentation Tools!\n\nIf you have any games open that have anti-cheats, please close them immediately!\n\nSee the GitHub Readme or Steam guide for more info.\n\nYou will not be reminded next time!\n\nIf you can't see OMSI Presentation Tools, it may be behind OMSI 2, find it in the ALT+TAB menu.", "First Launch", MB_OK | MB_ICONWARNING | MB_TOPMOST);

        // Save the fact that the first launch has passed to the .ini
        rc = ini.SetValue("Settings", "isFirstLaunch", "0");

        // If there was an error writing to the file, display an error message, otherwise write to the file
        if (rc < 0) {
            MessageBoxA(0, "Failed to save to ini file.", "OMSI Presentation Tools", MB_OK | MB_ICONERROR);      
        }
        else {
            ini.SaveFile(".\\plugins\\OMSIPresentationTools.ini");
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
            MessageBoxA(0, "Falied to determine game version.\nQuit and restart OMSI.", "OMSI Presentation Tools", MB_OK | MB_ICONERROR);
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

        // Not exiting here as this destroys the code to be jumped to
        // FreeLibraryAndExitThread((HMODULE)param, 0);

    }



    // If a map is currently loaded, enter the main program loop

    while (isProcessActive) {

        // OMSI 2 Logfile watcher - to determine if a map is currently loaded

        ifs.seekg(p);
        while (getline(ifs, log))
        {
            // "Map camera loaded" event
            if (log.find(logFileStatus_MapCamLoaded) != std::string::npos) {
                isMapCurrentlyLoaded = true;
                mapJustLoaded = true;
            }

            // "Map closing" event
            if (log.find(logFileStatus_ClosingMap) != std::string::npos) {
                isMapCurrentlyLoaded = false;
            }

            if (ifs.tellg() == -1) p = p + log.size();
            else p = ifs.tellg();
        }
        ifs.clear();
    

        /* If a map just loaded, calculate a pointer to the FoV of the
        *  F4 camera based off the address we grabbed in the f4Addy variable */
        if (mapJustLoaded && isMapCurrentlyLoaded) {
            mapJustLoaded = false;
            if (CalculateFovOffset()) {
                isFovWritingEnabled = true;
            }
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
                *(float*)f4FovPtr = defaultF4FovValue;
            }

        }

    }

}



void InitForm() {

    System::Windows::Forms::Application::EnableVisualStyles();
    System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
    OMSIPresToolsCLR::MyForm form;  // Initialise the form
    form.MaximizeBox = false;   // Prevent maximising
    form.AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
    System::Windows::Forms::Application::Run(% form);   // Run the form

}



int InitConfigValues() {

    int funcStatus = 0;
    ini.SetUnicode();
    rc = ini.LoadFile(".\\plugins\\OMSIPresentationTools.ini");

    if (rc >= 0) {

        isFirstLaunchOPL = atoi(ini.GetValue("Settings", "isFirstLaunch"));

        switch (isFirstLaunchOPL) {

        case 0:
            funcStatus = 1;
            break;

        case 1:
            funcStatus = 2;
            break;

        default:
            break;

        }
    }
    else {
        MessageBoxA(0, "Failed to read from ini file.", "OMSI Presentation Tools", MB_OK | MB_ICONERROR);
        funcStatus = 3;
    }

    return funcStatus;
}


int GetGameVersion() {

    int result = 0;
    bool scanStatus23032 = false;
    bool scanStatus23004 = false;

    scanStatus23032 = ScanForGameVersion(OMSI_22032_ANSI);

    if (scanStatus23032) {
        result = 1;
    }
    else {
        scanStatus23004 = ScanForGameVersion(OMSI_23004_ANSI);
        if (scanStatus23004) {
            result = 2;
        }
    }

    return result;

}




bool CalculateFovOffset() {

    (char*)f4FovPtrChar = (char*)f4Addy + 0x38;

    f4FovPtr = (float*)f4FovPtrChar;

    // Set memory permissions
    VirtualProtect((void*)f4FovPtr, floatLength, PAGE_EXECUTE_READWRITE, &oldProtection);

    addy = true;

    return true;

}



bool Hook(void* toHook, void* localFunc, int length) {

    // Stop if there isn't enough space for a jmp to be written
    if (length < 5) return false;

    // Set memory permissions
    DWORD oldProtection;
    VirtualProtect(toHook, length, PAGE_EXECUTE_READWRITE, &oldProtection);

    // Populate the memory with nop for a clean start
    memset(toHook, 0x90, length);

    // Offset from where we write jmp to destination, including the size of the jmp (5)
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


// UI

void ToggleF4FovEnabled() {
    isF4FovEnabled = !isF4FovEnabled;
}





bool ScanForGameVersion(const char* searchString)
{

    bool scanSuccess = false;
    uintptr_t scanStart = (uintptr_t)moduleBaseAddress + (uintptr_t)OMSI_VERSIONCHECK_START_RELADDR;
    uintptr_t scanEnd = (uintptr_t)moduleBaseAddress + (uintptr_t)OMSI_VERSIONCHECK_END_RELADDR;
    BYTE* foundAddress;
    AOBScanner scanner(scanStart, scanEnd);
    foundAddress = scanner.Scan(searchString);

    if (foundAddress)
    {
        scanSuccess = true;
    }

    return scanSuccess;

}




/* --- OMSI Functions Start --- */


// Called on OMSI startup (just before main menu appears)

void __stdcall PluginStart(void* aOwner)
{    
}


// Called on OMSI quit (when the user clicks "Yes" on the confirmation)

void __stdcall PluginFinalize()
{
    isProcessActive = false;
    DWORD tmp;
    VirtualProtect((void*)f4FovAddress, floatLength, oldProtection, &tmp);
}


/* --- OMSI Functions End --- */
