/*++
    2012. 8. 2..3?
    - 시스템에 부착된 (전체 & 인터페이스GUID포함) Device Information Element를 얻어와
    - Class GUID를 얻고, 이를 이용 Class Name을 얻어냄
 --*/
#include <windows.h>
#include <stdio.h>
#include <SetupAPI.h>
#include <tchar.h>

#pragma comment(lib, "setupapi.lib")


int _tmain(void)
{
    HANDLE devinfo = INVALID_HANDLE_VALUE;
    SP_DEVINFO_DATA  DevInfoData;
    struct _GUID * pGuid;               

    printf("시스템에 부착된 모든 Device Information Element를 찾습니다\n");
    devinfo = SetupDiGetClassDevs(NULL, 0, 0, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if(devinfo == INVALID_HANDLE_VALUE)
        return 0;

    int index = 0;
    while(1)
    {
        DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        BOOL bl = SetupDiEnumDeviceInfo(devinfo, index, &DevInfoData);
        if(!bl)
            break;

        // DevInfoData.ClassGuid {533C5B84-EC70-11D2-9505-00C04F79DEAF}	
        //  _GUID.Data1 = 0x533c5b84
        //  _GUID.Data2 = 0xec70
        //  _GUID.Data3 = 0x11d2
        TCHAR ClassName[200] = {0, };
        pGuid = (struct _GUID*)&DevInfoData.ClassGuid;
        SetupDiClassNameFromGuid(pGuid, ClassName, 200, NULL);
        
        _tprintf(_T("[%d] CLASSNAME = %s\n"), index, ClassName);

        index++;
    }

    SetupDiDestroyDeviceInfoList(devinfo);

    //////////////////////////////////////////////////////////////////////////////////////////////////

    printf("Device Interface를 가지고 있는 Device Information Element를 찾습니다\n");
    getchar();

    devinfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_PRESENT|DIGCF_ALLCLASSES|DIGCF_INTERFACEDEVICE);
    if(devinfo == INVALID_HANDLE_VALUE)
        return 0;

    index = 0;
    while(1)
    {
        DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        BOOL bl = SetupDiEnumDeviceInfo(devinfo, index, &DevInfoData);
        if(!bl)
            break;

        TCHAR ClassName[200] = {0, };
        pGuid = (struct _GUID *)&DevInfoData.ClassGuid;
        SetupDiClassNameFromGuid(pGuid, ClassName, 200, NULL);
        _tprintf(_T("[%d] CLASSNAME = %s\n"), index, ClassName);
        index++;
    }

    SetupDiDestroyDeviceInfoList(devinfo);

    printf("끝..엔터..");
    getchar();


    return 0;
}