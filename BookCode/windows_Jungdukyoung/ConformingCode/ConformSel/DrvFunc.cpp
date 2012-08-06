/*++

    MakeDrvStart
        - 드라이버의 Name으로 OpenService
        - CreateFile의 파일명 =>  \\.\Name   (DosName의 앞부분은 '.'으로 무시된다)
        - CreateFile로 얻은 핸들 리턴
        
    MakeDrvControl

    MakeDrvIoControl

 --*/


#include "stdafx.h"
#include <stdio.h>
#include "DrvFunc.h"
 

HANDLE MakeDrvSimpleStart(PTCHAR pPath, PTCHAR pName)
{
    TCHAR szPathName[MAX_PATH];
    HANDLE hHandle;

    if(pPath == NULL)
    {
        TCHAR *p;
        DWORD dwSize = (DWORD)GetModuleFileName(NULL, szPathName, sizeof(szPathName));
        if(dwSize && dwSize <= MAX_PATH)
            p = _tcsrchr(szPathName, _T('\\'));
        if(p)
            *(p+1) = _T('\0');
        _tcscat(szPathName, pName);
        _tcscat(szPathName, _T(".sys"));
    }
    else
    {
        _tcscpy(szPathName, pPath);
    }

    DWORD dwError = MakeDrvRegister(szPathName, pName);
    if(dwError && dwError != ERROR_SERVICE_EXISTS)
        return 0;
    /* Test Result - 서비스가 이미 등록되어 있으면 수정해도 의미가 없다.
	if(dwError == ERROR_SERVICE_EXISTS)
	{
		//Check and Modify the Driver Path 
		char szRegPath[256];
		char szRegKey[256];
		HKEY hKey;

		sprintf(szRegPath, "\\??\\%s", szPathName);
		sprintf(szRegKey, "SYSTEM\\CurrentControlSet\\Services\\%s", pName);
		
		dwError = RegOpenKeyEx(	HKEY_LOCAL_MACHINE,	szRegKey, 0, KEY_ALL_ACCESS, &hKey);
		if(dwError == 0)
		{
			dwError = RegSetValueEx(hKey, "ImagePath", 0, REG_EXPAND_SZ, (BYTE *)szRegPath, sizeof(szRegPath) + 1);
			RegCloseKey(hKey);
		}

	}
	*/

    hHandle = MakeDrvStart(pName);

    return hHandle;

}

DWORD MakeDrvRegister(PTCHAR pPath, PTCHAR pName)
{
    DWORD dwError = ERROR_SUCCESS;
    SC_HANDLE hSCMan = NULL;
    SC_HANDLE hService = NULL;

    // connect to local service control manager
    if ((hSCMan = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE )) == NULL) 
    {
        dwError = GetLastError();
        return dwError;
    }

    // add to service control manager's database
    if ((hService = CreateService(hSCMan, pName, pName, GENERIC_READ, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, 
        SERVICE_ERROR_NORMAL, pPath, NULL, NULL, NULL, NULL, NULL)) == NULL)
   	{
        dwError = GetLastError();
    }
    else
    { 
        CloseServiceHandle(hService);
    }

    CloseServiceHandle(hSCMan);

    return dwError;
}

DWORD MakeDrvUnRegister(PTCHAR pName)
{
    DWORD dwError = ERROR_SUCCESS;
    SC_HANDLE hSCMan = NULL;
    SC_HANDLE hService = NULL;

    // connect to local service control manager
    if ((hSCMan = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT)) == NULL)
    {
        dwError = GetLastError();
        return dwError;
    }

    // get a handle to the service
    if ((hService = OpenService(hSCMan, pName, DELETE)) != NULL)
    {
        // remove the driver
        if (!DeleteService(hService))
        {
            dwError = GetLastError();
        }		 
        CloseServiceHandle(hService);
    }
    else 
    {
        dwError = GetLastError();
    }
    CloseServiceHandle(hSCMan);

    return dwError;
}


