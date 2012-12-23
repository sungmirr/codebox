/*++
    <2012. 12. 23>

    ProcessInsight
   
--*/
#include <windows.h>
#include <stdio.h>
#include "Archive.h"
#include <strsafe.h>


int main(void)
{
    Archive ar;

    ar.SetProcessList();
    ar.PrintProcessList();

    return 0;
}