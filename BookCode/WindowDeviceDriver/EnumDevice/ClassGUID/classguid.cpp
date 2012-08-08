/*++
    2012. 8. 2..3?
    - �ý��ۿ� ������ (Class GUID & Interface GUID����) Device Information Element�� ����
    - Class GUID�� ���, �̸� �̿� Class Name�� ��

    - SetupDiGetClassDevs
    - SetupDiDestroyDeviceInfoList
    - SetupDiEnumDeviceInfo
    - SetupDiClassNameFromGuid
 --*/

#include <windows.h>
#include <stdio.h>
#include <SetupAPI.h>
#include <tchar.h>

#pragma comment(lib, "setupapi.lib")

int _tmain(void)
{
    HANDLE hDevInfo = INVALID_HANDLE_VALUE;
    SP_DEVINFO_DATA DevInfoData;
    struct _GUID *pGuid;

    printf("�ý��ۿ� ������ ��� Device Information Element�� ã���ϴ�\n");
    hDevInfo = SetupDiGetClassDevs(NULL, 0, 0, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if(hDevInfo == INVALID_HANDLE_VALUE)
        return 0;

    int index = 0;
    while(1)
    {
        DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        BOOL bl = SetupDiEnumDeviceInfo(hDevInfo, index, &DevInfoData);
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

    SetupDiDestroyDeviceInfoList(hDevInfo);

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Device Interface�� ������ �ִ� Device Information Element�� ã���ϴ�\n");
    getchar();

    hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_PRESENT|DIGCF_ALLCLASSES|DIGCF_INTERFACEDEVICE);
    if(hDevInfo == INVALID_HANDLE_VALUE)
        return 0;

    index = 0;
    while(1)
    {
        DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        BOOL bl = SetupDiEnumDeviceInfo(hDevInfo, index, &DevInfoData);
        if(!bl)
            break;

        TCHAR ClassName[200] = {0, };
        pGuid = (struct _GUID *)&DevInfoData.ClassGuid;
        SetupDiClassNameFromGuid(pGuid, ClassName, 200, NULL);
        _tprintf(_T("[%d] CLASSNAME = %s\n"), index, ClassName);
        index++;
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);

    printf("��..����..");
    getchar();

    return 0;
}