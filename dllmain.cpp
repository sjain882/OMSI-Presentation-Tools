/* OMSI Presentation Tools
*  C++17, Windows Forms, SimpleINI
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
#include "windows.h"
#include <TlHelp32.h>
#include <memoryapi.h>
#include <winuser.h>
#include "MyForm.h"
#include "OMSIPresToolsCLR.h"
#include "lib/AOBScanner.h"
#include "lib/SimpleIni.h"
#include "lib/ConvertUTF.h"


using namespace System;
using namespace System::Windows::Forms;



/* Export standard OMSI functions so OMSI can call them.
*  This prevents the linker from obfustucating function names.
*  Also via Project Properties > All Configurations > Linker
*  > Input > type "OMSIDLL.def" for external export list.
*/

extern "C" __declspec(dllexport)void __stdcall PluginStart(void* aOwner);
extern "C" __declspec(dllexport)void __stdcall AccessVariable(unsigned short varindex, float* value, bool* write);
extern "C" __declspec(dllexport)void __stdcall AccessStringVariable(unsigned short varindex, wchar_t* value, bool* write);
extern "C" __declspec(dllexport)void __stdcall AccessTrigger(unsigned short triggerindex, bool* active);
extern "C" __declspec(dllexport)void __stdcall AccessSystemVariable(unsigned short varindex, float* value, bool* write);
extern "C" __declspec(dllexport)void __stdcall PluginFinalize();



// Instantiate variables

// Internal
float* f4fovptr;
FILE* fDummy;
HANDLE mhStdOutput;
DWORD procId;
HANDLE hProcess;
bool hasPatternScanned;
char* moduleBaseChar;



// UI

bool isF4FovEnabled;


// DLL Entrypoint

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}



// TimedExecution Struct by rev_eng_e

struct TimedExecution
{

    DWORD ms, s, m, h, startTick, endTick;
    float elapsedTime;

    void startTiming()
    {
        DWORD ticks = startTick = GetTickCount();
        ms = ticks % 1000;
        ticks /= 1000;
        s = ticks % 60;
        ticks /= 60;
        m = ticks % 60;
        ticks /= 60;
        h = ticks;
        printf("Started at: %d:%02d:%02d.%03d\n", h, m, s, ms);
    }

    void endTiming()
    {
        DWORD ticks = endTick = GetTickCount();
        ms = (ticks % 1000);
        ticks /= 1000;
        s = (ticks % 60);
        ticks /= 60;
        m = (ticks % 60);
        ticks /= 60;
        h = ticks;
        elapsedTime = (float)(endTick - startTick) / 1000.0f;
        printf("Finished at: %d:%02d:%02d.%03d\n", h, m, s, ms);
    }

};


// UI

void toggleF4FovEnabled() {
    isF4FovEnabled = !isF4FovEnabled;
}


// GetProcessID

DWORD GetProcId(const wchar_t* procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!_wcsicmp(procEntry.szExeFile, procName))
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}



// Get ModuleBase struct

auto GetModuleBase(DWORD proc_id, const wchar_t* modName)
{
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, proc_id);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    CloseHandle(hSnap);
                    return modEntry;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    return MODULEENTRY32();
}



// Get address of ModuleBase struct

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}



// AoB Pattern Scanner main method by rev_eng_e

void PatternScanForF4()
{

    uintptr_t moduleBase = (uintptr_t)moduleBaseChar;

    BYTE* findme = (BYTE*)malloc(100);
    findme[0] = 0x31;
    findme[1] = rand() % 0xff;
    findme[2] = 0x33;
    findme[3] = 0x33;
    findme[4] = 0x37;
    findme[5] = rand() % 0xff;
    findme[6] = 0xab;
    findme[7] = 0xca;
    printf("FindMe address: %p\n", findme);
    TimedExecution t;
    
    char buffer [100];
    int returnText = 100;
    int bufferSize = 100;

    AOBScanner scanner(0x00401000, 0xFFFFFFFF);
    t.startTiming();
    BYTE* foundAddress = scanner.Scan("90 E8 ?? ?? 78 CA 7E 00 0C 72"); // OMSI F4 MapCam TCamera Struct "Header" - Will be found! :)
    //BYTE *foundAddress=scanner.Scan("31 xx 33 33 37 xx ab ca aa aa aa aa"); //Probably wont be found
    t.endTiming();
    if (foundAddress)
    {
        //returnText = snprintf(buffer, bufferSize, "Found F4 FOV at %p in %.2fs", foundAddress, t.elapsedTime);

        printf("Found other address containing FindMe's bytes from AOB: %p in %.2f seconds", foundAddress, t.elapsedTime);
        //returnText = snprintf(buffer, bufferSize, "Found F4 FOV again at %p in %.2fs", foundAddress, t.elapsedTime);
        //returnText = snprintf(buffer, bufferSize, "Found it again!");
    }
    else
    {
        //returnText = snprintf(buffer, bufferSize, "Didn't find F4 FOV in %.2fs", scanner.RegionEnd, t.elapsedTime);
        printf("Did not locate address in scan up to: %p and it took: %.2f seconds", scanner.RegionEnd, t.elapsedTime);
    }

    hasPatternScanned = true;

}


