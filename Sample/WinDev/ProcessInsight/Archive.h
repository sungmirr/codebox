#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

#include <windows.h>
#include <iostream>
#include <list>
#define _NTDDK_
#include "nativeAPI.h"
#include "Meminfo32.h"
using namespace std;


// nativeAPI.h로 옮겨
typedef NTSTATUS (NTAPI *_NtQueryInformationProcess)(
    HANDLE ProcessHandle,
    ULONG ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PDWORD ReturnLength
    );

typedef NTSTATUS (NTAPI *_NtQueryInformationThread)(
    HANDLE ThreadHandle,
    ULONG ThreadInformationClass,
    PVOID ThreadInformation,
    ULONG ThreadInformationLength,
    PULONG ReturnLength
    );


#define NX_STRING_SIZE 32
// SIGNITURE 추가?
typedef struct _NX_MODULEINFO
{
    WCHAR name[MAX_PATH];
    PVOID address;              /// 64bit 호환 되게 바꿔
    WCHAR szSize[NX_STRING_SIZE];
    ULONG protection;
}NX_MODULEINFO, *PNX_MODULEINFO;


typedef struct _NX_THREADINFO
{
    WCHAR modulename[MAX_PATH];
    ULONG tid;
    PVOID startaddress;         /// 64bit 호환 되게 바꿔
    ULONG priority;
}NX_THREADINFO, *PNX_THREADINFO;


typedef struct _NX_PROCESSINFO
{
    WCHAR name[MAX_PATH];
    WCHAR *cmdline;             ///// 메모리 해제~~!! 주의  아님 string으로 대체
    ULONG pid;
    ULONG ppid;
    ULONG priority;
    list<PNX_MODULEINFO> mlist;        // 메모리 해제
    list<PNX_THREADINFO> tlist;        // 메모리 해제
}NX_PROCESSINFO, *PNX_PROCESSINFO;

class Sysinfo
{   
protected:
    bool x64;
    _NtQueryInformationProcess pNtQIP;
    _NtQueryInformationThread pNtQIT;

    bool IsProcessWow64(HANDLE hProcess)
    {
        if(x64)
        {
            NTSTATUS s;
            size_t w64;
            ULONG readed;

            s = pNtQIP(hProcess, ProcessWow64Information, &w64, sizeof(w64), &readed);
            if(!NT_SUCCESS(s))
                return false;

            if(w64)
                return true;
        }
        return false;
    }

    Sysinfo() : x64(false),pNtQIP(NULL),pNtQIT(NULL) {}

    bool Init()
    {
#if 1
        SYSTEM_INFO sInfo;
        GetNativeSystemInfo(&sInfo);
        if(sInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
            x64 = true;
        else
            x64 = false;
#endif

        HMODULE hMod = GetModuleHandleA("ntdll.dll");
        pNtQIP = (_NtQueryInformationProcess)GetProcAddress(hMod, "NtQueryInformationProcess");
        if(!pNtQIP)
            return false;
        pNtQIT = (_NtQueryInformationThread)GetProcAddress(hMod, "NtQueryInformationThread");
        if(!pNtQIT)
            return false;

        return true;
    }
};



class Archive : public Sysinfo
{
private:
    list<PNX_PROCESSINFO> plist;           // pid기준으로 맵으로 변경
    list<PNX_MODULEINFO>::iterator mit;
    list<PNX_THREADINFO>::iterator tit;
    list<PNX_PROCESSINFO>::iterator pit;

    bool CleanupProcessList(void);
    bool CleanupThreadList(const PNX_PROCESSINFO &pi);
    bool CleanupModuleList(const PNX_PROCESSINFO &pi);

    bool SetDebugPrivilege(void);

    PVOID GetPebAddress32(HANDLE hProcess);         
    PVOID GetPebAddressWow(HANDLE hProcess);
    PVOID64 GetPebAddress64(HANDLE hProcess);

    bool GetProcessCmdLineW(ULONG pid, PWCHAR *cmdline, PDWORD readed);
    bool GetThreadStartAddress(ULONG tid, PVOID *address);
                                        
public:
    bool SetProcessList(void);
    bool SetThreadList(ULONG pid, PNX_PROCESSINFO &pi);
    bool SetModuleList(ULONG pid, PNX_PROCESSINFO &pi);

    bool PrintProcessList(void);
    bool PrintThreadList(PNX_PROCESSINFO &pi);
    bool PrintModuleList(PNX_PROCESSINFO &pi);

    Archive()
    {
        bool b = SetDebugPrivilege();
        if(!b) cout << "SetPrivilege fail\n";
        b = Init();
        if(!b) cout << "sysinfo init fail\n";
        printf("Init(%d)\n", b);
    }
    ~Archive()
    {
        CleanupProcessList();
    }
};

#endif // #ifndef _ARCHIVE_H_