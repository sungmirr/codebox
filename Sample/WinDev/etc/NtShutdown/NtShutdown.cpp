/*++
    2012. 7. 24 23:20
    - Windows NT�ý����� Shutdown��Ű�� ���α׷�
    
    ref : http://support.microsoft.com/kb/601349/ko
          http://msdn.microsoft.com/en-us/library/windows/desktop/aa376871(v=vs.85).aspx


    Windows NT�� Shutdown�ϴ� ���μ����� SE_PRIVILEGE_ENABLED������ ������ �־�� �Ѵ�
    ExitWindowsEx�� ȣ���ϱ� ���� SE_PRIVILEGE_ENABLED���� ȹ��
 --*/

#include <windows.h>
#include <tchar.h>

BOOL MySystemShutdown()
{
    HANDLE hToken = NULL;
    TOKEN_PRIVILEGES tkp;

    // Get a token for this process
    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        return FALSE;


    // Get the LUID for the shutdown privilege
    // LUID(Locally Unique Identifier)
    //   - used on a specified system to locally represent the specified privilege name
    // LookupPrivilegeValue - retrieve the LUID
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1; // one privilege to set
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // Get the shutdown privilege for this process
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

    if(GetLastError() != ERROR_SUCCESS)
        return FALSE;

    // shut down the system and force all applications to close
    if(!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
                    SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
                    SHTDN_REASON_MINOR_UPGRADE |
                    SHTDN_REASON_FLAG_PLANNED)) 
        return FALSE;

    return TRUE;
}

int _tmain(void)
{
    if(!MySystemShutdown())
        _tprintf(_T("shutdown fail"));
    else
        _tprintf(_T("shutdown success"));

    return 0;
}