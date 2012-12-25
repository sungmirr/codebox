#include "Archive.h"
#include <tlhelp32.h>
#include <strsafe.h>

bool Archive::SetModuleList(ULONG pid, PNX_PROCESSINFO &pi)
{
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;
    PNX_MODULEINFO mi = NULL;

    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if(hModuleSnap == INVALID_HANDLE_VALUE)
        return false;

    me32.dwSize = sizeof(MODULEENTRY32);

    if(!Module32First(hModuleSnap, &me32))
        goto $cleanup;

    do
    {
        Meminfo32 meminfo;
        PVOID addr = (PVOID)me32.modBaseAddr;
        while(meminfo.InitImageMeminfo32(me32.th32ProcessID, addr))
        {
            mi = new NX_MODULEINFO;
            if(!mi)	goto $cleanup;
			memset(mi, 0, sizeof(NX_MODULEINFO));
            mi->address = meminfo.GetBaseAddress();
			Meminfo32::ProtectToStringW(meminfo.GetProtect(), mi->szProtect, sizeof(mi->szProtect));
            Meminfo32::SizeToStringW(meminfo.GetRegionSize(), mi->szSize, sizeof(mi->szSize));
            StringCbCopyW(mi->name, sizeof(mi->name), me32.szModule);
            pi->mlist.push_back(mi);
            addr = GetPtr(addr, meminfo.GetRegionSize());
            meminfo.ClearImageMeminfo32();
        }
    }while(Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
    return true;

$cleanup:
    if(hModuleSnap != INVALID_HANDLE_VALUE)
        CloseHandle(hModuleSnap);

    //CleanupModuleList(pi);
    return false;
}


bool Archive::SetThreadList(ULONG pid, PNX_PROCESSINFO &pi)
{
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;
    PNX_THREADINFO ti = NULL;

    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); 
    if(hThreadSnap == INVALID_HANDLE_VALUE) 
        return false;

    te32.dwSize = sizeof(THREADENTRY32);

    if(!Thread32First(hThreadSnap, &te32))
        goto $cleanup;

    do
    {
        if(te32.th32OwnerProcessID == pid)
        {
            ti = new NX_THREADINFO;
            if(!ti)	goto $cleanup;
            memset(ti, 0, sizeof(NX_THREADINFO));

            ti->tid = te32.th32ThreadID;
			ThreadPriorityToStringW(GetThreadPriorityClass(ti->tid), ti->szPriority, sizeof(ti->szPriority));
            GetThreadStartAddress(ti->tid, &ti->startaddress);
            if(ti->startaddress)
            {
                Meminfo32 meminfo;
                if(meminfo.InitMeminfo32(pid, ti->startaddress))
                {
                    if(meminfo.AddressToModuleNameW(ti->modulename, sizeof(ti->modulename)))
                    {
                        pi->tlist.push_back(ti);
                        continue;
                    }
                }
            }
            StringCbCopyW(ti->modulename, sizeof(ti->modulename), L"n/a");
            pi->tlist.push_back(ti);
        }
    }while(Thread32Next(hThreadSnap, &te32));

    CloseHandle(hThreadSnap);
    return true;

$cleanup:
    if(hThreadSnap != INVALID_HANDLE_VALUE)
        CloseHandle(hThreadSnap);

    //CleanupThreadList(pi);
    return false;
}


bool Archive::SetProcessList(void)
{
    HANDLE hProcessSnap = INVALID_HANDLE_VALUE;
    PROCESSENTRY32 pe32;
    PNX_PROCESSINFO pi = NULL;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE)
        return false;
    
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if(!Process32First(hProcessSnap, &pe32))
        goto $cleanup;

    do
    {
        pi = new NX_PROCESSINFO;
        if(!pi) goto $cleanup;
        
        StringCbCopyW(pi->name, sizeof(pi->name), pe32.szExeFile);  
        pi->pid = pe32.th32ProcessID;
        pi->ppid = pe32.th32ParentProcessID;
		ProcessPriorityToStringW(GetProcessPriorityClass(pi->pid), pi->szPriority, sizeof(pi->szPriority));
        GetProcessCmdLineW(pi->pid, &pi->cmdline, NULL);

        SetThreadList(pi->pid, pi);
        SetModuleList(pi->pid, pi);
        plist.push_back(pi);
    }while(Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return true;

$cleanup:
    if(hProcessSnap != INVALID_HANDLE_VALUE)
        CloseHandle(hProcessSnap);

    CleanupProcessList();

    return false;
}

