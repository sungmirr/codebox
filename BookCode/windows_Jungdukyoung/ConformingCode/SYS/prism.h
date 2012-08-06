#define NT_DEVICE_NAME      L"\\Device\\ConformSel"
#define DOS_DEVICE_NAME     L"\\DosDevices\\ConformSel"
#define PRISM_DEVICE_TYPE   0x0000AA71

#define PRISM_IO(_code)     CTL_CODE(PRISM_DEVICE_TYPE,  _code, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_CREATE_CONFORMING_CODE    PRISM_IO(0x4)
#define IOCTL_RELEASE_CONFORMING_CODE   PRISM_IO(0x5)

typedef struct _CONFORMING_INFO{
    unsigned short ConformingSel;
}CONFORMING_INFO, *PCONFORMING_INFO;