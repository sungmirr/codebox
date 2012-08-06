#include "ntddk.h"
#include "prism.h"



// external
NTSTATUS My_IoControl(PFILE_OBJECT pFileObject,
                       ULONG nIoCode,
                       PCHAR pSystemBuffer,
                       ULONG nInput,
                       ULONG nOutput,
                       ULONG *nRetrunOut);

void My_Create(PFILE_OBJECT pFileObject)
{
}

void My_Close(PFILE_OBJECT pFileObject)
{
}

VOID My_DriverEntry(IN PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT deviceObject)
{
}

VOID My_DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
}

//predefine
NTSTATUS MJFuncOp(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS MJFuncControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
VOID     MJFuncUnload(IN PDRIVER_OBJECT DriverObject);


// DriverEntry
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    NTSTATUS status;
    UNICODE_STRING NtNameString;
    UNICODE_STRING Win32NameString;
    PDEVICE_OBJECT deviceObject= NULL;
    int i;
    
    //1. Create our device name
    RtlInitUnicodeString(&NtNameString, NT_DEVICE_NAME);
    status = IoCreateDevice(DriverObject, 0, &NtNameString, FILE_DEVICE_UNKNOWN, 0,
                        FALSE, &deviceObject);
    if(!NT_SUCCESS(status))
    {
        DbgPrint("Prism: IoCreateDevice fail\n");
        return status;
    }


    //2. Setting the Major Function
    for(i=0; i <= IRP_MJ_MAXIMUM_FUNCTION; ++i)
    {
        DriverObject->MajorFunction[i] = MJFuncOp;
    }
    DriverObject->DriverUnload = MJFuncUnload;
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = MJFuncControl;

    RtlInitUnicodeString(&Win32NameString, DOS_DEVICE_NAME);
    status = IoCreateSymbolicLink(&Win32NameString, &NtNameString);

    if(!NT_SUCCESS(status))
    {
        DbgPrint("Prism: IoCreateSymbolicLink fail\n");
        IoDeleteDevice(DriverObject->DeviceObject);
        return status;
    }
    
    deviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

    My_DriverEntry(DriverObject, deviceObject);

    KdPrint(("Prism: All initialized!\n"));
    
    return status;
}

NTSTATUS MJFuncOp(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
    PIO_STACK_LOCATION CurIrpStack = NULL;
    UCHAR MajorFunction;
    PFILE_OBJECT pFileObject = NULL;

    //1. 
    CurIrpStack = IoGetCurrentIrpStackLocation(Irp);
    MajorFunction = CurIrpStack->MajorFunction;

    // 2.
    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;


    // 3. IRP_MJ_CLOSE
    if(MajorFunction == IRP_MJ_CLOSE)
    {
        pFileObject = CurIrpStack->FileObject;
        My_Close(pFileObject);
    }

    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    // 4. IRP_MJ_CREATE
    if(MajorFunction == IRP_MJ_CREATE)
    {
        pFileObject = CurIrpStack->FileObject;
        My_Create(pFileObject);
    }

    return STATUS_SUCCESS;
}

NTSTATUS MJFuncControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
    PIO_STACK_LOCATION pCurIrpStack;
    ULONG ulIoControlCode;
    PFILE_OBJECT pFileObject;
    PCHAR pInputBuffer;
    ULONG ulInputBufferLength, ulOutputBufferLength;

    NTSTATUS nReturn;
    ULONG nOutputBufferLength = 0;

    //1. Reading the InputString
    pCurIrpStack = IoGetCurrentIrpStackLocation(Irp);
    ulIoControlCode = pCurIrpStack->Parameters.DeviceIoControl.IoControlCode;
    pFileObject = pCurIrpStack->FileObject;

    //2.Getting the parameter
    pInputBuffer = (PCHAR)(Irp->AssociatedIrp.SystemBuffer);
    ulInputBufferLength = pCurIrpStack->Parameters.DeviceIoControl.InputBufferLength;
    ulOutputBufferLength = pCurIrpStack->Parameters.DeviceIoControl.OutputBufferLength;
    if(pInputBuffer == NULL)
    {
        Irp->IoStatus.Information = 0;
        Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
        return STATUS_SUCCESS;
    }

    nReturn = My_IoControl(pFileObject, ulIoControlCode, pInputBuffer, 
                    ulInputBufferLength, ulOutputBufferLength, &nOutputBufferLength);

    // Save Output Buffer
    if(nOutputBufferLength)
        Irp->IoStatus.Information = nOutputBufferLength;
    Irp->IoStatus.Status = nReturn;
    
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return STATUS_SUCCESS;
}

void MJFuncUnload(IN PDRIVER_OBJECT DriverObject)
{
    UNICODE_STRING Win32NameString;

    My_DriverUnload(DriverObject);

    RtlInitUnicodeString(&Win32NameString, DOS_DEVICE_NAME);
    IoDeleteSymbolicLink(&Win32NameString);

    IoDeleteDevice(DriverObject->DeviceObject);
    KdPrint(("Prism: Unload!!"));
}