bool Archive::ProcessPriorityToStringW(DWORD priority, LPWSTR buf, size_t bufsize)
{
	if(buf == NULL || bufsize == 0)
		return false;

	LPWSTR szPriority = L"n/a";

	switch(priority)
	{
	case ABOVE_NORMAL_PRIORITY_CLASS:
		szPriority = L"ABOVE_NORMAL_PRIORITY_CLASS";
		break;
	case BELOW_NORMAL_PRIORITY_CLASS:
		szPriority = L"BELOW_NORMAL_PRIORITY_CLASS";
		break;
	case HIGH_PRIORITY_CLASS:
		szPriority = L"HIGH_PRIORITY_CLASS";
		break;
	case IDLE_PRIORITY_CLASS:
		szPriority = L"IDLE_PRIORITY_CLASS";
		break;
	case NORMAL_PRIORITY_CLASS:
		szPriority = L"NORMAL_PRIORITY_CLASS";
		break;
	case REALTIME_PRIORITY_CLASS:
		szPriority = L"REALTIME_PRIORITY_CLASS";
		break;
	}

	try
	{
		HRESULT hr = StringCbCopyW(buf, bufsize, szPriority);
		if(SUCCEEDED(hr))
			return true;

	}
	catch(...)
	{
		wprintf(L"ProtectToStringW raise exception\n");
	}

	return false;
}




bool Archive::ThreadPriorityToStringW(DWORD priority, LPWSTR buf, size_t bufsize)
{
	if(buf == NULL || bufsize == 0)
		return false;

	LPWSTR szPriority = L"n/a";

	switch(priority)
	{
	case THREAD_PRIORITY_ABOVE_NORMAL:
		szPriority = L"THREAD_PRIORITY_ABOVE_NORMAL";
		break;
	case THREAD_PRIORITY_BELOW_NORMAL:
		szPriority = L"THREAD_PRIORITY_BELOW_NORMAL";
		break;
	case THREAD_PRIORITY_HIGHEST:
		szPriority = L"THREAD_PRIORITY_HIGHEST";
		break;
	case THREAD_PRIORITY_IDLE:
		szPriority = L"THREAD_PRIORITY_IDLE";
		break;
	case THREAD_PRIORITY_LOWEST:
		szPriority = L"THREAD_PRIORITY_LOWEST";
		break;
	case THREAD_PRIORITY_NORMAL:
		szPriority = L"THREAD_PRIORITY_NORMAL";
		break;
	case THREAD_PRIORITY_TIME_CRITICAL:
		szPriority = L"THREAD_PRIORITY_TIME_CRITICAL";
		break;
	}

	try
	{
		HRESULT hr = StringCbCopyW(buf, bufsize, szPriority);
		if(SUCCEEDED(hr))
			return true;

	}
	catch(...)
	{
		wprintf(L"ProtectToStringW raise exception\n");
	}

	return false;
}


DWORD Archive::GetProcessPriorityClass(ULONG pid)
{
	DWORD priority;
	HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
	if(!h)
		return 0;

	priority = ::GetPriorityClass(h);
	CloseHandle(h);

	return priority;
}


DWORD Archive::GetThreadPriorityClass(ULONG tid)
{
	DWORD priority;
	HANDLE h = OpenThread(THREAD_QUERY_INFORMATION, FALSE, tid);
	if(!h)
		return 0;

	priority = ::GetThreadPriority(h);
	CloseHandle(h);

	return priority;
}

