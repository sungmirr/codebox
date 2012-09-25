//nativeAPI.h
#ifndef _NATIVEAPI_H
#define _NATIVEAPI_H

extern "C" {


//ntddk.h
typedef LONG NTSTATUS, *PNTSTATUS, **PPNTSTATUS;
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH      ((NTSTATUS)0xC0000004L)


#ifndef _NTDDK_
	typedef struct _IO_COUNTERS {
		ULONGLONG ReadOperationCount;
		ULONGLONG WriteOperationCount;
		ULONGLONG OtherOperationCount;
		ULONGLONG ReadTransferCount;
		ULONGLONG WriteTransferCount;
		ULONGLONG OtherTransferCount;
	} IO_COUNTERS;
	typedef IO_COUNTERS *PIO_COUNTERS;
#endif

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;

typedef enum _POOL_TYPE {
    NonPagedPool,
    PagedPool,
    NonPagedPoolMustSucceed,
    DontUseThisType,
    NonPagedPoolCacheAligned,
    PagedPoolCacheAligned,
    NonPagedPoolCacheAlignedMustS,
    MaxPoolType

    // end_wdm
    ,
    //
    // Note these per session types are carefully chosen so that the appropriate
    // masking still applies as well as MaxPoolType above.
    //

    NonPagedPoolSession = 32,
    PagedPoolSession = NonPagedPoolSession + 1,
    NonPagedPoolMustSucceedSession = PagedPoolSession + 1,
    DontUseThisTypeSession = NonPagedPoolMustSucceedSession + 1,
    NonPagedPoolCacheAlignedSession = DontUseThisTypeSession + 1,
    PagedPoolCacheAlignedSession = NonPagedPoolCacheAlignedSession + 1,
    NonPagedPoolCacheAlignedMustSSession = PagedPoolCacheAlignedSession + 1,

    // begin_wdm

    } POOL_TYPE;

//

typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation,              // 0
    SystemProcessorInformation,          // 1
    SystemPerformanceInformation,        // 2
    SystemTimeOfDayInformation,          // 3
    SystemNotImplemented1,               // 4
    SystemProcessesAndThreadsInformation, // 5
    SystemCallCounts,                    // 6
    SystemConfigurationInformation,      // 7
    SystemProcessorTimes,                // 8
    SystemGlobalFlag,                    // 9
    SystemNotImplemented2,               // 10
    SystemModuleInformation,             // 11
    SystemLockInformation,               // 12
    SystemNotImplemented3,               // 13
    SystemNotImplemented4,               // 14
    SystemNotImplemented5,               // 15
    SystemHandleInformation,             // 16
    SystemObjectInformation,             // 17
    SystemPagefileInformation,           // 18
    SystemInstructionEmulationCounts,    // 19
    SystemInvalidInfoClass1,             // 20
    SystemCacheInformation,              // 21
    SystemPoolTagInformation,            // 22
    SystemProcessorStatistics,           // 23
    SystemDpcInformation,                // 24
    SystemNotImplemented6,               // 25
    SystemLoadImage,                     // 26
    SystemUnloadImage,                   // 27
    SystemTimeAdjustment,                // 28
    SystemNotImplemented7,               // 29
    SystemNotImplemented8,               // 30
    SystemNotImplemented9,               // 31
    SystemCrashDumpInformation,          // 32
    SystemExceptionInformation,          // 33
    SystemCrashDumpStateInformation,     // 34
    SystemKernelDebuggerInformation,     // 35
    SystemContextSwitchInformation,      // 36
    SystemRegistryQuotaInformation,      // 37
    SystemLoadAndCallImage,              // 38
    SystemPrioritySeparation,            // 39
    SystemNotImplemented10,              // 40
    SystemNotImplemented11,              // 41
    SystemInvalidInfoClass2,             // 42
    SystemInvalidInfoClass3,             // 43
    SystemTimeZoneInformation,           // 44
    SystemLookasideInformation,          // 45
    SystemSetTimeSlipEvent,              // 46
    SystemCreateSession,                 // 47
    SystemDeleteSession,                 // 48
    SystemInvalidInfoClass4,             // 49
    SystemRangeStartInformation,         // 50
    SystemVerifierInformation,           // 51
    SystemAddVerifier,                   // 52
    SystemSessionProcessesInformation    // 53
} SYSTEM_INFORMATION_CLASS;

NTSYSAPI
NTSTATUS
NTAPI
ZwQuerySystemInformation(
    IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
    OUT PVOID SystemInformation,
    IN ULONG SystemInformationLength,
    OUT PULONG ReturnLength OPTIONAL
    );


