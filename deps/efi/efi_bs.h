#ifndef EFI_BOOT_SERVICES_H
#define EFI_BOOT_SERVICES_H

#include "efi_types.h"

#include "protocols/device_path.h"

#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

#define EVT_TIMER												0x80000000
#define EVT_RUNTIME												0x40000000

#define EVT_NOTIFY_WAIT											0x00000100
#define EVT_NOTIFY_SIGNAL										0x00000200

#define EVT_SIGNAL_EXIT_BOOT_SERVICES							0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE						0x60000202

#define EFI_EVENT_GROUP_EXIT_BOOT_SERVICES {0x27abf055,0xb1b8,0x4c26, {0x80,0x48,0x74,0x8f,0x37,0xba,0xa2,0xdf}}
#define EFI_EVENT_GROUP_BEFORE_EXIT_BOOT_SERVICES {0x8be0e274,0x3970,0x4b44, {0x80,0xc5,0x1a,0xb9,0x50,0x2f,0x3b,0xfc}}
#define EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE {0x13fa7698,0xc831,0x49c7, {0x87,0xea,0x8f,0x43,0xfc,0xc2,0x51,0x96}}
#define EFI_EVENT_GROUP_MEMORY_MAP_CHANGE {0x78bee926,0x692f,0x48fd, {0x9e,0xdb,0x1,0x42,0x2e, 0xf0,0xd7,0xab}}
#define EFI_EVENT_GROUP_READY_TO_BOOT {0x7ce88fb3,0x4bd7,0x4679, {0x87,0xa8,0xa8,0xd8,0xde,0xe5,0xd,0x2b}}
#define EFI_EVENT_GROUP_AFTER_READY_TO_BOOT {0x3a2a00ad,0x98b9,0x4cdf, {0xa4,0x78,0x70,0x27,0x77,0xf1,0xc1,0xb}}
#define EFI_EVENT_GROUP_RESET_SYSTEM {0x62da6a56,0x13fb,0x485a, {0xa8,0xda,0xa3,0xdd,0x79,0x12,0xcb,0x6b}}

#define TPL_APPLICATION 4
#define TPL_CALLBACK 8
#define TPL_NOTIFY 16
#define TPL_HIGH_LEVEL 31

#define EFI_MEMORY_UC 0x0000000000000001
#define EFI_MEMORY_WC 0x0000000000000002
#define EFI_MEMORY_WT 0x0000000000000004
#define EFI_MEMORY_WB 0x0000000000000008
#define EFI_MEMORY_UCE 0x0000000000000010
#define EFI_MEMORY_WP 0x0000000000001000
#define EFI_MEMORY_RP 0x0000000000002000
#define EFI_MEMORY_XP 0x0000000000004000
#define EFI_MEMORY_NV 0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE 0x0000000000010000
#define EFI_MEMORY_RO 0x0000000000020000
#define EFI_MEMORY_SP 0x0000000000040000
#define EFI_MEMORY_CPU_CRYPTO 0x0000000000080000
#define EFI_MEMORY_RUNTIME 0x8000000000000000
#define EFI_MEMORY_ISA_VALID 0x4000000000000000
#define EFI_MEMORY_ISA_MASK 0x0FFFF00000000000

#define EFI_MEMORY_DESCRIPTOR_VERSION 1

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL 0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL 0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER 0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE 0x00000020

typedef struct _EFI_BOOT_SERVICES EFI_BOOT_SERVICES;

typedef enum {
	TimerCancel,
	TimerPeriodic,
	TimerRelative
} EFI_TIMER_DELAY;