/* --- OMSI Functions Start --- */


// Called on OMSI startup (just before main menu appears)

void __stdcall PluginStart(void* aOwner)
{
    //	Sleep(5000);
    //	f4fovptr = (float*)0x006E6349;
    //	*(float*)f4fovptr = 19.00;

    isF4FovEnabled = false;
    f4FovUI = 450;
    f4FovActValue = (float)45.0;
    f4FovHoldValue = (float)45.0;
    justEnabledFOVApplication = false;
    justScrolled = false;

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    OMSIPresToolsCLR::MyForm form;
    form.MaximizeBox = false;
    Application::Run(% form);
    


    AllocConsole();
    mhStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    SetConsoleTitleA("OMSI Presentation Tools (Release, x86) - PreAlpha DO NOT REDISTRIBUTE");

    hasPatternScanned = false;

    std::cout << "Waiting for 10 seconds..." << std::endl;
    Sleep(10000);

    // Get process ID
    procId = GetProcId(L"Omsi.exe");
    std::cout << "procId = " << procId << std::endl;

    // Get module base address
    // OMSI Prefers 0x00400000
    // cout will show 0x400000
    uintptr_t moduleBase = GetModuleBaseAddress(procId, L"Omsi.exe");
    std::cout << "moduleBase = " << "0x" << std::hex << moduleBase << std::endl;
    moduleBaseChar = (char*)moduleBase;

    // Get handle to Process
    hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    // Calculate F4 FOV Initialisation value - NEEDS REWORKING
    uintptr_t f4FovInitAddr = moduleBase + 0x002E634A;
    //    uintptr_t f4FovInitAddr = 0x006E634A;
    std::cout << "f4FovInitAddr = " << "0x" << std::hex << f4FovInitAddr << std::endl;

    // Read fov value
    int f4FOVInitValue = 45;
    ReadProcessMemory(hProcess, (BYTE*)f4FovInitAddr, &f4FOVInitValue, sizeof(f4FOVInitValue), nullptr);
    std::cout << "f4FovInitValue = " << f4FOVInitValue << std::endl;

    Sleep(5000);

    // Write to it
    float newf4FovInitValue = 14.235;
    WriteProcessMemory(hProcess, (BYTE*)f4FovInitAddr, &newf4FovInitValue, sizeof(newf4FovInitValue), nullptr);

    // Read fov value
    ReadProcessMemory(hProcess, (BYTE*)f4FovInitAddr, &f4FOVInitValue, sizeof(f4FOVInitValue), nullptr);
    std::cout << "New f4FovInitValue = " << f4FOVInitValue << std::endl;

}


/* Each Access*() is called by OMSI EVERY FRAME, for EACH variable/trigger
*  listed in the OPL, provided the user has currently selected a bus.
*  ! Keep the code of these routines optimised !
*  (Note that this means this function could be called multiple times per frame -
*   lets say we have 15 local variables listed in the OPL - then, this function will
*   be called 15 times every frame of the game. This can be resource intensive!)
*  So, can be used like a loop where varindex/trigger is the incrementing value
*  (index of the variable/trigger being passed in the current call from the OPL list).
*  The easiest way to understand what variable is currently being called is to ingest all
*  variables/triggers into a list with listName[varindex] = (float)*value; and then
*  reference values from the list with the same index as listed in the OPL, e.g.,
*  listName[0] is the first variable/trigger listed in the OPL file.
*/

void __stdcall AccessVariable(unsigned short varindex, float* value, bool* write)
{
    if (!hasPatternScanned) {
        PatternScanForF4();
    }
}

void __stdcall AccessStringVariable(unsigned short varindex, wchar_t* value, bool* write)
{
}


void __stdcall AccessTrigger(unsigned short triggerindex, bool* active)
{
}


void __stdcall AccessSystemVariable(unsigned short varindex, float* value, bool* write)
{
}


// Called on OMSI quit (when the user clicks "Yes" on the confirmation)

void __stdcall PluginFinalize()
{
    std::cout << "Patching done, closing console & process handle";
    FreeConsole();
    CloseHandle(hProcess);
}


/* --- OMSI Functions End --- */
