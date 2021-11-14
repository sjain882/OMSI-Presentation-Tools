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
#include <winuser.h>



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


void Parse(char* combo, char* pattern, char* mask)
{
    char lastChar = ' ';
    unsigned int j = 0;

    for (unsigned int i = 0; i < strlen(combo); i++)
    {
        if ((combo[i] == '?' || combo[i] == '*') && (lastChar != '?' && lastChar != '*'))
        {
            pattern[j] = mask[j] = '?';
            j++;
        }

        else if (isspace(lastChar))
        {
            pattern[j] = lastChar = (char)strtol(&combo[i], 0, 16);
            mask[j] = 'x';
            j++;
        }
        lastChar = combo[i];
    }
    pattern[j] = mask[j] = '\0';
}


char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size)
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


char* ScanEx(char* pattern, char* mask, char* begin, intptr_t size, HANDLE hProc)
{
    char* match{ nullptr };
    SIZE_T bytesRead;
    DWORD oldprotect;
    char* buffer{ nullptr };
    MEMORY_BASIC_INFORMATION mbi;
    mbi.RegionSize = 0x1000;//

    VirtualQueryEx(hProc, (LPCVOID)begin, &mbi, sizeof(mbi));

    for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
    {
        if (!VirtualQueryEx(hProc, curr, &mbi, sizeof(mbi))) continue;
        if (mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

        delete[] buffer;
        buffer = new char[mbi.RegionSize];

        if (VirtualProtectEx(hProc, mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oldprotect))
        {
            ReadProcessMemory(hProc, mbi.BaseAddress, buffer, mbi.RegionSize, &bytesRead);
            VirtualProtectEx(hProc, mbi.BaseAddress, mbi.RegionSize, oldprotect, &oldprotect);

            char* internalAddr = ScanBasic(pattern, mask, buffer, (intptr_t)bytesRead);

            if (internalAddr != nullptr)
            {
                //calculate from internal to external
                match = curr + (internalAddr - buffer);
                break;
            }
        }
    }
    delete[] buffer;
    return match;
}


char* ScanModEx(char* pattern, char* mask, MODULEENTRY32& modEntry, HANDLE hProc)
{
    return ScanEx(pattern, mask, (char*)modEntry.modBaseAddr, modEntry.modBaseSize, hProc);
}




void PatternScanForF4()
{
    //    char idaSig = (char)"90 E8 ?? 05 78 CA 7E 00 0C 72 ?? 05 39 8E E3 3F CD CC CC 3D 00 50 C3 47 00 00 00 00 00 00 00 00";

    char sig = (char)"\x90\xE8\xAA\x05\x78\xCA\x7E\x00\x0C\x72\xB4\x05\x39\x8E\xE3\x3F\xCD\xCC\xCC\x3D\x00\x50\xC3\x47\x00\x00\x00\x00\x00\x00\x00\x00";

    char mask = (char)"xx?xxxxxxx?xxxxxxxxxxxxxxxxxxxxx";

    char sig2 = (char)"\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
    char mask2 = (char)"xxxxxxx";

    // Get module base
    auto moduleBaseActual = GetModuleBase(procId, L"Omsi.exe");

//    char* F4_TCamera_struct_addy = ScanModEx(&sig, &mask, moduleBaseActual, hProcess);

//    char* F4_TCamera_struct_addy = ScanModEx(const_cast<char*>("\x90\xE8\xAA\x05\x78\xCA\x7E\x00\x0C\x72\xB4\x05\x39\x8E\xE3\x3F\xCD\xCC\xCC\x3D\x00\x50\xC3\x47\x00\x00\x00\x00\x00\x00\x00\x00"), const_cast<char*>("xx?xxxxxxx?xxxxxxxxxxxxxxxxxxxxx"), moduleBaseActual, hProcess);

    char* F4_TCamera_struct_addy = ScanModEx(const_cast<char*>("\xFF\xFF\xFF\xFF\xFF\xFF\xFF"), const_cast<char*>("xxxxxxx"), moduleBaseActual, hProcess);


    uintptr_t* F4_TCamera_struct_addyCasted = (uintptr_t*)F4_TCamera_struct_addy;

//    Convert::ToInt32(F4_TCamera_struct_addyCasted).ToString("X")); // I RECEIVE F8C400000101

    std::cout << F4_TCamera_struct_addyCasted;

    //    std::cout << "moduleBase = " << "0x" << std::hex << F4_TCamera_struct_addy << std::endl;

    hasPatternScanned = true;

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

    hasPatternScanned = false;

    std::cout << "Waiting for 10 seconds..." << std::endl;
    Sleep(10000);

    // Get process ID
	procId = GetProcId(L"Omsi.exe");
    std::cout << "procId = " << procId << std::endl;

    // Get module base address
    uintptr_t moduleBase = GetModuleBaseAddress(procId, L"Omsi.exe");
    std::cout << "moduleBase = " << "0x" << std::hex << moduleBase << std::endl;

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

void __stdcall PluginFinalize()
{
    std::cout << "Patching done, closing console & process handle";
    FreeConsole();
    CloseHandle(hProcess);
}


