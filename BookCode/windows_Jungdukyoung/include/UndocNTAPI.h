#ifndef _UNDOCNTAPI_H
#define _UNDOCNTAPI_H

NTSYSAPI
NTSTATUS
NTAPI
KeI386AllocateGdtSelectors(
    PUSHORT pSelectorArray,
    ULONG NumberOfSelectors
);

NTSYSAPI
NTSTATUS
NTAPI
KeI386ReleaseGdtSelectors(
    PUSHORT pSelectorArray,
    ULONG NumberOfSelectors
);

NTSYSAPI
NTSTATUS
NTAPI
KeI386SetGdtSelector(
    ULONG Selector,
    PVOID pDescriptor
);


#endif