HANDLE MakeDrvStart(LPTSTR lpDriver)
{
    DWORD dwError = ERROR_SUCCESS;
    SC_HANDLE hSCMan = NULL;
    SC_HANDLE hService = NULL;
    TCHAR	szDrvName[50];	
    HANDLE	h = 0;
    BOOL	bOpened = FALSE;

    // connect to local service control manager
    if ((hSCMan = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT)) == NULL) 
    {
        dwError = GetLastError();
        OutputDebugStringA("MakeDrvStart - OpenSCManger Error\n");
        return 0;
    }

    // get a handle to the service
    if ((hService = OpenService(hSCMan, lpDriver, SERVICE_START)) != NULL) 
    {
        bOpened = TRUE;
        // start the driver
        if (!StartService(hService, 0, NULL))
        {
            OutputDebugStringA("MakeDrvStart - Service Start Error\n");
            dwError = GetLastError();
        }

        CloseServiceHandle(hService);
    } 
    else 
    {
        char szMsg[50];

        dwError = GetLastError();
        sprintf(szMsg, "MakeDrvStart - Service Open Error(%d)\n", dwError);
        OutputDebugStringA(szMsg);		
    }

    CloseServiceHandle(hSCMan); 	  

    if(bOpened)
    {
        _stprintf(szDrvName, _T("\\\\.\\%s"), lpDriver);        // #define DOS_DEVICE_NAME     L"\\DosDevices\\ConformSel"
        h = CreateFile(szDrvName, GENERIC_READ | GENERIC_WRITE, 0, NULL, 
                    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if(h == INVALID_HANDLE_VALUE)
        {
            char szTest[50];
            sprintf(szTest, "MakeDrvStart[CreateFile Error] : Err(%d, 0x%x)", GetLastError(), GetLastError());
            OutputDebugStringA(szTest);
            return 0;
        }
    }

    return h;
}

DWORD MakeDrvStop(LPTSTR lpDriver, HANDLE hHandle)
{
    DWORD dwError = ERROR_SUCCESS;
    SC_HANDLE hSCMan = NULL;
    SC_HANDLE hService = NULL;
    SERVICE_STATUS serviceStatus;

    if(hHandle)
        CloseHandle(hHandle);

    // connect to local service control manager
    if ((hSCMan = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT)) == NULL) 
    {
        dwError = GetLastError();
        return dwError;
    }

    // get a handle to the service
    if ((hService = OpenService(hSCMan, lpDriver, SERVICE_STOP)) != NULL) 
    {
        // stop the driver
        if (!ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus))
        {
            dwError = GetLastError();
        }
        CloseServiceHandle(hService);
    } 
    else 
    {
        dwError = GetLastError();
    }

    CloseServiceHandle(hSCMan);

    return dwError;
}



/*---------------------------------------------------------------
Control Device Driver
-----------------------------------------------------------------*/
DWORD MakeDrvControl(LPTSTR lpDriver, DWORD dwCode, PVOID pInputBuffer, DWORD dwInputBufferSize, 
                     PVOID pOutputBuffer, DWORD dwOutputBufferSize)
{
    DWORD dwError = ERROR_SUCCESS;
    DWORD dwReturned;
    HANDLE hDevice;
    TCHAR szName[30];

    _stprintf(szName, _T("\\\\.\\%s"), lpDriver);

    hDevice = CreateFile(szName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if(hDevice == INVALID_HANDLE_VALUE)
    {
        dwError = GetLastError();
        return dwError;
    }

    if(!DeviceIoControl(hDevice, dwCode, pInputBuffer, dwInputBufferSize, 
                        pOutputBuffer, dwOutputBufferSize, &dwReturned, NULL))
    {
        dwError = GetLastError();
    }

    CloseHandle(hDevice);

    return dwError;
}

/*---------------------------------------------------------------
IoControl
-----------------------------------------------------------------*/
BOOL MakeDrvIoControl(HANDLE hDevice, DWORD dCode, PVOID pInput, DWORD dInput, PVOID pOutput, DWORD dOutput)
{
    DWORD dData = 0;
    BOOL bReturn;

    if(hDevice == NULL)
        return FALSE;

    if(pInput == NULL | dInput == 0)
    {
        pInput = (PVOID)&dData;
        bReturn = DeviceIoControl(hDevice, dCode, pInput, sizeof(DWORD), pOutput, dOutput, &dData, NULL)
            && (dData == dOutput);
    }
    else
    {
        bReturn = DeviceIoControl(hDevice, dCode, pInput, dInput, pOutput, dOutput, &dData, NULL)
            && (dData == dOutput);
    }

    return bReturn;
}