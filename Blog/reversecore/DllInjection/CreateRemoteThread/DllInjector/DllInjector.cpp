#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

//#define _WIN32_WINNT _WIN32_WINNT_WS03
/* OpenProcess(PRCOSS_ALL_ACCESS, );
 *	http://stackoverflow.com/questions/2285878/c-elevating-privileges-on-an-exe-using-openprocess
 *  http://msdn.microsoft.com/en-us/library/windows/desktop/ms684880(v=vs.85).aspx
 *  http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745(v=vs.85).aspx
 */


DWORD FindProcessID(LPCTSTR szProcessName);
BOOL InjectDll(DWORD pid, LPCTSTR szDllName);


int _tmain(int argc, TCHAR **argv)
{
    if(argc != 3)
    {
        printf("DllInjector.exe <target-process> <dll-name>\n");
        return 0;
    }

    DWORD pid;
    pid = FindProcessID(argv[1]);
    _tprintf(_T("%s pid is %d\n"), argv[1], pid);
    if(!pid)
    {
        printf("FindProcessID fail\n");
        return 0;
    }

    InjectDll(pid, argv[2]);
    return 0;
}


//return - pid, 실패시 0리턴
DWORD FindProcessID(LPCTSTR szProcessName)
{
    HANDLE hSnapShot = INVALID_HANDLE_VALUE;
    PROCESSENTRY32 pe = { sizeof(pe) };

    hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    Process32First(hSnapShot, &pe);
    do 
    {
        if(!_tcsicmp(pe.szExeFile, szProcessName))
        {
            CloseHandle(hSnapShot);
            return pe.th32ProcessID;
        }
    } while (Process32Next(hSnapShot, &pe));

    CloseHandle(hSnapShot);
    return 0;
}


BOOL InjectDll(DWORD pid, LPCTSTR szDllName)
{
    HANDLE hProcess = NULL;
    HANDLE hThread = NULL;
    LPVOID pRemoteBuf = NULL;           // LoadLibray의 인자값. dll파일명
    DWORD dwBufsize = (_tcslen(szDllName) + 1) * sizeof(TCHAR);
    LPTHREAD_START_ROUTINE pThreadProc; // LoadLibaray함수의 주소     

    // CreateRemoteThred function causes a new thread of execution to begin in the address
    // if the specified process. The thread has access to all objects that the process opens
    //hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    hProcess = OpenProcess(STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFF, FALSE, pid);
    //hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, pid);
    if(!hProcess) { printf("OpenProcess fail 0x%08x\n", GetLastError()); return FALSE; }

    pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufsize, MEM_COMMIT, PAGE_READWRITE);
    if(!pRemoteBuf) { printf("VirautlAllocEx fail 0x%08x\n", GetLastError()); return FALSE; }
    
    WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)szDllName, dwBufsize, NULL);

#ifdef _UNICODE
    pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "LoadLibraryW");
#else
    pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "LoadLibraryA");
#endif

    
    hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, pRemoteBuf, 0, NULL);
    if(!hThread) { printf("CreateRemoteThread fail 0x%08x\n", GetLastError()); return FALSE; }
    printf("CreateRemoteThread - LoadLibray : %08x, pRemoteBuf : %08x", pThreadProc, pRemoteBuf);
    WaitForSingleObject(hThread, INFINITE);

    CloseHandle(hThread);
    CloseHandle(hProcess);
    
    return TRUE;
}