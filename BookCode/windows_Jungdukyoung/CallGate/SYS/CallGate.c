#include <ntddk.h>
#include "intel80x86.h"
#include "UndocNTAPI.h"

#include "prism.h"


// Code Segment와 Call Gate 생성
// User Input : CALLGATE_INFO{ FuncAddress, NumParam }
// SYS Output : CALLGATE_INFO{ CodeSelector, CallGateSelector }
NTSTATUS CreateCallGate(CALLGATE_INFO *pCallGateInfo);

NTSTATUS ReleaseCallGate(CALLGATE_INFO *pCallGateInfo);


NTSTATUS My_IoControl(PFILE_OBJECT pFileObject, ULONG nIoCode, PCHAR pSystemBuffer,
                      ULONG nInput, ULONG nOutput, ULONG *nReturnOut)
{
    NTSTATUS ntStatus = STATUS_SUCCESS;

    switch(nIoCode)
    {
        case IOCTL_CREATE_CALLGATE:
        {
            PCALLGATE_INFO pCallGateInfo;

            pCallGateInfo = (PCALLGATE_INFO)pSystemBuffer;
            ntStatus = CreateCallGate(pCallGateInfo);
            if(ntStatus == STATUS_SUCCESS)
                *nReturnOut = sizeof(CALLGATE_INFO);
            break;
        }
        case IOCTL_RELEASE_CALLGATE:
        {
            PCALLGATE_INFO pCallGateInfo;

            pCallGateInfo = (PCALLGATE_INFO)pSystemBuffer;
            ntStatus = ReleaseCallGate(pCallGateInfo);
            break;
        }
    }

    return ntStatus;
}

NTSTATUS CreateCallGate(CALLGATE_INFO *pCallGateInfo)
{
    CALLGATE_DESCRIPTOR callgate_desc;
    CODE_SEG_DESCRIPTOR code_desc;
    unsigned short aSelector[2];
    NTSTATUS ntStatus;

    ntStatus = KeI386AllocateGdtSelectors(aSelector, 0x2);
    if(!NT_SUCCESS(ntStatus))
    {
        KdPrint(("Unable to allocate selectors from GDT\n"));
        return ntStatus;
    }

    KdPrint(("Two Selectors allocated = %x, %x\n", aSelector[0], aSelector[1]));

    /*1. Setting Code Descriptor*/
    code_desc.Limit_0_15 = 0xFFFF;
    code_desc.Base_0_15 = 0;
    code_desc.Base_16_23 = 0;

    code_desc.Read = 1;
    code_desc.Conforming = 0;
    code_desc.Code_data = 1;
    code_desc.S = 1;
    code_desc.DPL = 0;
    code_desc.Present = 1;

    code_desc.Limit_16_19 = 0xF;
    code_desc.Unused = 0;
    code_desc.Reserved = 1;
    code_desc.DefaultBit = 1;
    code_desc.Granularity = 1;

    code_desc.Base_24_31 = 0;



    /*2. Setting CallGate Descriptor*/
    callgate_desc.Offset_0_15 = LOWORD(pCallGateInfo->FuncAddress);   // offset LOWORD
    callgate_desc.Selector = aSelector[0];          // code segment 셀렉터 등록

    callgate_desc.Param_count = (unsigned char)pCallGateInfo->NumParam;
    callgate_desc.Dummy_bits = 0;

    callgate_desc.Type = 0xC;         //call gate
    callgate_desc.S = 0;    		  //A system descriptor
    callgate_desc.DPL = 3;            //can call at Ring 3 code 
    callgate_desc.Present = 1;
    callgate_desc.Offset_16_31 = HIWORD(pCallGateInfo->FuncAddress);   // offset HIWORD

    /* Set Coode Descriptor */
    ntStatus = KeI386SetGdtSelector(aSelector[0], &code_desc);
    if(ntStatus != STATUS_SUCCESS)
    {
        KdPrint(("KeI386SetGdtSelector Error (%x)\n", ntStatus));
        KeI386ReleaseGdtSelectors(aSelector, 0x02);        
        return ntStatus;
    }

    /*Set Call Gate*/
    ntStatus = KeI386SetGdtSelector(aSelector[1], &callgate_desc);
    if(ntStatus != STATUS_SUCCESS)
    {
        KdPrint(("KeI386SetGdtSelector Error (%x)\n", ntStatus));
        KeI386ReleaseGdtSelectors(aSelector, 0x02);        
        return ntStatus;
    }

    pCallGateInfo->CodeSelector = aSelector[0];
    pCallGateInfo->CallGateSelector = aSelector[1];

    return STATUS_SUCCESS;
}

NTSTATUS ReleaseCallGate(CALLGATE_INFO *pCallGateInfo)
{
    unsigned short aSelector[2];
    NTSTATUS ntStatus;
    
    aSelector[0] = pCallGateInfo->CodeSelector;
    aSelector[1] = pCallGateInfo->CallGateSelector;

    ntStatus = KeI386ReleaseGdtSelectors(aSelector, 0x2);
    if(!NT_SUCCESS(ntStatus))
    {
        KdPrint(("ReleaseGDTSelectors Error %x\n", ntStatus));
    }

    return ntStatus;
}