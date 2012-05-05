#include <windows.h>
#include <tchar.h>

#define BLOCK_LEN 65536

void ShowErrorMessage(HRESULT hr);

int _tmain(int argc, TCHAR **argv)
{
    if(argc != 3)
    {
        _tprintf(_T("mmf_filecopy.exe <source> <target>\n"));
        return 0;
    }

    LPCTSTR szSource = argv[1];
    LPCTSTR szTarget = argv[2];

    HANDLE hSource = INVALID_HANDLE_VALUE;
    HANDLE hMapSource = NULL;
    PVOID pSource = NULL;

    HANDLE hTarget = INVALID_HANDLE_VALUE;
    HANDLE hMapTarget = NULL;
    PVOID pTarget = NULL;

    try
    {
#if 0
        PINT p = NULL;
        *p = 10;
#endif

        hSource = CreateFile(szSource, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
        if(hSource == INVALID_HANDLE_VALUE)
            throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());

        hTarget = CreateFile(szTarget, GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, 0, NULL);
        if(hTarget == INVALID_HANDLE_VALUE)
            throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());

        DWORD dwFileSize = GetFileSize(hSource, NULL);
        // ���εǴ� VM������ �Ӽ����� ���⼭ ����!!!! Read
        hMapSource = CreateFileMapping(hSource, NULL, PAGE_READONLY, 0, dwFileSize, NULL);
        if(!hMapSource)
            throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());

        // ���εǴ� VM������ �Ӽ����� ���⼭ ����!!!! ReadWrite
        hMapTarget = CreateFileMapping(hTarget, NULL, PAGE_READWRITE, 0, dwFileSize, NULL);
        if(!hMapTarget)
            throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());
        
        DWORD dwCopyLength = BLOCK_LEN;
        DWORD dwTransferred = 0;
        while(dwTransferred < dwFileSize)
        {
            dwCopyLength = dwFileSize - dwTransferred;
            if(dwCopyLength >= BLOCK_LEN)
                dwCopyLength = BLOCK_LEN;

            /// MapViewOfFile�� �����Ű�� VM������ szSource�� ����(offset dwTrasferred���� dwCopyLength)�� ���εȴ�. 
            /// ���ε� Address ����!!!
            pSource = MapViewOfFile(hMapSource, FILE_MAP_READ, 0, dwTransferred, dwCopyLength);
            if(!pSource)
                throw MAKE_HRESULT(1, FACILITY_WIN32, GetLastError());

            pTarget = MapViewOfFile(hMapTarget, FILE_MAP_WRITE, 0, dwTransferred, dwCopyLength);

            CopyMemory(pTarget, pSource, dwCopyLength);

            dwTransferred += dwCopyLength;

            // VM�������� �縮���� => ������ ���� �ȴ�.
            if(pSource)
                UnmapViewOfFile(pSource);
            if(pTarget)
                UnmapViewOfFile(pTarget);
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
    

    
    if(pSource)
        UnmapViewOfFile(pSource);
    if(hMapSource)
        CloseHandle(hMapSource);
    if(hSource != INVALID_HANDLE_VALUE)
        CloseHandle(hSource);

    if(pTarget)
        UnmapViewOfFile(pTarget);
    if(hMapTarget)
        CloseHandle(hMapTarget);
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
        MessageBox(0, _T("�� �� ���� ������ �߻��߽��ϴ�."), NULL, 0);
        return;
    }

    MessageBox(0, (LPCTSTR)lpMsgBuff, NULL, 0);
    LocalFree(lpMsgBuff);
}