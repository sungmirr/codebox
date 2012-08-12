



#include <windows.h>
#include <winternl.h>
#include <stdio.h>
#define _NTDDK_
#include "nativeAPI.h"
typedef struct _RSYSTEM_PROCESS_INFORMATION 
{
    ULONG NextEntryOffset; // 다음 프로세스 정보 오프셋
    ULONG NumberOfThreads; // 이 프로세스 포함된 스레드 개수
    LARGE_INTEGER WorkingSetPrivateSize;
    ULONG HardFaultCount;
    ULONG NumberOfThreadsHighWatermark;
    ULONGLONG CycleTime; // 프로세스 수행에 소모된 사이클 시간
    LARGE_INTEGER CreateTime; // 생성 시간
    LARGE_INTEGER UserTime; // 유저 모드에서 수행된 시간
    LARGE_INTEGER KernelTime; // 커널 모드에서 수행된 시간
    UNICODE_STRING ImageName; // 프로세스 이미지 이름
    ULONG BasePriority;
    HANDLE UniqueProcessId; // 프로세스 아이디
    HANDLE InheritedFromUniqueProcessId; // 부모 프로세스 아이디
    ULONG HandleCount;
    ULONG SessionId;
    ULONG_PTR UniqueProcessKey;
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivatePageCount;
    LARGE_INTEGER ReadOperationCount;
    LARGE_INTEGER WriteOperationCount;
    LARGE_INTEGER OtherOperationCount;
    LARGE_INTEGER ReadTransferCount;
    LARGE_INTEGER WriteTransferCount;
    LARGE_INTEGER OtherTransferCount;
} RSYSTEM_PROCESS_INFORMATION, *PRSYSTEM_PROCESS_INFORMATION;

typedef struct _CLIENT_ID
{
    HANDLE UniqueProcess; // 프로세스 아이디
    HANDLE UniqueThread; // 스레드 아이디
} CLIENT_ID, *PCLIENT_ID;

typedef struct _RSYSTEM_THREAD_INFORMATION 
{
    LARGE_INTEGER KernelTime; // 커널 모드에서 수행된 시간
    LARGE_INTEGER UserTime; // 유저 모드에서 수행된 시간
    LARGE_INTEGER CreateTime; // 생성 시간
    ULONG WaitTime;
    PVOID StartAddress; // 시작 주소
    CLIENT_ID ClientId; // 프로세스/스레드 아이디
    ULONG Priority; 
    LONG BasePriority;
    ULONG ContextSwitches; 
    ULONG ThreadState; // 현재 스레드 수행 상태
    ULONG WaitReason; // 대기 사유
} RSYSTEM_THREAD_INFORMATION, *PRSYSTEM_THREAD_INFORMATION;

#define STATUS_INFO_LENGTH_MISMATCH 0xC0000004
#define XGetPtr(base, offset) ((PVOID)((ULONG_PTR) (base) + (ULONG_PTR) (offset)))

typedef 
NTSTATUS 
(WINAPI *NtQuerySystemInformationT)
(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);

template <class T>
class Visitor
{
public:
    virtual BOOL Visit(T &data) = 0;
};

typedef Visitor<RSYSTEM_THREAD_INFORMATION> ThreadVisitor;

BOOL NtqsiEnumThreads(ThreadVisitor &visitor)
{
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    NtQuerySystemInformationT pNTQSI;
    pNTQSI = (NtQuerySystemInformationT) 
        GetProcAddress(ntdll, "NtQuerySystemInformation");

    const int NTQSI_MAX_TRY = 20;
    const ULONG NTQSI_BUFFER_MARGIN = 4096;
    const ULONG NTQSI_BUFFER_INIT_SIZE = 200000;

    ULONG buffer_size = NTQSI_BUFFER_INIT_SIZE;
    PUCHAR buffer = new UCHAR[buffer_size];
    ULONG req_size;
    NTSTATUS s;

    for(int i=0; i<NTQSI_MAX_TRY; ++i)
    {
        s = pNTQSI(SystemProcessInformation, buffer, buffer_size, &req_size);
        if(NT_SUCCESS(s))
            break;

        if(buffer)
            delete [] buffer;

        if(s == STATUS_INFO_LENGTH_MISMATCH)
        {
            buffer_size = req_size + NTQSI_BUFFER_MARGIN;
            buffer = new UCHAR[buffer_size];
        }
        else
        {
            return FALSE;
        }
    }

    PRSYSTEM_PROCESS_INFORMATION p = (PRSYSTEM_PROCESS_INFORMATION) buffer;

    while(p->NextEntryOffset != 0)
    {
        PRSYSTEM_THREAD_INFORMATION t;
        t = (PRSYSTEM_THREAD_INFORMATION) XGetPtr(p, sizeof(*p));
        for(ULONG i=0; i<p->NumberOfThreads; ++i)
        {
            try
            {
                if(!visitor.Visit(t[i]))
                {
                    if(buffer)
                        delete [] buffer;

                    return TRUE;
                }
            }
            catch(...)
            {
                if(buffer)
                    delete [] buffer;

                return FALSE;
            }
        }

        p = (PRSYSTEM_PROCESS_INFORMATION) XGetPtr(p, p->NextEntryOffset);
    } 

    if(buffer)
        delete [] buffer;

    return TRUE;
}

