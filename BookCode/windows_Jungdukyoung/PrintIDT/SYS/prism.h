#ifndef _PRISM_H
#define _PRISM_H

#define NT_DEVICE_NAME	L"\\Device\\PrintIDT"
#define DOS_DEVICE_NAME L"\\DosDevices\\PrintIDT"
#define PRISM_DEVICE_TYPE 0x0000AA71

//
#define PRISM_IO(_code)		CTL_CODE(PRISM_DEVICE_TYPE, _code, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_PRINT_IDT		PRISM_IO(0x7)	//

#endif