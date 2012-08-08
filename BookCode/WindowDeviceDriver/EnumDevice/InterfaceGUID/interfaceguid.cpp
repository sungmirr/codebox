/*++
    2012. 8. 8..9?
    - SetupDiGetClassDevs : 특정 pGuid의 HDEVINFO를 얻는다
    - SetupDiEnumDeviceInterfaces
    - SetupDiGetDeviceInterfaceDetail : pGuid의 특정 index 인터페이스 이름을 얻어돈다
 --*/

#include <windows.h>
#include <SetupAPI.h>
#include <stdio.h>
#include <tchar.h>
#include "interfaceguid.h"

#pragma comment(lib, "setupapi.lib")

int GetDeviceStackNameCount( struct _GUID * pGuid );
BOOL GetDeviceStackName( struct _GUID * pGuid, TCHAR ** ppDeviceName, int index );

int _tmain(void)
{
    int devCount = 0;
    int GuidCount = 0;
    struct _GUID *pGuid;
    while(1)
    {
        if(GlobalGuid[GuidCount] == NULL)
            break;

        pGuid = GlobalGuid[GuidCount];
        GuidCount++;

        printf("%S", GlobalString[GuidCount]);
        printf("유형의 장치를 찾았습니다\n");

        devCount = GetDeviceStackNameCount(pGuid);
        if(devCount)
        {
            printf("설치된 해당하는 Interface유형의 디바이스(s)를 %d개 찾았습니다\n", devCount);
            printf("---------------------------------------------------------\n");
        }
        else
        {
            printf("설치된 해당하는 Interface유형의 디바이스(s)를 찾지 못했습니다\n\n");
        }

        for(int i=0; i < devCount; ++i)
        {
            TCHAR *pDeviceName;
            BOOL bRet = GetDeviceStackName(pGuid, &pDeviceName, i);
            _tprintf(_T("Device name is \"%s\"\n"), pDeviceName);

            HANDLE hDev = CreateFile(pDeviceName, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, NULL,
                                OPEN_EXISTING, 0, NULL);
            if(hDev == INVALID_HANDLE_VALUE)
            {
                printf("디바이스를 열지 못했습니다\n");
            }
            else
            {
                printf("디바이스를 성공적으로 열었습니다\n");
                CloseHandle(hDev);
            }
            free( pDeviceName );
            printf("\n");
        }

        getchar();
    }
    
    return 0;
}

int GetDeviceStackNameCount( struct _GUID * pGuid )
{
    HDEVINFO hDev;
    SP_INTERFACE_DEVICE_DATA interfaceData;
    int devCount = 0;

    // 특정 pGuid의 HDEVINFO를 얻는다
    //  cf)HDEVINFO DeviceInfo = SetupDiGetClassDevs(NULL, _T("USB"),
    //                            0, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    hDev = SetupDiGetClassDevs(pGuid, 0, 0, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
    if(hDev == INVALID_HANDLE_VALUE)
        return 0;

    interfaceData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
    while(1)
    {
        BOOL bl;
        bl = SetupDiEnumDeviceInterfaces(hDev, 0, (struct _GUID*)pGuid, devCount, &interfaceData);
        if(!bl)
            break;

        devCount++;
    }

    SetupDiDestroyDeviceInfoList(hDev);

    return devCount;
}

BOOL GetDeviceStackName( struct _GUID * pGuid, TCHAR ** ppDeviceName, int index )
{
    HDEVINFO hDev;
    SP_INTERFACE_DEVICE_DATA interfaceData;
    PSP_INTERFACE_DEVICE_DETAIL_DATA pInterfaceDetailData;

    *ppDeviceName = NULL;
    hDev = SetupDiGetClassDevs(pGuid, 0, 0, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
    if(hDev == INVALID_HANDLE_VALUE)
        return FALSE;
    
    interfaceData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
    BOOL bRet = SetupDiEnumDeviceInterfaces(hDev, NULL, pGuid, index, &interfaceData);
    if(bRet == FALSE)
        return FALSE;

    DWORD size = 0;
    SetupDiGetDeviceInterfaceDetail(hDev, &interfaceData, 0, 0, &size, 0);
    pInterfaceDetailData = (PSP_INTERFACE_DEVICE_DETAIL_DATA)malloc(size);
    pInterfaceDetailData->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
    SetupDiGetDeviceInterfaceDetail(hDev, &interfaceData, pInterfaceDetailData, size, 0, 0);

    *ppDeviceName = (TCHAR *)malloc((_tcslen(pInterfaceDetailData->DevicePath) + 1) * sizeof(TCHAR));
    memset(*ppDeviceName, 0, _tcslen(pInterfaceDetailData->DevicePath)*sizeof(TCHAR));
    _tcscpy(*ppDeviceName, pInterfaceDetailData->DevicePath);
    free(pInterfaceDetailData);

    SetupDiDestroyDeviceInfoList(hDev);

    return TRUE;
}