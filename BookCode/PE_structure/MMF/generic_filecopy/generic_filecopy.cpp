#include <windows.h>
#include <stdio.h>
#include <tchar.h>


#define BLOCK_LEN 65536

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * <2012. 5. 6 00:24>
 * Code Template
 *  - HANDLE 초기화,해제& Exception & Error Message
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if 0
void ShowErrorMessage(HRESULT hr);

int  _tmain(int argc, TCHAR **argv)
{
    if(argc != 3)
    {
        _tprintf(_T("generic_filecopy.exe <source> <target>\n"));
        return 0;
    }

    LPCTSTR szSource = argv[1];
    LPCTSTR szTarget = argv[2];

    HANDLE hSource = INVALID_HANDLE_VALUE;
    HANDLE hTarget = INVALID_HANDLE_VALUE;

    try
    {
        hSource = CreateFile(szSource, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
        if(hSource == INVALID_HANDLE_VALUE)
            ///// 1.
            throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());    

    }
    catch(HRESULT hr)
    {
        ///// 2.
        ShowErrorMessage(hr);
    }

    ///// 3.
    if(hSource != INVALID_HANDLE_VALUE)
        CloseHandle(hSource);
    if(hTarget != INVALID_HANDLE_VALUE)
        CloseHandle(hTarget);

    return 0;
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
        MessageBox(0, "알 수 없는 에러가 발생했습니다.", NULL, 0);
        return;
    }

    MessageBox(0, (LPCTSTR)lpMsgBuff, NULL, 0);
    LocalFree(lpMsgBuff);
}
#endif



void ShowErrorMessage(HRESULT hr);

int  _tmain(int argc, TCHAR **argv)
{
    if(argc != 3)
    {
        _tprintf(_T("generic_filecopy.exe <source> <target>\n"));
        return 0;
    }

    LPCTSTR szSource = argv[1];
    LPCTSTR szTarget = argv[2];

    HANDLE hSource = INVALID_HANDLE_VALUE;
    HANDLE hTarget = INVALID_HANDLE_VALUE;

    try
    {
        hSource = CreateFile(szSource, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
        if(hSource == INVALID_HANDLE_VALUE)
            throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());

        hTarget = CreateFile(szTarget, GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, 0, NULL);
        if(hTarget == INVALID_HANDLE_VALUE)
            throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());

        BYTE pBuff[BLOCK_LEN];
        DWORD dwFileSize = GetFileSize(hSource, NULL);
        DWORD dwCopyLength = BLOCK_LEN;
        DWORD dwTrasferred = 0;
        DWORD dwReadBytes = 0;
        DWORD dwWroteBytes = 0;

        while(dwTrasferred < dwFileSize)
        {
            dwCopyLength = dwFileSize - dwTrasferred;
            if(dwCopyLength >= BLOCK_LEN)
                dwCopyLength = BLOCK_LEN;

            if(!ReadFile(hSource, pBuff, dwCopyLength, &dwReadBytes, NULL))
                MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());

            if(!WriteFile(hTarget, pBuff, dwCopyLength, &dwWroteBytes, NULL))
                MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());

            dwTrasferred += dwCopyLength;
        }

    }
    catch(HRESULT hr)
    {
        ShowErrorMessage(hr);
    }
    catch(...)
    {
        MessageBox(0, _T("Raise exception!!!"), NULL, 0);
    }

    if(hSource != INVALID_HANDLE_VALUE)
        CloseHandle(hSource);
    if(hTarget != INVALID_HANDLE_VALUE)
        CloseHandle(hTarget);

    return 0;
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