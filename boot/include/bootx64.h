/*
 *
 *		bootx64.h
 *		UEFI引导程序头文件
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留最终解释权。
 *
 */

#ifndef INCLUDE_BOOTX64_H_
#define INCLUDE_BOOTX64_H_

#include "types.h"
#include "memory.h"
#include "fbc.h"

#define EFI_ERROR_MASK							0x8000000000000000
#define EFIERR(a)								(EFI_ERROR_MASK | a)
#define EFI_ERROR(status)						(((long long)status) < 0)
#define EFIAPI									__attribute__((ms_abi))
#define EFI_SUCCESS								0
#define EFI_LOAD_ERROR							EFIERR(1)
#define EFI_INVALID_PARAMETER					EFIERR(2)
#define EFI_UNSUPPORTED							EFIERR(3)
#define EFI_BAD_BUFFER_SIZE						EFIERR(4)
#define EFI_BUFFER_TOO_SMALL					EFIERR(5)
#define EFI_NOT_READY							EFIERR(6)
#define EFI_DEVICE_ERROR						EFIERR(7)
#define EFI_WRITE_PROTECTED						EFIERR(8)
#define EFI_OUT_OF_RESOURCES					EFIERR(9)
#define EFI_VOLUME_CORRUPTED					EFIERR(10)
#define EFI_VOLUME_FULL							EFIERR(11)
#define EFI_NO_MEDIA							EFIERR(12)
#define EFI_MEDIA_CHANGED						EFIERR(13)
#define EFI_NOT_FOUND							EFIERR(14)
#define EFI_ACCESS_DENIED						EFIERR(15)
#define EFI_NO_RESPONSE							EFIERR(16)
#define EFI_NO_MAPPING							EFIERR(17)
#define EFI_TIMEOUT								EFIERR(18)
#define EFI_NOT_STARTED							EFIERR(19)
#define EFI_ALREADY_STARTED						EFIERR(20)
#define EFI_ABORTED								EFIERR(21)
#define EFI_ICMP_ERROR							EFIERR(22)
#define EFI_TFTP_ERROR							EFIERR(23)
#define EFI_PROTOCOL_ERROR						EFIERR(24)
#define EFI_INCOMPATIBLE_VERSION				EFIERR(25)
#define EFI_SECURITY_VIOLATION					EFIERR(26)
#define EFI_CRC_ERROR							EFIERR(27)
#define EFI_END_OF_MEDIA						EFIERR(28)
#define EFI_END_OF_FILE							EFIERR(31)
#define EFI_INVALID_LANGUAGE					EFIERR(32)
#define EFI_COMPROMISED_DATA					EFIERR(33)

#define EFI_FILE_MODE_READ_ONLY					0x00000001
#define EFI_READ_ONLY							EFI_FILE_MODE_READ_ONLY

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL	0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL			0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL			0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER	0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER				0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE				0x00000020

#define EFI_FILE_MODE_READ						0x0000000000000001
#define EFI_FILE_MODE_WRITE						0x0000000000000002
#define EFI_FILE_MODE_CREATE					0x8000000000000000

#define min(a, b)								((a) < (b) ? (a) : (b))
#define max(a, b)								((a) < (b) ? (b) : (a))

typedef void *EFI_HANDLE;
typedef void *EFI_EVENT;
typedef uint64_t EFI_STATUS;
typedef uint64_t EFI_PHYSICAL_ADDRESS;
typedef uint64_t EFI_VIRTUAL_ADDRESS;

typedef struct {
	MEMORY_MAP MemoryMap;
} BOOT_CONFIG;

typedef struct {
	uint32_t Type;
	EFI_PHYSICAL_ADDRESS PhysicalStart;
	EFI_VIRTUAL_ADDRESS VirtualStart;
	uint64_t NumberOfPages;
	uint64_t Attribute;
} __attribute__((__aligned__(16))) EFI_MEMORY_DESCRIPTOR;

enum EFI_ALLOCATE_TYPE {
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress,
	MaxAllocateType
};

enum EFI_MEMORY_TYPE {
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
	EfiMaxMemoryType
};

enum EFI_GRAPHICS_PIXEL_FORMAT {
	PixelRedGreenBlueReserved8BitPerColor,
	PixelBlueGreenRedReserved8BitPerColor,
	PixelBitMask,
	PixelBltOnly,
	PixelFormatMax
};

static void xmemset(void *dst_, uint8_t value, uint64_t size)
{
	uint8_t *dst = (uint8_t *)dst_;
	while (size-- > 0)
		*dst++ = value;
}

static void *xmemcpy(void *dst_, const void *src_, uint64_t size)
{
	uint8_t *dst = (uint8_t *)dst_;
	const uint8_t *src = (uint8_t *)src_;
	while (size-- > 0)
		*dst++ = *src++;
	return (void *)src_;
}

struct EFI_GUID {
	uint32_t Data1;
	uint16_t Data2;
	uint16_t Data3;
	uint8_t Data4[8];
};

struct EFI_INPUT_KEY {
	uint16_t ScanCode;
	uint16_t UnicodeChar;
};

