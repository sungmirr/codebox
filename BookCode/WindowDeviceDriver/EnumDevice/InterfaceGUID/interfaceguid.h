#pragma once
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface Class GUIDs
DEFINE_GUID(GUID_DEVINTERFACE_DISK,                   0x53f56307L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_CDROM,                  0x53f56308L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_PARTITION,              0x53f5630aL, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_TAPE,                   0x53f5630bL, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_WRITEONCEDISK,          0x53f5630cL, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_VOLUME,                 0x53f5630dL, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_MEDIUMCHANGER,          0x53f56310L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_FLOPPY,                 0x53f56311L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_CDCHANGER,              0x53f56312L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_STORAGEPORT,            0x2accfe60L, 0xc130, 0x11d2, 0xb0, 0x82, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_COMPORT,                0x86e0d1e0L, 0x8089, 0x11d0, 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73);
DEFINE_GUID(GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR, 0x4D36E978L, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
//


struct _GUID * GlobalGuid[20]={ 
    (struct _GUID *)&GUID_DEVINTERFACE_DISK, 
    (struct _GUID *)&GUID_DEVINTERFACE_CDROM,
    (struct _GUID *)&GUID_DEVINTERFACE_PARTITION,
    (struct _GUID *)&GUID_DEVINTERFACE_TAPE,
    (struct _GUID *)&GUID_DEVINTERFACE_WRITEONCEDISK, 
    (struct _GUID *)&GUID_DEVINTERFACE_VOLUME,
    (struct _GUID *)&GUID_DEVINTERFACE_MEDIUMCHANGER,
    (struct _GUID *)&GUID_DEVINTERFACE_FLOPPY,
    (struct _GUID *)&GUID_DEVINTERFACE_CDCHANGER,
    (struct _GUID *)&GUID_DEVINTERFACE_STORAGEPORT,
    (struct _GUID *)&GUID_DEVINTERFACE_COMPORT,
    (struct _GUID *)&GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR,
    0
};


TCHAR * GlobalString[20]={
    _T("GUID_DEVINTERFACE_DISK	유형의 장치"),
    _T("GUID_DEVINTERFACE_CDROM 유형의 장치"),
    _T("GUID_DEVINTERFACE_PARTITION 유형의 장치"),
    _T("GUID_DEVINTERFACE_TAPE 유형의 장치"),
    _T("GUID_DEVINTERFACE_WRITEONCEDISK 유형의 장치"),
    _T("GUID_DEVINTERFACE_VOLUME 유형의 장치"),
    _T("GUID_DEVINTERFACE_MEDIUMCHANGER 유형의 장치"),
    _T("GUID_DEVINTERFACE_FLOPPY 유형의 장치"),
    _T("GUID_DEVINTERFACE_CDCHANGER 유형의 장치"),
    _T("GUID_DEVINTERFACE_STORAGEPORT 유형의 장치"),
    _T("GUID_DEVINTERFACE_COMPORT 유형의 장치"),
    _T("GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR 유형의 장치"),
    0
};