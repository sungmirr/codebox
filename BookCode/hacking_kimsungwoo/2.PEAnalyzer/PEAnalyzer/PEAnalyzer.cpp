#include <stdio.h>
#include <windows.h>
#include <tchar.h>



BOOL prompt(TCHAR *cmd, SIZE_T size);
void printError( TCHAR* msg );
BOOL GetPointerOfFile(TCHAR *lpFileName, LPVOID *pBasePointer);
BOOL PEAnalyzer(TCHAR *cmd);
BOOL ParsePE(LPVOID lpBasePointer);
BOOL ParseFileType(PIMAGE_NT_HEADERS pINH);


int _tmain(void)
{
    TCHAR cmd[MAX_PATH];
    if(prompt(cmd, sizeof(cmd)) == FALSE)
    {   
        printError(_T("prompt fail"));
        return 0;
    }

    
    return PEAnalyzer(cmd);
}


BOOL PEAnalyzer(TCHAR *cmd)
{
    LPVOID lpBasePointer;
    int result;

    if(!GetPointerOfFile(cmd, &lpBasePointer))
    {
        printError(_T("GetPointerOfFile fail"));
        return FALSE;
    }


    return TRUE;
}


BOOL ParsePE(LPVOID lpBasePointer)
{   
    PIMAGE_DOS_HEADER pIDH = (PIMAGE_DOS_HEADER)lpBasePointer;
    if(pIDH->e_magic != IMAGE_DOS_SIGNATURE)
    {
        _tprintf(_T("It has not PE File Format\n"));
        return FALSE;
    }

    PIMAGE_NT_HEADERS pINH = (PIMAGE_NT_HEADERS)((DWORD)lpBasePointer + pIDH->e_lfanew);
    if(pINH->Signature != IMAGE_NT_SIGNATURE)
    {
        _tprintf(_T("It has not PE File Format\n"));
        return FALSE;
    }

    ParseFileType(pINH);

   // ParseImports(lpBasePointer, pINH);
    
}

BOOL ParseFileType(PIMAGE_NT_HEADERS pINH)
{
    DWORD dwMask;

    dwMask = IMAGE_FILE_EXECUTABLE_IMAGE;
    if(pINH->FileHeader.Characteristics & dwMask)
        _tprintf(_T("File Executable\n"));

    dwMask = IMAGE_FILE_SYSTEM;
    if(pINH->FileHeader.Characteristics & dwMask)
        _tprintf(_T("File Type : System File\n"));

    dwMask = IMAGE_FILE_DLL;
    if(pINH->FileHeader.Characteristics & dwMask)
        _tprintf(_T("File Tyep : DLL\n"));

    return TRUE;
}

/*

BOOL ParseImports(LPVOID lpBasePointer, PIMAGE_NT_HEADERS pINH)
{
    
}

*/



BOOL prompt(TCHAR *cmd, SIZE_T size)
{
    _tprintf(_T("exe or dll file name : "));
    if(!_fgetts(cmd, size / sizeof(*cmd), stdin))
        return FALSE;

    // 입력값 뒤에 엔터(0a) 제거
    if(cmd[_tcslen(cmd)-1] == 0x0a)
        cmd[_tcslen(cmd)-1] = 0x00;
    return TRUE;
}

BOOL GetPointerOfFile(TCHAR *lpFileName, LPVOID *pBasePointer)
{
    BOOL ret = FALSE;
    HANDLE hFile = INVALID_HANDLE_VALUE;
    HANDLE hFileMap = NULL;
    DWORD dwSize;

    hFile = CreateFile(lpFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, NULL, NULL);
    if(hFile == INVALID_HANDLE_VALUE)
        goto $cleanup;

    hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if(hFileMap == NULL)
        goto $cleanup;
    
    dwSize = GetFileSize(hFile, NULL);
    *pBasePointer = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, dwSize);
    if(*pBasePointer == NULL)
        goto $cleanup;

    ret = TRUE;

$cleanup:
    if(hFile != INVALID_HANDLE_VALUE)
        CloseHandle(hFile);
    if(hFileMap)
        CloseHandle(hFileMap);

    return ret;

}


void printError(TCHAR* msg)
{
    DWORD eNum;
    TCHAR sysMsg[256];
    TCHAR* p;

    eNum = GetLastError( );
    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, eNum,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        sysMsg, 256, NULL );

    // Trim the end of the line and terminate it with a null
    p = sysMsg;
    while( ( *p > 31 ) || ( *p == 9 ) )
        ++p;
    do { *p-- = 0; } while( ( p >= sysMsg ) &&
        ( ( *p == '.' ) || ( *p < 33 ) ) );

    // Display the message
    _tprintf( TEXT("%s failed with error %d (%s)\n"), msg, eNum, sysMsg );
}