struct EFI_FILE_PROTOCOL {
	uint64_t Revision;
	EFIAPI
	EFI_STATUS(*Open)
	(struct EFI_FILE_PROTOCOL *This, struct EFI_FILE_PROTOCOL **NewHandle, uint16_t *FileName, uint64_t OpenMode, uint64_t Attributes);
	EFIAPI EFI_STATUS (*Close)(struct EFI_FILE_PROTOCOL *This);
	uint64_t _buf2;
	EFIAPI
	EFI_STATUS (*Read)(struct EFI_FILE_PROTOCOL *This, uint64_t *BufferSize, void *Buffer);
	EFIAPI
	EFI_STATUS (*Write)(struct EFI_FILE_PROTOCOL *This, uint64_t *BufferSize, void *Buffer);
	uint64_t _buf3[4];
	EFIAPI EFI_STATUS (*Flush)(struct EFI_FILE_PROTOCOL *This);
};

struct EFI_SYSTEM_TABLE {
	char _buf1[44];
		struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
		uint64_t Reset;
		EFIAPI EFI_STATUS (*ReadKeyStroke)(struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, struct EFI_INPUT_KEY *Key);
		EFI_EVENT WaitForKey;
	} *ConIn;
	uint64_t _buf2;
	struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
		uint64_t _buf;
		EFIAPI
		EFI_STATUS (*OutputString)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, uint16_t *String);
		uint64_t _buf2[4];
		EFIAPI EFI_STATUS (*ClearScreen)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
	} *ConOut;
	uint64_t _buf3[3];
	struct EFI_BOOT_SERVICES *BootServices;
};

struct EFI_BOOT_SERVICES {
	char _buf1[24];

	/* Task Priority Services */
	uint64_t _buf2[2];

	/* Memory Services */
	EFIAPI
	EFI_STATUS(*AllocatePages)
	(enum EFI_ALLOCATE_TYPE Type, enum EFI_MEMORY_TYPE MemoryType, uint64_t Pages, EFI_PHYSICAL_ADDRESS *Memory);
	EFIAPI EFI_STATUS (*FreePages)(EFI_PHYSICAL_ADDRESS Memory, uint64_t Pages);
	EFIAPI EFI_STATUS (*GetMemoryMap)(uint64_t *MemoryMapSize, EFI_MEMORY_DESCRIPTOR *MemoryMap,
	uint64_t *MapKey, uint64_t *DescriptorSize, uint32_t *DescriptorVersion);
	EFIAPI EFI_STATUS (*AllocatePool)(enum EFI_MEMORY_TYPE PoolType, uint64_t Size, void **Buffer);
	EFIAPI EFI_STATUS (*FreePool)(void *Buffer);

	/* Event & Timer Services */
	uint64_t _buf4[2];
	EFIAPI
	EFI_STATUS (*WaitForEvent)(uint64_t NumberOfEvents, EFI_EVENT *Event, uint64_t *Index);
	uint64_t _buf4_2[3];

	/* Protocol Handler Services */
	uint64_t _buf5[9];

	/* Image Services */
	uint64_t _buf6[5];

	/* Miscellaneous Services */
	uint64_t  _buf7[2];
	EFIAPI EFI_STATUS (*SetWatchdogTimer)(uint64_t Timeout, uint64_t WatchdogCode, uint64_t DataSize, uint64_t *WatchdogData);

	/* DriverSupport Services */
	uint64_t _buf8[2];

	/* Open and Close Protocol Services */
	EFIAPI
	EFI_STATUS(*OpenProtocol)
	(EFI_HANDLE Handle, struct EFI_GUID *Protocol, void **Interface, EFI_HANDLE AgentHandle,
	EFI_HANDLE ControllerHandle, uint32_t Attributes);
	uint64_t _buf9[2];

	/* Library Services */
	uint64_t _buf10[2];
	EFIAPI
	EFI_STATUS (*LocateProtocol)(struct EFI_GUID *Protocol, void *Registration, void **Interface);
	uint64_t _buf10_2[2];

	/* 32-bit CRC Services */
	uint64_t _buf11;

	/* Miscellaneous Services */
	uint64_t _buf12[3];
};

struct EFI_LOADED_IMAGE_PROTOCOL {
	uint32_t Revision;
	EFI_HANDLE ParentHandle;
	struct EFI_SYSTEM_TABLE *SystemTable;

	EFI_HANDLE DeviceHandle;
	void *FilePath;
	void *Reserved;

	uint32_t LoadOptionsSize;
	void *LoadOptions;

	void *ImageBase;
	uint64_t ImageSize;
	enum EFI_MEMORY_TYPE ImageCodeType;
	enum EFI_MEMORY_TYPE ImageDataType;
	EFIAPI EFI_STATUS (*Unload)(EFI_HANDLE ImageHandle);
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL {
	uint64_t _buf[3];
	struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE {
		uint32_t MaxMode;
		uint32_t Mode;
		struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION {
			uint32_t Version;
			uint32_t HorizontalResolution;
			uint32_t VerticalResolution;
			enum EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
			uint32_t PixelInformation[4];
			uint32_t PixelsPerScanLine;
		} *Info;
		uint64_t SizeOfInfo;
		EFI_PHYSICAL_ADDRESS FrameBufferBase;
		uint64_t FrameBufferSize;
	} *Mode;
};

struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
	uint64_t Revision;
	EFIAPI EFI_STATUS (*OpenVolume)(struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This, struct EFI_FILE_PROTOCOL **Root);
};

/* 初始化efi */
void efi_init(EFI_HANDLE ImageHandle, struct EFI_SYSTEM_TABLE *SystemTable);

/* 打印字符串 */
void puts(unsigned short *s);

/* 分配固定大小的内存 */
void *malloc(int buf_size);

/* 释放内存 */
void free(void *buf);

EFI_STATUS GetMMP(MEMORY_MAP *MemoryMap);

#endif // INCLUDE_BOOTX64_H_
