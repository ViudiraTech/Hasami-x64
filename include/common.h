/*
 *
 *		common.h
 *		常见设备驱动
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留所有权利。
 *
 */

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include "types.h"
#include "string.h"

VOID
outb(
	uint16_t port,
	uint8_t value
	); // 端口写（8位）

VOID
outw(
	uint16_t port,
	uint16_t value
	); // 端口写（16位）

VOID
outl(
	uint16_t port,
	uint32_t value
	); // 端口写（32位）

uint8_t
inb(
	uint16_t port
	); // 端口读（8位）

uint16_t
inw(
	uint16_t port
	); // 端口读（16位）

uint32_t
inl(
	uint16_t port
	); // 端口读（32位）

/* 从I/O端口批量地读取数据到内存（16位） */
VOID
insw(
	uint16_t port,
	VOID *buf,
	unsigned long n
	);

/* 从内存批量地写入数据到I/O端口（16位） */
VOID
outsw(
	uint16_t port,
	const VOID *buf,
	unsigned long n
	);

/* 从I/O端口批量地读取数据到内存（32位） */
VOID
insl(
	uint32_t port,
	VOID *addr,
	int cnt
	);

/* 从内存批量地写入数据到I/O端口（32位） */
VOID
outsl(
	uint32_t port,
	const VOID *addr,
	int cnt
	);

/* 获取当前的CR0寄存器的值 */
uint32_t
get_cr0(
	VOID
	);

/* 将值写入CR0寄存器 */
VOID
set_cr0(
	uint32_t cr0
	);

VOID
enable_intr(
	VOID
	); // 开启中断

VOID
disable_intr(
	VOID
	); // 关闭中断

VOID
krn_halt(
	VOID
	); // 内核停机

#endif // INCLUDE_COMMON_H_
