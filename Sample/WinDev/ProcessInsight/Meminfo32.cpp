#include "Meminfo32.h"


bool Meminfo32::InitMeminfo32(ULONG pid, LPCVOID address)
{
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, pid);
    if(!hProcess)
        return false;

    if(!VirtualQueryEx(hProcess, address, &mbi, sizeof(mbi)))
    {
        CloseHandle(hProcess);
        hProcess = NULL;
        return false;
    }

    ready = true;
    return true;
}

bool Meminfo32::InitImageMeminfo32(ULONG pid, LPCVOID address)
{
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, pid);
    if(!hProcess)
        return false;

    if(!VirtualQueryEx(hProcess, address, &mbi, sizeof(mbi)))
        goto $clenaup;

    if(mbi.Type != MEM_IMAGE)
        goto $clenaup;

    ready = true;
    return true;

$clenaup:
    CloseHandle(hProcess);
    hProcess = NULL;
    return false;
}

PVOID Meminfo32::GetAllocationAddress()
{
    if(!ready)
        return NULL;

    return mbi.AllocationBase;
}

DWORD Meminfo32::GetAllocationProtect()
{
    if(!ready)
        return 0;

    return mbi.AllocationProtect;
}

PVOID Meminfo32::GetBaseAddress()
{
    if(!ready)
        return NULL;

    return mbi.BaseAddress;
}

DWORD Meminfo32::GetRegionSize()
{
    if(!ready)
        return 0;

    return mbi.RegionSize;
}

DWORD Meminfo32::GetType()
{
    if(!ready)
        return 0;

    return mbi.Type;
}

DWORD Meminfo32::GetProtect()
{
    if(!ready)
        return 0; 

    return mbi.Protect;
}


bool Meminfo32::ProtectToStringW(DWORD protect, LPWSTR buf, size_t bufsize)
{
    if(protect == 0 || buf == NULL || bufsize == 0)
        return false;

    LPWSTR szProtection = L"unknwon";

    switch(protect)
    {
        case PAGE_EXECUTE:
            szProtection = L"PAGE_EXECUTE";
            break;
        case PAGE_EXECUTE_READ:
            szProtection = L"PAGE_EXECUTE_READ";
            break;
        case PAGE_EXECUTE_READWRITE:
            szProtection = L"PAGE_EXECUTE_READWRITE";
            break;
        case PAGE_EXECUTE_WRITECOPY:
            szProtection = L"PAGE_EXECUTE_WRITECOPY";
            break;
        case PAGE_NOACCESS:
            szProtection = L"PAGE_NOACCESS";
            break;
        case PAGE_READONLY:
            szProtection = L"PAGE_READONLY";
            break;
        case PAGE_READWRITE:
            szProtection = L"PAGE_READWRITE";
            break;
        case PAGE_WRITECOPY:
            szProtection = L"PAGE_WRITECOPY";
            break;
        case PAGE_GUARD:
            szProtection = L"PAGE_GUARD";
            break;
        case PAGE_NOCACHE:
            szProtection = L"PAGE_NOCACHE";
            break;
        case PAGE_WRITECOMBINE:
            szProtection = L"PAGE_WRITECOMBINE";
            break;
    }

    try
    {
        HRESULT hr = StringCbCopyW(buf, bufsize, szProtection);
        if(SUCCEEDED(hr))
            return true;
        
    }
    catch(...)
    {
        wprintf(L"ProtectToStringW raise exception\n");
    }
    
    return false;
}

bool Meminfo32::GetSizeToUnit(ULONG size, LPWSTR buf, size_t bufsize)
{
    wchar_t *unit[4] = {L"bytes", L"Kb", L"Mb", L"Gb"};
    int iKs=0;
    const double Ks = 1024.0;

    try
    {
        while(true)
        {
            if(size > Ks)
            {
                size = (ULONG)size /Ks;
                iKs++;
            }
            else
            {
                break;
            }
        }

        HRESULT hr = StringCbPrintfW(buf, bufsize, L"%0.2f %s\n", size, unit[iKs]);
        if(SUCCEEDED(hr))
            return true;
    }
    catch(...)
    {
        wprintf(L"Meminfo32::GetSizeToUnit raise exception\n");
        return false;
    }

    return false;
}

bool Meminfo32::AddressToModuleNameW(LPWSTR buf, size_t bufsize)
{
    if(!ready)
        return false; 

    if(buf == NULL || bufsize == 0)
        return false;

    wchar_t modulename[MAX_PATH] = {0, };
    HMODULE hMod = (HMODULE)GetAllocationAddress();
    if(!hMod)
        return false;

    if(!GetModuleFileNameEx(hProcess, hMod, modulename, MAX_PATH))
        return false;

    try
    {
        HRESULT hr;
        WCHAR *tmp = NULL;
        tmp = wcsrchr(modulename, L'\\');
        if(tmp)
        {
            ++tmp;
            hr = StringCbCopyW(buf, bufsize, tmp);
        }
        else
        {
            hr = StringCbCopyW(buf, bufsize, modulename);
        }
        if(SUCCEEDED(hr))
            return true;
    }
    catch(...)
    {
        wprintf(L"AddressToModuleNameW raise exception\n");
    }

    return false;
}

void Meminfo32::ClearMeminfo32()  
{
    if(hProcess)
    {
        CloseHandle(hProcess);
        hProcess = NULL;
    }
    ready = false;
    memset(&mbi, 0, sizeof(mbi));
}

void Meminfo32::ClearImageMeminfo32()
{
    if(hProcess)
    {
        CloseHandle(hProcess);
        hProcess = NULL;
    }
    ready = false;
    memset(&mbi, 0, sizeof(mbi));
}