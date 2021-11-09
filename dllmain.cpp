/* OMSI Presentation Tools
*  C++20, dear ImGui, SimpleINI
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


void __stdcall PluginStart(void* aOwner)
{
//	Sleep(5000);
//	f4fovptr = (float*)0x006E6349;
//	*(float*)f4fovptr = 19.00;

    AllocConsole();
    mhStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    SetConsoleTitleA("OMSI Presentation Tools (Release, x86) - PreAlpha DO NOT REDISTRIBUTE");


    std::cout << "Waiting for 10 seconds..." << std::endl;
    Sleep(10000);

    // Get process ID
	DWORD procId = GetProcId(L"Omsi.exe");
    std::cout << "procId = " << procId << std::endl;

    // Get module base address
    uintptr_t moduleBase = GetModuleBaseAddress(procId, L"Omsi.exe");
    std::cout << "moduleBase = " << "0x" << std::hex << moduleBase << std::endl;

    // Get handle to Process
    HANDLE hProcess = 0;
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
    float newf4FovInitValue = 19;
    WriteProcessMemory(hProcess, (BYTE*)f4FovInitAddr, &newf4FovInitValue, sizeof(newf4FovInitValue), nullptr);

    // Read fov value
    ReadProcessMemory(hProcess, (BYTE*)f4FovInitAddr, &f4FOVInitValue, sizeof(f4FOVInitValue), nullptr);
    std::cout << "New f4FovInitValue = " << f4FOVInitValue << std::endl;

    FreeConsole();

    CloseHandle(hProcess);

}


void __stdcall AccessVariable(unsigned short varindex, float* value, bool* write)
{
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

void __stdcall PluginFinalize()
{
}


