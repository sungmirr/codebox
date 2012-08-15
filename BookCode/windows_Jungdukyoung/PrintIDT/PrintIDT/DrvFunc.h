#ifndef _DRVFUNC_H_
#define _DRVFUNC_H_

#include <winsvc.h>
#include <winioctl.h>
#include <windows.h>
#include <tchar.h>

HANDLE MakeDrvSimpleStart(PTCHAR pPath, PTCHAR pName);
DWORD MakeDrvRegister(PTCHAR pPath, PTCHAR pName);
DWORD MakeDrvUnRegister(PTCHAR pName);
HANDLE MakeDrvStart(LPTSTR lpDriver);
DWORD MakeDrvStop(LPTSTR lpDriver, HANDLE hHandle);
DWORD MakeDrvControl(LPTSTR lpDriver, DWORD dwCode, PVOID pInputBuffer, DWORD dwInputBufferSize,
                     PVOID pOutputBuffer, DWORD dwOutputBufferSize);
BOOL MakeDrvIoControl (HANDLE hDevice, DWORD dCode, PVOID  pInput, DWORD  dInput, PVOID  pOutput, DWORD  dOutput);

#endif