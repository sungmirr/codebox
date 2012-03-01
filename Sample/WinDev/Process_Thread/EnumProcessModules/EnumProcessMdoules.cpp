/*--
 *  Reference : http://msdn.microsoft.com/en-us/library/windows/desktop/ms686701(v=vs.85).aspx
 --*/

#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <tchar.h>


BOOL GetProcessList(void);
void printError( TCHAR* msg );


int wmain(void)
{
    GetProcessList();

    return 0;
}


BOOL GetProcessList(void)
{
    PROCESSENTRY32 pe32 = {sizeof(pe32)};
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE)
    {
        printError(L"CreateToolHelp32Snapshot");
        return FALSE;
    }

    if(!Process32First(hProcessSnap, &pe32))
    {
        printError(L"Process32First");
        CloseHandle(hProcessSnap);
        return FALSE;
    }

    do 
    {
        printf("\nPROCESS NAME : %S\n", pe32.szExeFile);
        printf("\tProcess ID = 0x%08x\n", pe32.th32ProcessID);
        printf("\tThread count = %d\n", pe32.cntThreads);
        printf("\tParent process ID = 0x%08x\n", pe32.th32ParentProcessID);
        printf("\tPriority class base = 0x%08x\n", pe32.pcPriClassBase);

// Retrieve the priority class.
#if 1
        DWORD dwPriorityClass = 0;
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
        //HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , FALSE, pe32.th32ProcessID);
        if(!hProcess)
            printError(L"OpenProceess");
        else
        {
            dwPriorityClass = GetPriorityClass(hProcess);
            if(!dwPriorityClass)
                printError(L"GetPriorityClass");
            CloseHandle(hProcess);
        }
        if(dwPriorityClass)
            printf("\t*Priority class = 0x%08x\n", dwPriorityClass);
#endif // end - Retrieve the priority class

                
    }while(Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);

    return TRUE;
}



void printError( TCHAR* msg )
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
