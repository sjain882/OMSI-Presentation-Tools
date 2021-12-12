/* OMSI Presentation Tools
*  C++17, Windows Forms
*  Created by sjain (https://github.com/sjain882)
*  Issues at https://github.com/sjain882/OMSI-Presentation-Tools/issues
*  Suggestions at https://github.com/sjain882/OMSI-Presentation-Tools/pulls
*/

// Imports

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


/* Pragma lib includes */

#pragma comment(lib,"user32.lib")



/* Definitions for TProgMan.NewSituation and game version checks */

#define OMSI_22032_HOOK_ADDR 0x006E62B8
#define OMSI_23004_HOOK_ADDR 0x006E6392
#define OMSI_22032_HOOK_RELADDR 0x002E62B8
#define OMSI_23004_HOOK_RELADDR 0x002E6392
#define OMSI_NEWSITUATION_SIG \x55\x8B\xEC\x51\xB9\x56\x00\x00\x00
// Starts at 2.2.032, ends at 2.3.004, total range 312 bytes
#define OMSI_VERSIONCHECK_START_ADDR 0x0072DFE0
#define OMSI_VERSIONCHECK_END_ADDR 0x0072E12F
#define OMSI_VERSIONCHECK_START_RELADDR 0x0032DFE0
#define OMSI_VERSIONCHECK_END_RELADDR 0x0032E12F
#define OMSI_22032_ANSI "32 00 2E 00 32 00 2E 00 30 00 33 00 32"
#define OMSI_23004_ANSI "32 00 2E 00 33 00 2E 00 30 00 30 00 34"
#define ANSI_MASK "xxxxxxxxxxxxx"
#define OMSI_22032_ANSI_HEX "\x32\x00\x2E\x00\x32\x00\x2E\x00\x30\x00\x33\x00\x32"
#define OMSI_23004_ANSI_HEX "\x32\x00\x2E\x00\x33\x00\x2E\x00\x30\x00\x30\x00\x34"



using namespace System;
using namespace System::Windows::Forms;



/* Export standard OMSI functions so OMSI can call them.
*  This prevents the linker from obfustucating function names.
*  Also via Project Properties > All Configurations > Linker
*  > Input > type "OMSIDLL.def" for external export list.
*/

extern "C" __declspec(dllexport)void __stdcall PluginStart(void* aOwner);
extern "C" __declspec(dllexport)void __stdcall PluginFinalize();



/* Foward declarations */

DWORD WINAPI MainThread(LPVOID param);
bool Hook(void* toHook, void* localFunc, int length);
int GetGameVersion();
void InitialiseForm();
bool ScanForGameVersion(const char* searchString);



/* Instantiate variables */

// Internal
float* f4fovptr;
DWORD procId;
char* moduleBaseChar;
bool isF4FovEnabled;
uintptr_t f4FovAddress;
float newf4FovValue;
bool isProcessActive;


// Hooking

DWORD *f4Addy;
float* f4FovPtr;
DWORD hookAddress;
DWORD jumpBackAddress;
DWORD moduleBaseAddress;
bool hookStatus;
DWORD versionSearchStart;
char* versionSearchStartChar;


// SHIT

FILE* fDummy;
HANDLE mhStdOutput;


/* DLL Entrypoint - OMSI will use LoadLibrary to attach
 * .dll plugins so we can take advantageo of that, skipping PluginStart() 
 * avoiding any linkage to OMSI's plugin system (potential instability) */

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, MainThread, hModule, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}



/* Detoured function */

void __declspec(naked) localFunc() {

    __asm {
        mov edx, [esi + 0x14]
        mov f4Addy, edx
        mov [eax], edx
        jmp [jumpBackAddress]
    }

}



DWORD WINAPI MainThread(LPVOID param) {

    isProcessActive = true;
    isF4FovEnabled = false;
    f4FovUI = 450;
    f4FovActValue = (float)45.0;
    f4FovHoldValue = (float)45.0;
    justEnabledFOVApplication = false;
    justScrolled = false;
    hasFoundAddress = false;
    int floatLength = 4;

    AllocConsole();
    mhStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    SetConsoleTitleA("OMSI Presentation Tools (Release, x86) - PreAlpha DO NOT REDISTRIBUTE");

    std::thread initFormThread(InitialiseForm);
    initFormThread.detach();


    // Get OMSI's module base address internally
    moduleBaseAddress = (DWORD)GetModuleHandleA(NULL);

    // Get the game version internally
    int gameVersionStatus = GetGameVersion();

    // Determine where to hook based off this
    switch (gameVersionStatus)
    {

        // Failed
        case 0:
            MessageBoxA(0, "Falied to determine game version.\nQuit and restart OMSI.", "OMSI Presentation Tools", MB_OK | MB_ICONERROR);
            // TODO: Disable controls permanently
            break;

        // OMSI 2 v2.2.032
        case 1:
            hookAddress = (DWORD)moduleBaseAddress + (DWORD)OMSI_22032_HOOK_RELADDR;
            break;

        // OMSI 2 v2.3.004
        case 2:
            hookAddress = (DWORD)moduleBaseAddress + (DWORD)OMSI_23004_HOOK_RELADDR;
            break;

        default:
            break;
    }


    if (gameVersionStatus > 0) {

        printf("GVS\n");

        // We are overwriting 006E6392 and 006E6395
        int hookLength = 5;

        /* Where we jump back to at the end of the function we detour to.
        *  This is the address of the original function we hooked at, plus the length of the jmp instruction. */
        jumpBackAddress = hookAddress + hookLength;

        // Perform the hook
        hookStatus = Hook((void*)hookAddress, localFunc, hookLength);

        while (true) {
            std::cout << f4Addy;
        }

        // Not exiting here as this destroys the code to be jumped to
        // FreeLibraryAndExitThread((HMODULE)param, 0);

    }


    if (false) {
        std::cout << "HookStatus" << std::endl;
        // FOV is 52 bytes from the base of the TCamera struct
        f4FovPtr = (float*)f4Addy;
        f4FovPtr = f4FovPtr + 52;
        //f4FovAddress = (uintptr_t)f4Addy + 52;
        std::cout << f4FovAddress;

        // Set memory permissions
        DWORD oldProtection;
        VirtualProtect((void*)f4FovAddress, floatLength, PAGE_EXECUTE_READWRITE, &oldProtection);

    }




    while (false) {
        std::cout << "While" << std::endl;

        if (isF4FovEnabled) {
            std::cout << "isF4FovEnabled" << std::endl;
            newf4FovValue = (float)f4FovActValue;
            *(float*)f4FovAddress = newf4FovValue;
        }
        else if (!isF4FovEnabled) {
            std::cout << "!isF4FovEnabled" << std::endl;
            float defaultF4FovValue = (float)45.0;
            *(float*)f4FovAddress = defaultF4FovValue;
        }

    }



    // Restore the old memory permissions
    //DWORD tmp;
    //VirtualProtect((void*)f4FovAddress, floatLength, oldProtection, &tmp);

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

void toggleF4FovEnabled() {
    isF4FovEnabled = !isF4FovEnabled;
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
        printf("Found: %p\n", foundAddress);
        scanSuccess = true;
    }
    else
    {
        printf("Did not find\n");
    }

    return scanSuccess;

}





void InitialiseForm() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    OMSIPresToolsCLR::MyForm form;
    form.MaximizeBox = false;
    Application::Run(% form);

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
}


/* --- OMSI Functions End --- */
