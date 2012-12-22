/*++
    2012. 11. 22
    
    Property_32_64.exe
     - 현재 프로세스가 32bit인지 64bit인지 확인
        => 64bit : _WIN64, 32bit and WOW : _WIN32
        => #ifdef _WIN64
           // do something
           #else
           // do something
           #endif

     - 실행 되는 환경이 x86인지 x64인지 확인
        => GetNativeSystemInfo로 확인

     - 실행 환경이 x64이면 입력받은 pid의 프로세스가 64bit process인지 WOW process인지 확인
       => wow process : NtQueryInformationProcess(ProcessWow64Information)으로 확인
       => 64bit process인지 확인 법 :  실행환경이 x64이고 wowprocess가 아니면

     - 32bit와 64bit의 자료형의 길이 확인


    <reference>
    Predefined Macros : http://msdn.microsoft.com/en-us/library/b0084kay(v=vs.80).aspx
    Version Info : http://msdn.microsoft.com/en-us/library/windows/desktop/ms724429(v=vs.85).aspx


--*/
#include <windows.h>
#include <stdio.h>

void displayPrcessorInfo(SYSTEM_INFO &stInfo);
bool WINAPI NxIsProcessWow64(HANDLE hProcess);
bool WINAPI NxIsProcess64(HANDLE hProcess);
BOOL SetDebugPrivilege(HANDLE *phProcessToken, TOKEN_PRIVILEGES *pOldToken, DWORD *pdwOldCount);


typedef NTSTATUS (NTAPI *_NtQueryInformationProcess)(
    HANDLE ProcessHandle,
    DWORD ProcessInformationClass,
    PVOID ProcessInformation,
    DWORD ProcessInformationLength,
    PDWORD ReturnLength
    );

#define ProcessWow64Information 26
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

int main(void)
{
#ifdef _WIN64
    printf("_WIN64 defined\n");
#endif

#ifdef _WIN32
    printf("_WIN32 defined\n");
#endif

#ifdef _M_IX86
    printf("_M_IX86 defined\n");
#endif

#ifdef _M_IA64
    printf("_M_IA64 defined\n");
#endif
        


    //////////////////////////////////////////////////
    SYSTEM_INFO stInfo;
    GetSystemInfo( &stInfo );
    displayPrcessorInfo(stInfo);

    GetNativeSystemInfo( &stInfo );
    displayPrcessorInfo(stInfo);

    ///////////////////////////////////////////////////

    printf("input pid : ");
    char str[100];
    gets(str);
    DWORD pid = atoi(str);

    HANDLE hProcessToken = NULL;
    TOKEN_PRIVILEGES stOldToken = {0, };
    DWORD dwOldCount = 0;
    HANDLE hProcess;

    if(!SetDebugPrivilege(&hProcessToken, &stOldToken, &dwOldCount))
    {
        printf("SetDebugPrivilege");
        return FALSE;
    }

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if(!hProcess)
    {
        printf("Could not read CommandLine!\n");
        return FALSE;
    }

   
    if(NxIsProcessWow64(hProcess))
    {
        printf("NxIsProcessWow64 true\n");
    }
    else
    {
        printf("NxIsProcessWow64 false\n");
    }


    /////////////////////////////////////////////////////////////////////////

    printf ("\n-- General Data Type Size --\n");
    printf ("char size : %d byte\n", (int)sizeof(char));
    printf ("short size : %d byte\n", (int)sizeof(short));
    printf ("int size : %d byte\n", (int)sizeof(int));
    printf ("long size : %d byte\n", (int)sizeof(long));
    printf ("double size : %d byte\n", (int)sizeof(double));
    printf ("long double size : %d byte\n", (int)sizeof(long double));

    printf ("\n-- Pointer Data Type Size -- \n");
    printf ("char* size : %d byte\n", (int)sizeof(char*));
    printf ("short* size : %d byte\n", (int)sizeof(short*));
    printf ("int* size : %d byte\n", (int)sizeof(int*));
    printf ("long* size : %d byte\n", (int)sizeof(long*));
    printf ("double* size : %d byte\n", (int)sizeof(double*));
    printf ("long double* size : %d byte\n", (int)sizeof(long double*));


    return 0;
}


void displayPrcessorInfo(SYSTEM_INFO &stInfo) 
{
    switch(stInfo.wProcessorArchitecture)
    {
    case PROCESSOR_ARCHITECTURE_INTEL:
        printf( "Processor Architecture: Intel x86\n");
        break;
    case PROCESSOR_ARCHITECTURE_IA64:
        printf( "Processor Type: Intel x64\n");
        break;
    case PROCESSOR_ARCHITECTURE_AMD64:
        printf( "Processor Type: AMD 64\n");
        break;
    default:
        printf( "Unknown processor architecture\n");
    }
}


bool 
WINAPI
NxIsProcessWow64(HANDLE hProcess)
{
    NTSTATUS s;
    size_t w64;
    ULONG readed;

    _NtQueryInformationProcess pfnNtQueryInformationProcess;
    HMODULE hMod = GetModuleHandleA("ntdll.dll");
    pfnNtQueryInformationProcess = (_NtQueryInformationProcess)GetProcAddress(hMod, "NtQueryInformationProcess");
    if(!pfnNtQueryInformationProcess)
    {
        printf("GetProcAddress fail\n");
        return false;
    }

    s = pfnNtQueryInformationProcess(hProcess, ProcessWow64Information, &w64, sizeof(w64), &readed);
    if(!NT_SUCCESS(s))
        return false;

    if(w64)
        return true;

    return false;
}




BOOL SetDebugPrivilege(HANDLE *phProcessToken, TOKEN_PRIVILEGES *pOldToken, DWORD *pdwOldCount)
{
    TOKEN_PRIVILEGES stNewToken = {0, };

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, phProcessToken))
    {
        //wprintf(L"OpenProcessToken\n");
        return FALSE;
    }

    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &(stNewToken.Privileges[0].Luid)))
    {
        //wprintf(L"LookupPrivilegeValue\n");
        return FALSE;
    }

    stNewToken.PrivilegeCount = 1;
    stNewToken.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(*phProcessToken, FALSE, &stNewToken, sizeof(TOKEN_PRIVILEGES), pOldToken, pdwOldCount))
    {
        //wprintf(L"AdjustTokenPrivileges");
        return FALSE;
    }

    return TRUE;
}