typedef enum {
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress,
	MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiPersistentMemory,
	EfiUnacceptedMemoryType,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef enum {
	EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef enum {
	AllHandles,
	ByRegisterNotify,
	ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef struct {
	EFI_UINT32 Type;
	EFI_PHYSICAL_ADDRESS PhysicalStart;
	EFI_VIRTUAL_ADDRESS VirtualStart;
	EFI_UINT64 NumberOfPages;
	EFI_UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef struct {
	EFI_HANDLE AgentHandle;
	EFI_HANDLE ControllerHandle;
	EFI_UINT32 Attributes;
	EFI_UINT32 OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef
VOID
(EFIAPI *EFI_EVENT_NOTIFY)(
	IN EFI_EVENT Event,
	IN VOID *Context
);

typedef
EFI_TPL
(EFIAPI *EFI_RAISE_TPL)(
	IN EFI_TPL NewTpl
);

typedef
EFI_TPL
(EFIAPI *EFI_RESTORE_TPL)(
	IN EFI_TPL OldTpl
);

typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_PAGES)(
	IN EFI_ALLOCATE_TYPE Type,
	IN EFI_MEMORY_TYPE MemoryType,
	IN EFI_UINTN Pages,
	IN OUT EFI_PHYSICAL_ADDRESS *Memory
);

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_PAGES)(
	IN EFI_PHYSICAL_ADDRESS Memory,
	IN EFI_UINTN Pages
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_MEMORY_MAP)(
	IN OUT EFI_UINTN *MemoryMapSize,
	OUT EFI_MEMORY_DESCRIPTOR *MemoryMap,
	OUT EFI_UINTN *MapKey,
	OUT EFI_UINTN *DescriptorSize,
	OUT EFI_UINT32 *DescriptorVersion
);

typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_POOL)(
	IN EFI_MEMORY_TYPE PoolType,
	IN EFI_UINTN Size,
	OUT VOID **Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_POOL)(
	IN VOID *Buffer
);

typedef
VOID
(EFIAPI *EFI_CREATE_EVENT)(
	IN EFI_UINT32 Type,
	IN EFI_TPL NotifyTPL,
	IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
	IN VOID *NotifyContext OPTIONAL,
	OUT EFI_EVENT *Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIMER)(
	IN EFI_EVENT Event,
	IN EFI_TIMER_DELAY Type,
	IN EFI_UINT64 TriggerTime
);

typedef
EFI_STATUS
(EFIAPI *EFI_WAIT_FOR_EVENT)(
	IN EFI_UINTN NumberOfEvents,
	IN EFI_EVENT *Event,
	OUT EFI_UINTN *Index
);

typedef
EFI_STATUS
(EFIAPI *EFI_SIGNAL_EVENT)(
	IN EFI_EVENT Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_EVENT)(
	IN EFI_EVENT Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_CHECK_EVENT)(
	IN EFI_EVENT Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE)(
	IN OUT EFI_HANDLE *Handle,
	IN EFI_GUID *Protocol,
	IN EFI_INTERFACE_TYPE InterfaceType,
	IN VOID *Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE)(
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	IN VOID *OldInterface,
	IN VOID *NewInterface
);

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE)(
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	IN VOID *Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_HANDLE_PROTOCOL)(
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	OUT VOID **Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY)(
	IN EFI_GUID *Protocol,
	IN EFI_EVENT Event,
	OUT VOID **Registration
);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE)(
	IN EFI_LOCATE_SEARCH_TYPE SearchType,
	IN EFI_GUID *Protocol OPTIONAL,
	IN VOID *SearchKey OPTIONAL,
	IN OUT EFI_UINTN *BufferSize,
	OUT EFI_HANDLE *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_DEVICE_PATH)(
	IN EFI_GUID *Protocol,
	IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath,
	OUT EFI_HANDLE *Device
);

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE)(
	IN EFI_GUID *Guid,
	IN VOID *Table
);

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_LOAD)(
	IN EFI_BOOLEAN BootPolicy,
	IN EFI_HANDLE ParentImageHandle,
	IN EFI_DEVICE_PATH_PROTOCOL *DevicePath OPTIONAL,
	IN VOID *SourceBuffer OPTIONAL,
	IN EFI_UINTN SourceSize,
	OUT EFI_HANDLE *ImageHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_START)(
	IN EFI_HANDLE ImageHandle,
	OUT EFI_UINTN *ExitDataSize,
	OUT CHAR16 **ExitData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_EXIT)(
	IN EFI_HANDLE ImageHandle,
	IN EFI_STATUS ExitStatus,
	IN EFI_UINTN ExitDataSize,
	IN CHAR16 *ExitData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_UNLOAD)(
	IN EFI_HANDLE ImageHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_EXIT_BOOT_SERVICES)(
	IN EFI_HANDLE ImageHandle,
	IN EFI_UINTN MapKey
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT)(
	OUT EFI_UINT64 *Count
);

typedef
EFI_STATUS
(EFIAPI *EFI_STALL)(
	IN EFI_UINTN Microseconds
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_WATCHDOG_TIMER)(
	IN EFI_UINTN Timeout,
	IN EFI_UINT64 WatchDogCode,
	IN EFI_UINTN DataSize,
	IN CHAR16 *WatchdogData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_CONNECT_CONTROLLER)(
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE *DriverImageHandle OPTIONAL,
	IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL,
	IN EFI_BOOLEAN Recursive
);

