/*++
    ListProcessAndThread.exe

     - Native API(ZwQuerySystemInformation)를 이용 어플리케이션에서
      프로세스와 스레드 정보 얻기

     - 2012.7.25 20:00
--*/

#include <windows.h>
#include <stdio.h>
#define _NTDDK_
#include "nativeAPI.h"
#include <tchar.h>

void ShowErrorMessage(HRESULT hr);

int _tmain(void)
{
    DWORD dwAllocatedSize = 0, dwNeeded = 0;
    PSYSTEM_PROCESSES pProcesses = NULL;        // SYSTEM_PROCESSES안에 SYSTEM_THREADS 구조체 배열로 쓰레드정보포함
    int nThreadCount = 0;

    try
    {
        dwAllocatedSize = 0x1000;   // 4k, 4096
        pProcesses = (PSYSTEM_PROCESSES)VirtualAlloc(NULL, dwAllocatedSize, MEM_COMMIT, PAGE_READWRITE);

        while(ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, 
            pProcesses, dwAllocatedSize, &dwNeeded) == STATUS_INFO_LENGTH_MISMATCH)
        {
            VirtualFree(pProcesses, dwAllocatedSize, MEM_DECOMMIT);
            if(dwNeeded > dwAllocatedSize)
                dwAllocatedSize = dwNeeded;
            else
                dwAllocatedSize += 0x500;

            pProcesses = (PSYSTEM_PROCESSES)VirtualAlloc(NULL, dwAllocatedSize, MEM_COMMIT, PAGE_READWRITE);
        }
        
        while(pProcesses->NextEntryDelta != 0)
        {
            // 각 원소에 pProcess->NextEntryDelta만큼 오프셋 이동해서 접근
            // ULONG ThreadCount;, SYSTEM_THREADS Threads[1];  <== 얘네들 때문에 각 원소 사이즈가 각각틀리다
            pProcesses = (PSYSTEM_PROCESSES)((char *)pProcesses + pProcesses->NextEntryDelta);

            //Print Process Information
            _tprintf(_T("PID:%d - %s\n"), 
                pProcesses->ProcessId, 
                pProcesses->ProcessName.Buffer);

            //Print Thread
            for(ULONG nIndex = 0 ; nIndex < pProcesses->ThreadCount ; nIndex ++)
            {
                _tprintf(_T("    [%d], StartAddress : 0x%08x\n"), 
                    pProcesses->Threads[nIndex].ClientId.UniqueThread, 
                    pProcesses->Threads[nIndex].StartAddress);

            }
        }
    }
    catch(HRESULT hr)
    {
        ShowErrorMessage(hr);
    }
    catch(...)
    {
        MessageBox(0, _T("Exception raised!!!"), NULL, 0);
    }

    if(pProcesses)
        VirtualFree(pProcesses, dwAllocatedSize, MEM_DECOMMIT);

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