bool Archive::GetThreadStartAddress(ULONG tid, PVOID *address)
{
    if(!address)
        return false;

    HANDLE hThread = 0;
    PVOID ptr;
    NTSTATUS status;

    hThread = OpenThread(THREAD_QUERY_INFORMATION, FALSE, tid);
    if(!hThread)
	{
		*address = 0;
        return false;
	}

    status = pNtQIT(hThread, ThreadQuerySetWin32StartAddress, &ptr, sizeof(ptr), NULL);
    CloseHandle(hThread);

    if(!NT_SUCCESS(status))
	{
		*address = 0;
        return false;
	}

    *address = ptr;
    return true;
}


bool Archive::GetProcessCmdLineW(ULONG pid, PWCHAR *cmdline, PDWORD readed)
{
    if(!cmdline)
        return false;
  
    PWCHAR buf = NULL;
    int buflen = 0;
    HANDLE hProcess = 0;

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if(!hProcess)
        goto $cleanup;
#ifdef _WIN64
        
#else           // _WIN32
    PVOID rtlUserProcParamsAddress;
    UNICODE_STRING rtlCommandLine;
    PVOID pebaddr = GetPebAddress32(hProcess);
    if(!pebaddr)
        goto $cleanup;

    if(!ReadProcessMemory(hProcess
                    , GetPtr(pebaddr, 0x10)
                    , &rtlUserProcParamsAddress
                    , sizeof(PVOID)
                    , NULL))
    {
        goto $cleanup;
    }

    if(!ReadProcessMemory(hProcess
                        , GetPtr(rtlUserProcParamsAddress, 0x40)
                        , &rtlCommandLine
                        , sizeof(rtlCommandLine)
                        , NULL))
    {
        goto $cleanup;
    }

    buf = (PWCHAR)malloc(rtlCommandLine.Length + sizeof(WCHAR));
    memset(buf, 0, rtlCommandLine.Length + sizeof(WCHAR));

    if(!ReadProcessMemory(hProcess
                        , rtlCommandLine.Buffer
                        , buf
                        , rtlCommandLine.Length         
                        , NULL))
    {
        goto $cleanup;
    }

    
    if(readed)
        *readed = rtlCommandLine.Length;
    *cmdline = buf;

    if(hProcess)
        CloseHandle(hProcess);

    return true;
#endif

$cleanup:
    if(hProcess)
        CloseHandle(hProcess);
    if(buf)
        free(buf);
    WCHAR str[] = L"n/a";
    buflen = (wcslen(str)+1) * sizeof(WCHAR);
    buf = (PWCHAR)malloc(buflen);
    if(readed) *readed = 0;
    StringCbCopyW(buf, buflen, str);
    *cmdline = buf;

    return false;
}

PVOID Archive::GetPebAddress32(HANDLE hProcess)
{
    PROCESS_BASIC_INFORMATION32 pbi;
    pNtQIP(hProcess, ProcessBasicInformation, &pbi, sizeof(pbi), NULL);

    return pbi.PebBaseAddress;
}


PVOID64 Archive::GetPebAddress64(HANDLE hProcess)
{
    return NULL;
}

bool Archive::PrintModuleList(PNX_PROCESSINFO &pi)
{
    if(pi->mlist.empty())
        return false;

    wprintf(L"\t====================== M o d u l e   I n f o ======================\n");
    PNX_MODULEINFO mi;
    for(mit = pi->mlist.begin(); mit != pi->mlist.end(); ++mit)
    {
        mi = *mit;
		wprintf(L"%20s", mi->name);
        wprintf(L"\t0x%08x", mi->address);
        wprintf(L"\t%10s", mi->szSize);
        wprintf(L"\t%s\n", mi->szProtect);
    }

    return true;
}

bool Archive::PrintThreadList(PNX_PROCESSINFO &pi)
{
    if(pi->tlist.empty())
        return false;

    wprintf(L"\t====================== T h r e a d   I n f o ======================\n");
    PNX_THREADINFO ti;
    for(tit = pi->tlist.begin(); tit != pi->tlist.end(); ++tit)
    {
        ti = *tit;
        wprintf(L"tid : %d\n", ti->tid);
		wprintf(L"start address : 0x%08x(%s)\n", ti->startaddress, ti->modulename);
        wprintf(L"priority : %s\n\n", ti->szPriority);
    }

    return true;
}

