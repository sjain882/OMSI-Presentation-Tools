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
#include "lib/SimpleIni.h"
#include "lib/ConvertUTF.h"
#include <thread>
#include "lib/ntdll.h"


/* Pragma lib includes */

#pragma comment(lib,"user32.lib")



/* Definitions for TProgMan.NewSituation and game version checks */

#define OMSI_22032_HOOK_ADDR 0x006E6279
#define OMSI_23004_HOOK_ADDR 0x006E6392
#define OMSI_22032_HOOK_RELADDR 0x002E6279
#define OMSI_23004_HOOK_RELADDR 0x002E6392
#define OMSI_NEWSITUATION_SIG \x55\x8B\xEC\x51\xB9\x56\x00\x00\x00
// Starts at 2.2.032, ends at 2.3.004, total range 312 bytes
#define OMSI_VERSIONCHECK_START_ADDR 0x0072DFE0
#define OMSI_VERSIONCHECK_END_ADDR 0x0072E118
#define OMSI_VERSIONCHECK_START_RELADDR 0x0032DFE0
#define OMSI_VERSIONCHECK_END_RELADDR 0x0032E118
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
bool InternalScanForGameVersion(char* pattern, char* mask, char* begin, intptr_t size);
void InitialiseForm();



/* Instantiate variables */

// Internal
float* f4fovptr;
DWORD procId;
HANDLE hProcess;
char* moduleBaseChar;
bool isF4FovEnabled;
uintptr_t f4FovAddress;
float newf4FovValue;


// Hooking

DWORD f4TCameraStructAddress;
DWORD hookAddress;
DWORD jumpBackAddress;
DWORD moduleBaseAddress;


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
        mov f4TCameraStructAddress, edx
        mov[eax], edx
        jmp[jumpBackAddress]
    }

}



DWORD WINAPI MainThread(LPVOID param) {


    isF4FovEnabled = false;
    f4FovUI = 450;
    f4FovActValue = (float)45.0;
    f4FovHoldValue = (float)45.0;
    justEnabledFOVApplication = false;
    justScrolled = false;
    hasFoundAddress = false;

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
    int gameVersion = GetGameVersion();

    // Determine where to hook based off this
    switch (gameVersion)
    {

        // Failed
        case 0:
            MessageBoxA(0, "Falied to determine game version.\nQuit and restart OMSI.", "OMSI Presentation Tools", MB_OK | MB_ICONERROR);
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


    // We are overwriting 006E6392 and 006E6395
    int hookLength = 5;

    /* Where we jump back to at the end of the function we detour to.
    *  This is the address of the original function we hooked at, plus the length of the jmp instruction. */
    jumpBackAddress = hookAddress + hookLength;

    // Perform the hook
    //Hook((void*)hookAddress, localFunc, hookLength);
    printf("%02x", hookAddress);
    std::cout << std::endl;
    printf("%02x", (DWORD)moduleBaseAddress);

    // Not exiting here as this destroys the code to be jumped to
    // FreeLibraryAndExitThread((HMODULE)param, 0);

    return 0;

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

    // Temporary variable
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

    char Tram_22032 = (char)OMSI_22032_ANSI;
    char Latest_23004 = (char)OMSI_23004_ANSI;
    char mask = (char)ANSI_MASK;
    char versionSearchStart = (char) ((DWORD)moduleBaseAddress + (DWORD)OMSI_VERSIONCHECK_START_RELADDR);
    intptr_t versionSearchRegionSize = 312;

    scanStatus23032 = InternalScanForGameVersion(&Tram_22032, &mask, &versionSearchStart, versionSearchRegionSize);

    if (scanStatus23032) {
        result = 1;
    }
    else {
        scanStatus23004 = InternalScanForGameVersion(&Latest_23004, &mask, &versionSearchStart, versionSearchRegionSize);
        if (scanStatus23004) {
            result = 2;
        }
    }

    return result;

}




/* Pattern scanner */

char* BasicScan(char* pattern, char* mask, char* begin, intptr_t size)
{
    intptr_t patternLen = strlen(mask);

    for (int i = 0; i < size; i++)
    {
        bool found = true;
        for (int j = 0; j < patternLen; j++)
        {
            if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j))
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return (begin + i);
        }
    }
    return nullptr;
}


/* Internal pattern scan wrapper which only reports success */

bool InternalScanForGameVersion(char* pattern, char* mask, char* begin, intptr_t size)
{
    char* match{ nullptr };
    bool found = false;
    MEMORY_BASIC_INFORMATION mbi{};

    for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
    {
        if (!VirtualQuery(curr, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

        match = BasicScan(pattern, mask, curr, mbi.RegionSize);

        if (match != nullptr)
        {
            found = true;
            break;
        }
    }
    return found;
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
    std::cout << std::endl << "Patching done, closing console & process handle";
    CloseHandle(hProcess);
}


/* --- OMSI Functions End --- */
