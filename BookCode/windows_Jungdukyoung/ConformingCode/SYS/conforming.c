#include "ntddk.h"
#include "Intel80x86.h"
#include "UndocNTAPI.h"
#include "prism.h"

NTSTATUS CreateConformingCode(unsigned short *pConforomingCodeSel);

NTSTATUS ReleaseConformingCode(unsigned short selector);

NTSTATUS My_IoControl(PFILE_OBJECT pFileObject, ULONG nIoCode, PCHAR pSystemBuffer,
                      ULONG nInput, ULONG nOutput, ULONG *nReturnOut)
{
    NTSTATUS ntStatus = STATUS_SUCCESS;

    switch(nIoCode)
    {
        case IOCTL_CREATE_CONFORMING_CODE:
        {
            PCONFORMING_INFO pConform;
            unsigned short sel;

            pConform = (PCONFORMING_INFO)pSystemBuffer;
            ntStatus = CreateConformingCode(&sel);
            if(NT_SUCCESS(ntStatus))
            {
                pConform->ConformingSel = sel;
                *nReturnOut = sizeof(CONFORMING_INFO);
            }
            break;
        }
        case IOCTL_RELEASE_CONFORMING_CODE:
        {
            PCONFORMING_INFO pConform;

            pConform = (PCONFORMING_INFO)pSystemBuffer;
            ntStatus = ReleaseConformingCode(pConform->ConformingSel);
            break;
        }
    }

    return ntStatus;
}

NTSTATUS CreateConformingCode(unsigned short *pConformingCodeSel)
{
    CODE_SEG_DESCRIPTOR code_desc;
    unsigned short selector;
    NTSTATUS ntStatus;

    ntStatus = KeI386AllocateGdtSelectors(&selector, 0x01);
    if(!NT_SUCCESS(ntStatus))
    {
        KdPrint(("Unable to allocate selectors from GDT\n"));
        return ntStatus;
    }
    KdPrint(("Two Selectors allocated = %x\n", selector));

    // 1. Setting Code Descriptor
    code_desc.Limit_0_15 = 0xFFFF;
    code_desc.Base_0_15 = 0;
    code_desc.Base_16_23 = 0;

    code_desc.Read = 1;
    code_desc.Conforming = 1;	//Conforming Code
    code_desc.Code_data = 1;
    code_desc.S = 1;
    code_desc.DPL = 3;	        //User Level접근 가능
    code_desc.Present = 1;

    code_desc.Limit_16_19 = 0xF;
    code_desc.Unused = 0;
    code_desc.Reserved = 1;
    code_desc.DefaultBit = 1;
    code_desc.Granularity = 1;

    code_desc.Base_24_31 = 0;

    ntStatus = KeI386SetGdtSelector(selector, &code_desc);
    if(!NT_SUCCESS(ntStatus))
    {
        KdPrint(("KeI386SetGdtSelector Error(%x)\n", ntStatus));
        KeI386ReleaseGdtSelectors(&selector, 0x01);
        return ntStatus;
    }

    *pConformingCodeSel = selector;

    return STATUS_SUCCESS;
}

NTSTATUS ReleaseConformingCode(unsigned short selector)
{
    NTSTATUS ntStatus;

    ntStatus = KeI386ReleaseGdtSelectors(&selector, 0x01);
    if(!NT_SUCCESS(ntStatus))
        KdPrint(("ReleaseGDTSelectors Error %x\n", ntStatus));

    return ntStatus;
}