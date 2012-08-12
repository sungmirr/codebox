
#define NT_DEVICE_NAME L"\\Device\\CallGate"
#define DOS_DEVICE_NAME L"\\DosDevices\\CallGate"
#define PRISM_DEVICE_TYPE 0x0000AA71

#define PRISM_IO(_code)		CTL_CODE(PRISM_DEVICE_TYPE, _code, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_CREATE_CALLGATE		PRISM_IO(0x4)	//
#define IOCTL_RELEASE_CALLGATE		PRISM_IO(0x5)	//

typedef struct _CALLGATE_INFO
{
    void *FuncAddress;
    int NumParam;
    unsigned short CodeSelector;
    unsigned short CallGateSelector;
}CALLGATE_INFO, *PCALLGATE_INFO;