typedef
EFI_STATUS
(EFIAPI *EFI_DISCONNECT_CONTROLLER)(
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE DriverImageHandle OPTIONAL,
	IN EFI_HANDLE ChildHandle OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION)(
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
	OUT EFI_UINTN *EntryCount
);

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL)(
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	OUT VOID **Interface OPTIONAL,
	IN EFI_HANDLE AgentHandle,
	IN EFI_HANDLE ControllerHandle,
	IN EFI_UINT32 Attributes
);

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_PROTOCOL)(
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	IN EFI_HANDLE AgentHandle,
	IN EFI_HANDLE ControllerHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_PROTOCOLS_PER_HANDLE)(
	IN EFI_HANDLE Handle,
	OUT EFI_GUID ***ProtocolBuffer,
	OUT EFI_UINTN *ProtocolBufferCount
);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE_BUFFER)(
	IN EFI_LOCATE_SEARCH_TYPE SearchType,
	IN EFI_GUID *Protocol OPTIONAL,
	IN VOID *SearchKey OPTIONAL,
	OUT EFI_UINTN *NoHandles,
	OUT EFI_HANDLE **Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_PROTOCOL)(
	IN EFI_GUID *Protocol,
	IN VOID *Registration OPTIONAL,
	OUT VOID **Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
	IN OUT EFI_HANDLE *Handle,
	...
);

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
	IN OUT EFI_HANDLE *Handle,
	...
);

typedef
EFI_STATUS
(EFIAPI *EFI_CALCULATE_CRC32)(
	IN VOID *Data,
	IN EFI_UINTN DataSize,
	OUT EFI_UINT32 *Crc32
);

typedef
VOID
(EFIAPI *EFI_COPY_MEM)(
	IN VOID *Destination,
	IN VOID *Source,
	IN EFI_UINTN Length
);

typedef
VOID
(EFIAPI *EFI_SET_MEM)(
	IN VOID *Buffer,
	IN EFI_UINTN Size,
	IN EFI_UINT8 Value
);

typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT_EX)(
	IN EFI_UINT32 Type,
	IN EFI_TPL NotifyTpl,
	IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
	IN CONST VOID *NotifyContext OPTIONAL,
	IN CONST EFI_GUID *EventGroup OPTIONAL,
	OUT EFI_EVENT *Event
);

typedef struct _EFI_BOOT_SERVICES {
	EFI_TABLE_HEADER Hdr;

	// Task Priority Services
	EFI_RAISE_TPL RaiseTPL;
	EFI_RESTORE_TPL RestoreTPL;

	// Memory Services
	EFI_ALLOCATE_PAGES AllocatePages;
	EFI_FREE_PAGES FreePages;
	EFI_GET_MEMORY_MAP GetMemoryMap;
	EFI_ALLOCATE_POOL AllocatePool;
	EFI_FREE_POOL FreePool;

	// Event & Timer Services
	EFI_CREATE_EVENT CreateEvent;
	EFI_SET_TIMER SetTimer;
	EFI_WAIT_FOR_EVENT WaitForEvent;
	EFI_SIGNAL_EVENT SignalEvent;
	EFI_CLOSE_EVENT CloseEvent;
	EFI_CHECK_EVENT CheckEvent;

	// Protocol Handler Services
	EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;
	EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;
	EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;
	EFI_HANDLE_PROTOCOL HandleProtocol;
	VOID *Reserved;
	EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;
	EFI_LOCATE_HANDLE LocateHandle;
	EFI_LOCATE_DEVICE_PATH LocateDevicePath;
	EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;

	// Image Services
	EFI_IMAGE_LOAD LoadImage;
	EFI_IMAGE_START StartImage;
	EFI_EXIT Exit;
	EFI_IMAGE_UNLOAD UnloadImage;
	EFI_EXIT_BOOT_SERVICES ExitBootServices;

	// Miscellaneous Services
	EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount;
	EFI_STALL Stall;
	EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;

	// DriverSupport Services
	EFI_CONNECT_CONTROLLER ConnectController;
	EFI_DISCONNECT_CONTROLLER DisconnectController;

	// Open and Close Protocol Services
	EFI_OPEN_PROTOCOL OpenProtocol;
	EFI_CLOSE_PROTOCOL CloseProtocol;
	EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation;

	// Library Services
	EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;
	EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;
	EFI_LOCATE_PROTOCOL LocateProtocol;
	EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
	EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

	// 32-bit CRC Services
	EFI_CALCULATE_CRC32 CalculateCrc32;

	// Miscellaneous Services
	EFI_COPY_MEM CopyMem;
	EFI_SET_MEM SetMem;
	EFI_CREATE_EVENT_EX CreateEventEx;
} EFI_BOOT_SERVICES;

#endif /* EFI_BOOT_SERVICES_H */