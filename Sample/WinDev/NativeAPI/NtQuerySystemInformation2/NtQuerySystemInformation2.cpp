/*++

<2012.9.27 23:00>
    NtQuerySystemInformation2
      프로세스와 스레드 정보 얻기(SystemProcessesAndThreadsInformation,5)
    
    Reference
      - http://www.jiniya.net/wp/archives/7676
--*/

#include <windows.h>
#include <stdio.h>
#define _NTDDK_
#include "..\nativeAPI.h"


// NtQuerySystemInformatioin함수를 동적으로 로딩해서 사용
typedef 
NTSTATUS
(WINAPI *NtQuerySystemInformationT)
(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);

template <class T>
class Visitor
{
public:
    virtual BOOL Visit(T& data) = 0;
};

typedef Visitor<SYSTEM_THREADS> ThreadVisitor;


class ThreadPrinter : public ThreadVisitor
{
public:
    virtual BOOL Visit(SYSTEM_THREADS &data)
    {
        printf("Pid : %5d, Tid : %5d\n", data.ClientId.UniqueProcess, data.ClientId.UniqueThread);
        return TRUE;
    }
};


BOOL NtqsiEnumThreads(ThreadVisitor &visitor)
{
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    NtQuerySystemInformationT pNTQSI;
    pNTQSI = (NtQuerySystemInformationT)GetProcAddress(ntdll, "NtQuerySystemInformation");

    const int NTQSI_MAX_TRY = 20;
    const ULONG NTQSI_BUFFER_INIT_SIZE = 0x1000;
    const ULONG NTQSI_BUFFER_MARGIN = 0x500;

    ULONG buffer_size = NTQSI_BUFFER_INIT_SIZE;
    PUCHAR buffer = new UCHAR[buffer_size];
    ULONG req_size;
    NTSTATUS s;

    for(int i=0; i < NTQSI_MAX_TRY; ++i)
    {
        s = pNTQSI(SystemProcessesAndThreadsInformation, buffer, buffer_size, &req_size);
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
        PSYSTEM_THREADS t;
        t = (PSYSTEM_THREADS)GetPtr(p, sizeof(*p));
        for(int i=0; i < p->NumberOfThreads; ++i)
        {
            try
            {
                if(!visitor.Visit(t[i]))
                {
                    delete [] buffer;
                    return TRUE;
                }
            }
            catch(...)
            {
                delete [] buffer;
                return FALSE;
            }
        }

        p = (PRSYSTEM_PROCESS_INFORMATION)GetPtr(p, p->NextEntryOffset);
    }
    
    
    delete[] buffer;
    return TRUE;
}



void main()
{
    ThreadPrinter printer;
    NtqsiEnumThreads(printer);
}