bool Archive::PrintProcessInfo(PNX_PROCESSINFO &pi)
{
	wprintf(L"\t====================== P r o c e s s   I n f o ======================\n");
	wprintf(L"process name : %s\n", pi->name);
	wprintf(L"Command Line : %s\n", pi->cmdline);
	wprintf(L"pid          : %d\n", pi->pid);
	wprintf(L"ppid         : %d\n", pi->ppid);
	wprintf(L"priority     : %s\n\n", pi->szPriority);

	return true;
}

bool Archive::PrintProcessInfoByPid(UINT pid)
{
	PNX_PROCESSINFO p;
	for(pit = plist.begin(); pit!=plist.end(); ++pit)
	{
		p = *pit;
		if(pid == p->pid)
		{
			PrintProcessInfo(p);
			wprintf(L">>> press anykey....\n");
			getchar();
			PrintThreadList(p);
			wprintf(L">>> press anykey....\n");
			getchar();
			PrintModuleList(p);
			return true;
		}
	}

	return false;
}

bool Archive::PrintProcessList()
{
    PNX_PROCESSINFO p;
    for(pit = plist.begin(); pit!=plist.end(); ++pit)
    {
		p = *pit;
		PrintProcessInfo(p);
        PrintThreadList(p);
        PrintModuleList(p);
    }

    return true;
}


bool Archive::CleanupProcessList()
{
    try
    {
        if(plist.empty())
            return true;

        PNX_PROCESSINFO pi;
        for(pit=plist.begin(); pit!=plist.end(); ++pit)
        {
            pi = *pit;
            CleanupThreadList(pi);
            CleanupModuleList(pi);
            if(pi->cmdline)
                free(pi->cmdline);

            delete pi;
        }
#ifdef _DEBUG
        wprintf(L"CleanupProcessList success\n");
#endif
    }
    catch(...)
    {
        wprintf(L"CleanupProcessList Raise Exception\n");
        return false;
    }

    return true;
}

bool Archive::CleanupThreadList(const PNX_PROCESSINFO &pi)
{
    try
    {
        if(pi->tlist.empty())
            return true;

        for(tit=pi->tlist.begin(); tit!=pi->tlist.end();++tit)
            delete *tit;

        pi->tlist.clear();
#ifdef _DEBUG
        wprintf(L"CleanupThreadList success (pid : %d)\n", pi->pid);
#endif
    }
    catch(...)
    {
        wprintf(L"CleanupThreadList Raise Exception\n");
        return false;
    }

    return true;
}

bool Archive::CleanupModuleList(const PNX_PROCESSINFO &pi)
{
    try
    {
        if(pi->mlist.empty())
            return true;

        for(mit=pi->mlist.begin(); mit!=pi->mlist.end();++mit)
            delete *mit;

        pi->mlist.clear();
#ifdef _DEBUG
        wprintf(L"CleanupModuleList success (pid : %d)\n", pi->pid);
#endif
    }
    catch(...)
    {
        wprintf(L"CleanupThreadList Raise Exception\n");
        return false;
    }

    return true;
}


bool Archive::SetDebugPrivilege(void)
{
    HANDLE hProcessToken = NULL;
    TOKEN_PRIVILEGES OldToken;
    DWORD dwOldCount = 0;

    TOKEN_PRIVILEGES stNewToken = {0, };

    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hProcessToken))
        return false;

    if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &(stNewToken.Privileges[0].Luid)))
        return false;

    stNewToken.PrivilegeCount = 1;
    stNewToken.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if(!AdjustTokenPrivileges(hProcessToken, FALSE, &stNewToken, sizeof(TOKEN_PRIVILEGES), &OldToken, &dwOldCount))
        return false;

    return true;
}