//NTDLL.DLL
typedef LONG NTSTATUS, *PNTSTATUS, **PPNTSTATUS;
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

#define STATUS_INFO_LENGTH_MISMATCH      ((NTSTATUS)0xC0000004L)

typedef struct _VM_COUNTERS {
    ULONG PeakVirtualSize;
    ULONG VirtualSize;
    ULONG PageFaultCount;
    ULONG PeakWorkingSetSize;
    ULONG WorkingSetSize;
    ULONG QuotaPeakPagedPoolUsage;
    ULONG QuotaPagedPoolUsage;
    ULONG QuotaPeakNonPagedPoolUsage;
    ULONG QuotaNonPagedPoolUsage;
    ULONG PagefileUsage;
    ULONG PeakPagefileUsage;
} VM_COUNTERS;
typedef VM_COUNTERS *PVM_COUNTERS;

//typedef NTSTATUS (NTAPI *NTPROC) ();

typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID;
typedef CLIENT_ID *PCLIENT_ID;

typedef LONG KPRIORITY;
typedef LONG THREAD_STATE;
typedef LONG KWAIT_REASON;

typedef struct _OBJECT_ATTRIBUTES {
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
    PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;

typedef struct _SYSTEM_THREADS {
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER CreateTime;
	ULONG WaitTime;
	PVOID StartAddress;
	CLIENT_ID ClientId;
	KPRIORITY Priority;
	KPRIORITY BasePriority;
	ULONG ContextSwitchCount;
	THREAD_STATE State;
	KWAIT_REASON WaitReason;
}SYSTEM_THREADS, *PSYSTEM_THREADS;


typedef struct _SYSTEM_PROCESSES { 	//Information 5
	ULONG NextEntryDelta;
	ULONG ThreadCount;
	ULONG Reserved1[6];
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ProcessName;
	KPRIORITY BasePriority;
	ULONG ProcessId;
	ULONG InheritedFromProcessId;
	ULONG HandleCount;
	ULONG Reserved2[2];
	VM_COUNTERS VmCounters;
	IO_COUNTERS IoCounters;
	SYSTEM_THREADS Threads[1];
}SYSTEM_PROCESSES, *PSYSTEM_PROCESSES;

typedef struct _SYSTEM_HANDLE_INFORMATION {	//Information 16
    ULONG ProcessId;
    UCHAR ObjectTypeNumber;
    UCHAR Flags;			// 0x01 = PROTECT_FROM_CLOSE, 0x02 = INHERIT
    USHORT Handle;
    PVOID Object;
    ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;




typedef struct _OBJECT_NAME_INFORMATION {               
    UNICODE_STRING Name;                                
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;


typedef enum _OBJECT_INFORMATION_CLASS {
    ObjectBasicInformation,             // 0
    ObjectNameInformation,              // 1
    ObjectTypeInformation,              // 2
    ObjectAllTypesInformation,          // 3
    ObjectHandleInformation             // 4
} OBJECT_INFORMATION_CLASS;

NTSYSAPI
NTSTATUS
NTAPI
ZwQueryObject(
    IN HANDLE ObjectHandle,
    IN OBJECT_INFORMATION_CLASS ObjectInformationClass,
    OUT PVOID ObjectInformation,
    IN ULONG ObjectInformationLength,
    OUT PULONG ReturnLength OPTIONAL
    );

typedef struct _OBJECT_BASIC_INFORMATION { // Information 0
    ULONG Attributes;
    ACCESS_MASK GrantedAccess;
    ULONG HandleCount;
    ULONG PointerCount;
    ULONG PagedPoolUsage;
    ULONG NonPagedPoolUsage;
    ULONG Reserved[3];
    ULONG NameInformationLength;
    ULONG TypeInformationLength;
    ULONG SecurityDescriptorLength;
    LARGE_INTEGER CreateTime;
} OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;

typedef struct _OBJECT_TYPE_INFORMATION { // Information 2
    UNICODE_STRING Name;
    ULONG ObjectCount;
    ULONG HandleCount;
    ULONG Reserved1[4];
    ULONG PeakObjectCount;
    ULONG PeakHandleCount;
    ULONG Reserved2[4];
    ULONG InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ULONG ValidAccess;
    UCHAR Unknown;
    BOOLEAN MaintainHandleDatabase;
    UCHAR Reserved3[2];
    POOL_TYPE PoolType;
    ULONG PagedPoolUsage;
    ULONG NonPagedPoolUsage;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

}// extern "C"
#endif
