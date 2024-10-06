/*
 *
 *		bootx64.c
 *		UEFI引导程序
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留所有权利。
 *
 */

#include "bootx64.h"
#include "elf.h"

struct BOOT_CONFIG;
typedef VOID (*__attribute__((sysv_abi)) Kernel)(const struct FrameBufferConfig *, struct EFI_SYSTEM_TABLE *, struct BOOT_CONFIG *);

struct EFI_SYSTEM_TABLE					*ST;
struct EFI_BOOT_SERVICES				*BS;
struct EFI_LOADED_IMAGE_PROTOCOL		*LIP;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL		*GOP;
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL	*SFSP;
EFI_HANDLE								IM;

struct EFI_GUID gop_guid = {
	0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}
};

struct EFI_GUID lip_guid = {
    0x5b1b31a1, 0x9562, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}
};

struct EFI_GUID sfsp_guid = {
    0x964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}
};

struct EFI_GUID spp_guid = {
    0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}
};

/* efi入口 */
EFI_STATUS
EFIAPI
efi_main(
	EFI_HANDLE ImageHandle,
	struct EFI_SYSTEM_TABLE *SystemTable
	)
{
	efi_init(ImageHandle, SystemTable);
	ST->ConOut->ClearScreen(ST->ConOut);

	puts(L"BOOTX64 UEFI Bootloader (Version 1.0)\r\n");
	puts(L"Copyright (C) 2020 ViudiraTech, All rights reserved.\r\n\n");

	EFI_STATUS status;
	EFI_PHYSICAL_ADDRESS entry_addr;
	struct EFI_FILE_PROTOCOL *root, *kernel_file;
	uint64_t kernel_size = 4194304;
	VOID *kernel_buffer = malloc(kernel_size);

	status = SFSP->OpenVolume(SFSP, &root);
	if (EFI_ERROR(status)) {
		puts(L"[ FAIL ] Loading File System\r\n");
		while (1);
	}
	puts(L"[ SUCC ] Loading File System\r\n");
	status = root->Open(root, &kernel_file, L"\\kernel.elf", EFI_FILE_MODE_READ, 0);
	if (EFI_ERROR(status)) {
	puts(L"[ FAIL ] Loading Kernel Files\r\n");
	while (1);
	}
	status = kernel_file->Read(kernel_file, &kernel_size, kernel_buffer);
	if (EFI_ERROR(status)) {
	puts(L"[ FAIL ] Loading Kernel Files\r\n");
	while (1);
	}
	puts(L"[ SUCC ] Loading Kernel Files\r\n");

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)kernel_buffer;
	uint64_t kernel_first_addr, kernel_last_addr;
	CalcLoadAddressRange(ehdr, &kernel_first_addr, &kernel_last_addr);

	CopyLoadSegments(ehdr);
	entry_addr = ehdr->e_entry;

	struct FrameBufferConfig config = {
		(uint8_t *)GOP->Mode->FrameBufferBase, GOP->Mode->Info->PixelsPerScanLine,
		GOP->Mode->Info->HorizontalResolution, GOP->Mode->Info->VerticalResolution};

		switch (GOP->Mode->Info->PixelFormat) {
		case PixelRedGreenBlueReserved8BitPerColor: config.pixel_format = kRGBR; break;
		case PixelBlueGreenRedReserved8BitPerColor: config.pixel_format = kBGRR; break;
		default:
			puts(L"[ FAIL ] Loading Graphics\r\n");
			while (1);
	}
	puts(L"[ SUCC ] Loading Graphics\r\n");

	BOOT_CONFIG BootConfig;
	BootConfig.MemoryMap.MapSize = 4096;
	BootConfig.MemoryMap.Buffer = NULL;
	BootConfig.MemoryMap.MapKey = 0;
	BootConfig.MemoryMap.DescriptorSize = 0;
	BootConfig.MemoryMap.DescriptorVersion = 0;

	GetMMP(&BootConfig.MemoryMap);
	puts(L"[ SUCC ] Getting Memory Map\r\n\n");

	Kernel kernel = (Kernel)entry_addr;
	puts(L"Operating System Boot Success.\r\n");
	kernel(&config, SystemTable, (void *)&BootConfig);
	while (1);
}

/* 初始化efi */
VOID
efi_init(
	EFI_HANDLE ImageHandle,
	struct EFI_SYSTEM_TABLE *SystemTable
	)
{
	ST = SystemTable;
	BS = SystemTable->BootServices;
	IM = ImageHandle;

	// init
	BS->SetWatchdogTimer(0, 0, 0, NULL);
	BS->LocateProtocol(&gop_guid, NULL, (void **)&GOP);
	BS->OpenProtocol(ImageHandle, &lip_guid, (void **)&LIP, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
	BS->OpenProtocol(LIP->DeviceHandle, &sfsp_guid, (void **)&SFSP, ImageHandle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
}

/* 打印字符串 */
VOID
puts(
	unsigned short *s
	)
{
	ST->ConOut->OutputString(ST->ConOut, s);
}

/* 分配固定大小的内存 */
VOID
*malloc(
	int buf_size
	)
{
	VOID *res;
	unsigned long long status;

	// 分配内存，第一个参数是判断LIP是否存在，如果存在就直接拿过来用
	status = BS->AllocatePool(LIP ? LIP->ImageDataType : EfiLoaderData, buf_size, &res);
	if (status!=EFI_SUCCESS) return NULL;
	return res;
}

/* 释放内存 */
VOID
free(
	VOID *buf
	)
{
  BS->FreePool(buf);
}

EFI_STATUS
GetMMP(
	MEMORY_MAP *MemoryMap
	)
{
	EFI_STATUS GetMemoryMapStatus = EFI_SUCCESS;

	/* 获取内存表 */
	MemoryMap->Buffer = malloc(MemoryMap->MapSize);

	/* 获取内存表 */
	while( BS->GetMemoryMap(
		&MemoryMap->MapSize,
		(EFI_MEMORY_DESCRIPTOR*)MemoryMap->Buffer,
		&MemoryMap->MapKey,
		&MemoryMap->DescriptorSize,
		&MemoryMap->DescriptorVersion
	) == EFI_BUFFER_TOO_SMALL) {
		if (MemoryMap->Buffer) {
			free(MemoryMap->Buffer);
			MemoryMap->Buffer = NULL;
		}

		/* 重新分配更大的缓冲区 */
		MemoryMap->Buffer = malloc(MemoryMap->MapSize);
	}

	/* 检查是否成功分配了内存 */
	if (!MemoryMap->Buffer) {
		GetMemoryMapStatus = EFI_OUT_OF_RESOURCES;
	}
	return GetMemoryMapStatus;
}
