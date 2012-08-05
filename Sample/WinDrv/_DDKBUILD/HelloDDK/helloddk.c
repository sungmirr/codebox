#include "ntddk.h"

VOID OnUnload(IN PDRIVER_OBJECT DriverObject)
{
    DbgPrint("OnUnload called\n");
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    DbgPrint("Hello, world!!\n");
    DriverObject->DriverUnload = OnUnload;
    return STATUS_SUCCESS;
}