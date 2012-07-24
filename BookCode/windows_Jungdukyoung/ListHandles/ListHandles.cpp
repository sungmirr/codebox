/*++
    2012.07.24
    Native API(Nt~, Zw~) 사용을 위한 Project Setting
     - ntdll.lib(wdk설치시 생성)를 static link, nateveAPI.h(인터넷에서 다운로드) include

    
 --*/
#include <windows.h>
#define _NTDDK_
#include "nativeAPI.h"
#include <tchar.h>



void ShowErrorMessage(HRESULT hr);
BOOL EnablePrivilege(PCTSTR name);

int _tmain(int argc, TCHAR **argv)
{
    ULONG pid = 0;
    HANDLE hProcess = NULL;
    HANDLE hCurrentProcess = NULL;
    ULONG nHandles, nCount, nArraySize;
    ULONG *pULONG = NULL;
    SYSTEM_HANDLE_INFORMATION *aHandles = NULL;

    if(argc != 2)
    {
        _tprintf(_T("HELP : ListHAndles PID\n"));
        return 0;
    }
    

    try
    {
        pid = _tcstoul(argv[1], 0, 0);
        EnablePrivilege(SE_DEBUG_NAME);     // SeDebugPrivilege

        // PROCESS_DUP_HANDLE : Required to duplicate a handle using DuplicateHandle
        //      cf) PROCESS_ALL_ACCESS PROCESS_VM_OPERATION, PROCESS_VM_READ, PROCESS_VM_WRITE
        hProcess = OpenProcess(PROCESS_DUP_HANDLE, FALSE, pid);
        if(!hProcess)
            MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());

        hCurrentProcess = GetCurrentProcess();


        // Get Handle's Information
        nCount = 100;
        nArraySize = nCount * sizeof(SYSTEM_HANDLE_INFORMATION) + sizeof(ULONG);
        pULONG = (PULONG)malloc(nArraySize);
        while(ZwQuerySystemInformation(SystemHandleInformation, pULONG, 
                        nArraySize, 0) == STATUS_INFO_LENGTH_MISMATCH)
        {
            free(pULONG);
            nCount += 50;
            nArraySize = nCount * sizeof(SYSTEM_HANDLE_INFORMATION) + sizeof(ULONG);
            pULONG = (PULONG)malloc(nArraySize);
        }

        nHandles = *pULONG;
        aHandles = (PSYSTEM_HANDLE_INFORMATION)(pULONG + 1);


        // Print Handle's Information
        _tprintf(_T("Process ID : %d\n"), pid);
        for(ULONG i = 0; i < nHandles; ++i)
        {
#ifdef _DEBUG
            _tprintf(_T("[%08d]pid %d\n"), i, aHandles[i].ProcessId);
#endif
            if(aHandles[i].ProcessId == pid)
            {
                HANDLE hObject;
                OBJECT_BASIC_INFORMATION obi;
                POBJECT_TYPE_INFORMATION pOti;
                POBJECT_NAME_INFORMATION pOni;
                ULONG nTypeName, nObjectName, n;

                if(DuplicateHandle(hProcess, (HANDLE)aHandles[i].Handle,
                    hCurrentProcess, &hObject, 0, 0, DUPLICATE_SAME_ACCESS) == FALSE)
                    continue;

                ZwQueryObject(hObject, ObjectBasicInformation, &obi, sizeof(obi), &n);
                _tprintf(_T("%p %04hx %3lx %3ld %4ld "), 
                    aHandles[i].Object, aHandles[i].Handle, obi.Attributes,
                    obi.HandleCount - 1, obi.PointerCount - 2);
                //Object Type
                nTypeName = obi.TypeInformationLength + 2;
                pOti = (POBJECT_TYPE_INFORMATION)malloc(nTypeName);

                ZwQueryObject(hObject, ObjectTypeInformation, pOti, nTypeName, &nTypeName);
                _tprintf(_T("%-14.*ws "), pOti->Name.Length / 2, pOti->Name.Buffer);
                //Object Name
                nObjectName = obi.NameInformationLength == 0 
                    ? MAX_PATH * sizeof (WCHAR) : obi.NameInformationLength;

                pOni = (POBJECT_NAME_INFORMATION)malloc(nObjectName);

                if (NT_SUCCESS(ZwQueryObject(hObject, ObjectNameInformation, pOni,
                    nObjectName, &nObjectName)))
                    _tprintf(_T("%.*ws"), pOni->Name.Length / 2, pOni->Name.Buffer);

                _tprintf(_T("\n"));

                free(pOni);	free(pOti); CloseHandle(hObject);
            }
        }


   
    }
    catch(HRESULT hr)
    {
        ShowErrorMessage(hr);
    }
    catch(...)
    {
        MessageBox(0, _T("Exception raised!!!"), NULL, 0);
    }

    // cleanup
    if(hProcess)
        CloseHandle(hProcess);
    if(pULONG)
        free(pULONG);

    return 0;
}






BOOL EnablePrivilege(PCTSTR name)
{
    HANDLE hToken = NULL;
    TOKEN_PRIVILEGES priv = {1, {0, 0, SE_PRIVILEGE_ENABLED}};

    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
        return FALSE;

    LookupPrivilegeValue(0, name, &priv.Privileges[0].Luid);

    AdjustTokenPrivileges(hToken, FALSE, &priv, sizeof(priv), 0, 0);

    CloseHandle(hToken);

    if(GetLastError() != ERROR_SUCCESS)
        return FALSE;


    return TRUE;
}


void ShowErrorMessage(HRESULT hr)
{
    LPVOID lpMsgBuff = NULL;

    if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS, 
        NULL, hr, 
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
        (LPTSTR)&lpMsgBuff, 0, NULL))
    {
        MessageBox(0, _T("알 수 없는 에러가 발생했습니다."), NULL, 0);
        return;
    }

    MessageBox(0, (LPCTSTR)lpMsgBuff, NULL, 0);
    LocalFree(lpMsgBuff);
}