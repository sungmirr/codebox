#ifndef _MEMINFO32_H_
#define _MEMINFO32_H_

#include <windows.h>
#include <psapi.h>
#include <strsafe.h>

#pragma comment(lib,"psapi.lib")

class Meminfo32
{
private:
    HANDLE hProcess;
    bool ready;
    MEMORY_BASIC_INFORMATION mbi;

public:
    Meminfo32() { memset(&mbi, 0, sizeof(mbi)); ready = false; hProcess=0; }
    ~Meminfo32()
    {
        if(hProcess)
            CloseHandle(hProcess);
    }

    bool InitMeminfo32(ULONG pid, LPCVOID address);
    bool InitImageMeminfo32(ULONG pid, LPCVOID address);
    void ClearMeminfo32();
    void ClearImageMeminfo32();
    PVOID GetAllocationAddress();
    DWORD GetAllocationProtect();
    PVOID GetBaseAddress();
    DWORD GetRegionSize();
    DWORD GetType();
    DWORD GetProtect();
    static bool ProtectToStringW(DWORD protect, LPWSTR buf, size_t bufsize);
    static bool SizeToStringW(DOUBLE size, LPWSTR buf, size_t bufsize);
    bool AddressToModuleNameW(LPWSTR buf, size_t bufsize);
};

#endif