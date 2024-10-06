/*
 *
 *		memory.h
 *		内存相关定义头文件
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留所有权利。
 *
 */

#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#define FREE_MEMORY 1
#define MMIO_MEMORY 2
#define UEFI_MEMORY 3

#pragma pack(16)

#include "bootx64.h"

typedef struct __packed
{
	uint64_t MapSize;
	VOID *Buffer;
	uint64_t MapKey;
	uint64_t DescriptorSize;
	uint32_t DescriptorVersion;
} MEMORY_MAP;

typedef struct {
	uint32_t Type;
	uint64_t PhysicalStart;
	uint64_t PageSize;
} OS_MEMORY_DESCRIPTOR;

#endif // INCLUDE_MEMORY_H_
