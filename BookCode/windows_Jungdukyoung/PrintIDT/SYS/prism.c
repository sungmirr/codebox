#include "ntddk.h"
#include "Prism.h"

//[External]------------------------------------------------------------------------------
VOID My_DriverEntry(IN PDRIVER_OBJECT DriverObject ,PDEVICE_OBJECT deviceObject);
VOID My_DriverUnload(IN PDRIVER_OBJECT DriverObject);
NTSTATUS My_IoControl(PFILE_OBJECT pFileObject, ULONG nIoCode, PCHAR pSystemBuffer, ULONG nInput, ULONG nOutput, ULONG *nReturnOut);

void My_Create(PFILE_OBJECT pFileObject)
{
}

void My_Close(PFILE_OBJECT pFileObject)
{
}


//[PreDefine]------------------------------------------------------------------------------
NTSTATUS MJFuncControl ( IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp );
VOID	 MJFuncUnload( IN PDRIVER_OBJECT DriverObject );
NTSTATUS MJFuncOp(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);

/*--------------------------------------------------------------------------------
DriverEntry
--------------------------------------------------------------------------------*/
NTSTATUS DriverEntry( IN PDRIVER_OBJECT DriverObject , IN PUNICODE_STRING RegistryPath )
{
    PDEVICE_OBJECT	deviceObject = NULL;
    NTSTATUS	status;
    UNICODE_STRING	NtNameString;
    UNICODE_STRING	Win32NameString;
    PFAST_IO_DISPATCH fastIoDispatch;	
    int i;


    //1. Create our device name.	
    RtlInitUnicodeString ( &NtNameString , NT_DEVICE_NAME );		
    status = IoCreateDevice ( DriverObject , 0 , &NtNameString , FILE_DEVICE_UNKNOWN, 0, FALSE , &deviceObject );       
    if (!NT_SUCCESS(status)) 
    {
        DbgPrint( ("Prism: Create Fail : IoCreateDevice!\n") );
        return status;
    }	

    //2. Setting the Major Function
    for (i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++) 
    {
        DriverObject->MajorFunction[i] = MJFuncOp;
    }
    DriverObject ->DriverUnload = MJFuncUnload;
    DriverObject ->MajorFunction[IRP_MJ_DEVICE_CONTROL] = MJFuncControl;

    //3. Create Symbolic Link
    RtlInitUnicodeString ( &Win32NameString , DOS_DEVICE_NAME );	
    status = IoCreateSymbolicLink ( &Win32NameString , &NtNameString );

    if ( !NT_SUCCESS (status) )
    {
        DbgPrint( ("Prism: Create Fail : IoCreateSymbolicLink!\n") );
        IoDeleteDevice ( DriverObject ->DeviceObject );
        return status;
    }

    deviceObject->Flags &= ~DO_DEVICE_INITIALIZING;  

    //
    My_DriverEntry(DriverObject, deviceObject);
    //	
    KdPrint ( ("Prism: All initialized!\n") );	
    return status;
}

/*--------------------------------------------------------------------------------
MJFuncOp
--------------------------------------------------------------------------------*/
NTSTATUS MJFuncOp(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
    PIO_STACK_LOCATION CurIrpStack = IoGetCurrentIrpStackLocation(Irp);	
    PFILE_OBJECT pFileObject;
    UCHAR MajorFunction = CurIrpStack->MajorFunction;	

    //1.
    Irp ->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;

    if(MajorFunction == IRP_MJ_CLOSE)
    {
        pFileObject = CurIrpStack->FileObject;
        My_Close(pFileObject);
    }

    IoCompleteRequest( Irp, IO_NO_INCREMENT );

    if(MajorFunction == IRP_MJ_CREATE)
    {
        pFileObject = CurIrpStack->FileObject;
        My_Create(pFileObject);
    }

    return STATUS_SUCCESS;
}

/*--------------------------------------------------------------------------------
MJFuncControl
--------------------------------------------------------------------------------*/
NTSTATUS MJFuncControl (IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{	
    ULONG ulIoControlCode;
    PIO_STACK_LOCATION pCurIrpStack;	    
    PCHAR pInputBuffer;
    ULONG ulInputBufferLength, ulOutputBufferLength;    
    PDEVICE_OBJECT pDevObj;			
    ULONG ulInputBuffer;
    NTSTATUS	nReturn = STATUS_SUCCESS;	
    ULONG 	nOutputBufferLength = 0;
    PFILE_OBJECT pFileObject;
    //2. Reading the InputString
    pCurIrpStack = IoGetCurrentIrpStackLocation( Irp );    
    ulIoControlCode = pCurIrpStack -> Parameters.DeviceIoControl.IoControlCode;
    pFileObject = pCurIrpStack->FileObject;

    pInputBuffer = (PCHAR) (Irp -> AssociatedIrp.SystemBuffer);
    ulInputBufferLength = pCurIrpStack -> Parameters.DeviceIoControl.InputBufferLength;
    ulOutputBufferLength = pCurIrpStack -> Parameters.DeviceIoControl.OutputBufferLength;
    if( pInputBuffer == NULL )
    {
        Irp -> IoStatus.Information = 0;
        Irp -> IoStatus.Status = STATUS_INVALID_PARAMETER;
        return STATUS_SUCCESS;  
    }

    nReturn = My_IoControl(pFileObject, ulIoControlCode, pInputBuffer, ulInputBufferLength, ulOutputBufferLength, &nOutputBufferLength);

    //Save Output Buffer
    if(nOutputBufferLength)
        Irp->IoStatus.Information = nOutputBufferLength;
    Irp -> IoStatus.Status = nReturn;

    IoCompleteRequest( Irp, IO_NO_INCREMENT );	
    return STATUS_SUCCESS;  
}


/*--------------------------------------------------------------------------------
MJFuncUnload
--------------------------------------------------------------------------------*/
void MJFuncUnload ( IN PDRIVER_OBJECT DriverObject )
{
    UNICODE_STRING Win32NameString;

    My_DriverUnload(DriverObject);

    RtlInitUnicodeString ( &Win32NameString , DOS_DEVICE_NAME );	
    IoDeleteSymbolicLink ( &Win32NameString );	

    IoDeleteDevice ( DriverObject -> DeviceObject );
    KdPrint( ("Prism: Unloaded!!\n" ) );	
}