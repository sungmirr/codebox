#ifndef _INTEL80X86_H
#define _INTEL80X86_H
//intel80x86.h


#define LOWORD(i)           ((unsigned short)(unsigned int)(i))
#define HIWORD(i)           ((unsigned short)((((unsigned int)(i)) >> 16) & 0xFFFF))

typedef UCHAR               BYTE,  *PBYTE,  **PPBYTE;
typedef USHORT              WORD,  *PWORD,  **PPWORD;
typedef ULONG               DWORD, *PDWORD, **PPDWORD;

typedef int                 BOOL,  *PBOOL,  **PPBOOL;
typedef void                *PVOID,  **PPVOID;

typedef long		        NTSTATUS, *PNTSTATUS, **PPNTSTATUS;


/* UNICODE (wide character) types */
#ifndef __cplusplus
typedef short unsigned int wchar_t;
#endif	/* __cplusplus */
typedef wchar_t WCHAR;
typedef WCHAR *PWCHAR;
typedef WCHAR *LPWCH, *PWCH;
typedef CONST WCHAR *LPCWCH, *PCWCH;
typedef WCHAR *NWPSTR;
typedef WCHAR *LPWSTR, *PWSTR;
typedef CONST WCHAR *LPCWSTR, *PCWSTR;

typedef unsigned __int64    QWORD, *PQWORD, **PPQWORD;
typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS, **PPPHYSICAL_ADDRESS;



typedef struct _CODE_SEG_DESCRIPTOR
{
    union
    {
        struct
        {
            DWORD dwValueLow; 
            DWORD dwValueHigh;
        };
        struct
        {	
            unsigned short  Limit_0_15	 :16;
            unsigned short  Base_0_15	 :16;
            unsigned char   Base_16_23	 : 8;

            unsigned char    Accessed    : 1;
            unsigned char    Read	     : 1;//0 : OnlyExecute 1:Read/Execute
            unsigned char    Conforming  : 1;//1 : Conforming
            unsigned char    Code_data   : 1;//1 : Code, 0:Data
            unsigned char    S			 : 1;
            unsigned char    DPL         : 2;
            unsigned char    Present     : 1;

            unsigned char    Limit_16_19 : 4;
            unsigned char    Unused      : 1;
            unsigned char    Reserved    : 1;
            unsigned char    DefaultBit  : 1;// 0=16-bit, 1=32-bit	
            unsigned char    Granularity : 1;// 0=1Byte, 1=4KB

            unsigned char    Base_24_31	 : 8;
        };
    };	
}CODE_SEG_DESCRIPTOR, *PCODE_SEG_DESCRIPTOR;




#endif