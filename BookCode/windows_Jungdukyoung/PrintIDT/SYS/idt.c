/*++
    2012. 8. 15 14:00
        - IDT_ENTRY, IDTR �ڷ��� Intel80x86.h�� ����

        - sidt��ɾ �̿� IDTR�� ������ ����
           __asm sidt 6BytePointer;

        - IDTR.BaseAddress ������ �̿� idt_entry�� ��ȸ

 --*/
#include "ntddk.h"
#include "prism.h"
#include "Intel80x86.h"

void IntIDT_Print();

VOID My_DriverEntry(IN PDRIVER_OBJECT DriverObject ,PDEVICE_OBJECT deviceObject)
{
}

VOID My_DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
}


NTSTATUS My_IoControl(PFILE_OBJECT pFileObject, ULONG nIoCode, PCHAR pSystemBuffer, ULONG nInput, ULONG nOutput, ULONG *nReturnOut)
{
    if(nIoCode == IOCTL_PRINT_IDT)
    {
        IntIDT_Print();
    }	

    return STATUS_SUCCESS;
}

void IntIDT_Print()
{
    PIDTR pIdtr;
    PIDT_ENTRY pIdtEntry;
    char szBuffIdtr[6];
    int i;

    ULONG dwHandler;

    __asm sidt szBuffIdtr;
    pIdtr = (PIDTR)szBuffIdtr;
    pIdtEntry = (PIDT_ENTRY)pIdtr->Base;

    for(i = 0; i < 256; ++i)
    {
        dwHandler = ((ULONG)pIdtEntry[i].Offset_16_31 << 16U) | (pIdtEntry[i].Offset_0_15);

        DbgPrint("[0x%X] Selector 0x%x, Offset 0x%x, Type 0x%x, DPL %d, Present %d\n",
                   i, pIdtEntry[i].Selector, dwHandler, 
                   pIdtEntry[i].Type, pIdtEntry[i].DPL, pIdtEntry[i].Present);
    }
}