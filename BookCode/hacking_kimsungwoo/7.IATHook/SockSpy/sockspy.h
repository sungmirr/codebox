
#pragma once

#pragma pack(1)

typedef struct _FUNCSTUB
{
    PVOID RealProcAddress;
    BYTE opPUSHAD;
    BYTE opCALL;
    DWORD offHookProc;
    BYTE opPOPAD;
    WORD opJMP;
    DWORD offRealAddress;          
}FUNCSTUB, *PFUNCSTUB;