class ThreadPrinter : public ThreadVisitor
{
public:
    virtual BOOL Visit(RSYSTEM_THREAD_INFORMATION &data)
    {
        printf("PID => %5d TID => %5d\n"
            , data.ClientId.UniqueProcess
            , data.ClientId.UniqueThread);

        return TRUE;
    }
};

int main()
{
    ThreadPrinter printer;
    NtqsiEnumThreads(printer);
    return 0;
}

#if 0

/*++
    ListProcessAndThread.exe

     - Native API(ZwQuerySystemInformation)를 이용 어플리케이션에서
      프로세스와 스레드 정보 얻기

     - 2012.7.25 20:00
--*/

#include <windows.h>
#include <stdio.h>
#define _NTDDK_
#include "nativeAPI.h"
#include <tchar.h>

void ShowErrorMessage(HRESULT hr);

int _tmain(void)
{
    DWORD dwAllocatedSize = 0, dwNeeded = 0;
    PSYSTEM_PROCESSES pProcesses = NULL;        // SYSTEM_PROCESSES안에 SYSTEM_THREADS 구조체 배열로 쓰레드정보포함
    int nThreadCount = 0;

    try
    {
        dwAllocatedSize = 0x1000;   // 4k, 4096
        pProcesses = (PSYSTEM_PROCESSES)VirtualAlloc(NULL, dwAllocatedSize, MEM_COMMIT, PAGE_READWRITE);

        while(ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, 
            pProcesses, dwAllocatedSize, &dwNeeded) == STATUS_INFO_LENGTH_MISMATCH)
        {
            VirtualFree(pProcesses, dwAllocatedSize, MEM_DECOMMIT);
            if(dwNeeded > dwAllocatedSize)
                dwAllocatedSize = dwNeeded;
            else
                dwAllocatedSize += 0x500;

            pProcesses = (PSYSTEM_PROCESSES)VirtualAlloc(NULL, dwAllocatedSize, MEM_COMMIT, PAGE_READWRITE);
        }
        
        while(pProcesses->NextEntryDelta != 0)
        {
            // 각 원소에 pProcess->NextEntryDelta만큼 오프셋 이동해서 접근
            // ULONG ThreadCount;, SYSTEM_THREADS Threads[1];  <== 얘네들 때문에 각 원소 사이즈가 각각틀리다
            pProcesses = (PSYSTEM_PROCESSES)((char *)pProcesses + pProcesses->NextEntryDelta);

            //Print Process Information
            _tprintf(_T("PID:%d - %s\n"), 
                pProcesses->ProcessId, 
                pProcesses->ProcessName.Buffer);

            //Print Thread
            for(ULONG nIndex = 0 ; nIndex < pProcesses->ThreadCount ; nIndex ++)
            {
                _tprintf(_T("    [%d], StartAddress : 0x%08x\n"), 
                    pProcesses->Threads[nIndex].ClientId.UniqueThread, 
                    pProcesses->Threads[nIndex].StartAddress);

            }
        }
    }
    catch(HRESULT hr)
    {
        ShowErrorMessage(hr);
    }
    catch(...)
    {
        MessageBox(0, _T("Exception raised!!!"), NULL, 0);
    }

    if(pProcesses)
        VirtualFree(pProcesses, dwAllocatedSize, MEM_DECOMMIT);

    return 0;
}



void ShowErrorMessage(HRESULT hr)
{
    LPVOID lpMsgBuff = NULL;

    if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS, 
        NULL, hr, 
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
        (LPTSTR)&lpMsgBuff, 0, NULL))
    {
        MessageBox(0, _T("알 수 없는 에러가 발생했습니다."), NULL, 0);
        return;
    }

    MessageBox(0, (LPCTSTR)lpMsgBuff, NULL, 0);
    LocalFree(lpMsgBuff);
}

#endif