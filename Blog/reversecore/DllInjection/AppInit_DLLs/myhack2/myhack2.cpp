#include <windows.h>
#include <tchar.h>


#define DEF_CMD _T("C:\\Program Files\\Internet Explorer\\iexplorer.exe")
#define DEF_ADDR _T("www.naver.com")
#define DEF_DST_PROC _T("notepad.exe")

BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved)
{
    TCHAR szCmd[MAX_PATH] = {0, };
    TCHAR szPath[MAX_PATH] = {0, };
    TCHAR *szProcess = NULL;
    STARTUPINFO si = {0, };
    PROCESS_INFORMATION pi ={0, };


    // wSHowWindow�Ӽ����� ��ȿ �Ϸ���, dwFlags�� STARTF_USESHOWWINDOW ����
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    switch(fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        //* �������� DLL�� �����ǵǱ� ������ Ư�����μ��������� �����ϰ� ���͸�
        if(!GetModuleFileName(NULL, szPath, MAX_PATH))
            break;
        if(!(szProcess = _tcsrchr(szPath, _T('\\'))))
            break;
        szProcess++;
        if(_tcsicmp(szProcess, DEF_DST_PROC))
            break;
        //*********************************//

        _tprintf_s(szCmd, _T("%s %s"), DEF_CMD, DEF_ADDR);
        if(!CreateProcess(NULL, szCmd, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS,
                            NULL, NULL, &si, &pi))
                            break;

        if(pi.hProcess)
            CloseHandle(pi.hProcess);

        break;
    }

    return TRUE;
}