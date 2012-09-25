/*++
    2012. 9. 26
    
    HideProcessHookMDL
    - ��ƮŶ 109p 

    Prerequisite
    - SSDT, KeServiceDescriptorTable(ntoskrnl.exe)
      KeServiceDescriptorTableShadow(win32k.sys, USER,GDI ������ �ּ�)
    - SSDT�� �޸� ��ȣ ����(CR0 Trick or MDL)
      MDL
      1. SSDT�� ���̽� �ּҿ� ũ�⸦ ��´�
      2. SSDT������ ǥ�����ִ� MDL�� non-paged pool �޸� ������ �����(MmCreateMdl)
      3. ������ MDL �÷��� ���� MDL_MAPPED_TO_SYSTEM_VA���� OR�����Ѵ�
      4. MmMapLockedPages �Լ� ȣ��
    - Zw*�Լ� ���� �ڵ�
      Zw*�Լ��� opcode ������ �ش� �Լ��� �ε��� ��ȣ�� �̿��� ����
      move ax, ULONG   (ULONG�� SSDT������ �ε��� ��ȣ)
      �ε��� ��ȣ�� opcode�� �ι�° ����Ʈ �κп� ����
    - InterlockedExchange
    - ZwQuerySystemInformation
       ���μ����� ������ ���� ���ϱ�
       �۾������ڴ� �� �Լ��� �̿��� ���μ��� ����Ʈ ������ ����(SystemInformationClass, 5)
 --*/

#include "ntddk.h"


#pragma pack(1)
typedef struct ServiceDescriptorEntry {
    unsigned int *ServiceTableBase;
    unsigned int *ServiceCounterTableBase; //Used only in checked build
    unsigned int NumberOfServices;
    unsigned char *ParamTableBase;
} ServiceDescriptorTableEntry_t, *PServiceDescriptorTableEntry_t;
#pragma pack()

__declspec(dllimport)  ServiceDescriptorTableEntry_t KeServiceDescriptorTable;

// ntoskernl.exe���� �����ϴ� Zw*�Լ��� �ּҸ� �Է� �޾� �׿� �����ϴ� SSDT������ Nt*�Լ��� �ּҸ� ����
// Zw*�Լ��� SSDT�� Nt*�Լ��� �ϴ��� ���� �ƴ�
#define SYSTEMSERVICE(_function)  KeServiceDescriptorTable.ServiceTableBase[ *(PULONG)((PUCHAR)_function+1)]��
// Zw*�Լ��� �ּҸ� �Է� �޾� �ش� �Լ��� SSDT������ �ε��� ��ȣ�� ���Ѵ�
#define SYSCALL_INDEX(_Function) *(PULONG)((PUCHAR)_Function+1)
// 
#define HOOK_SYSCALL(_Function, _Hook, _Orig )  \
    _Orig = (PVOID) InterlockedExchange( (PLONG) &MappedSystemCallTable[SYSCALL_INDEX(_Function)], (LONG) _Hook)
#define UNHOOK_SYSCALL(_Function, _Hook, _Orig )  \
    InterlockedExchange( (PLONG) &MappedSystemCallTable[SYSCALL_INDEX(_Function)], (LONG) _Hook)



VOID OnUnload(IN PDRIVER_OBJECT DriverObject)
{
    DbgPrint("HideProcessHookMDL OnUnload called\n");
}



NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    DbgPrint("HideProcessHookMDL\n");
    DriverObject->DriverUnload = OnUnload;
    return STATUS_SUCCESS;
}