/*
 *
 *		common.h
 *		常见设备驱动
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留最终解释权。
 *
 */

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include "types.h"
#include "string.h"

void outb(uint16_t port, uint8_t value);	// 端口写（8位）
void outw(uint16_t port, uint16_t value);	// 端口写（16位）
void outl(uint16_t port, uint32_t value);	// 端口写（32位）

uint8_t inb(uint16_t port);					// 端口读（8位）
uint16_t inw(uint16_t port);				// 端口读（16位）
uint32_t inl(uint16_t port);				// 端口读（32位）

/* 从I/O端口批量地读取数据到内存（16位） */
void insw(uint16_t port, void *buf, unsigned long n);

/* 从内存批量地写入数据到I/O端口（16位） */
void outsw(uint16_t port, const void *buf, unsigned long n);

/* 从I/O端口批量地读取数据到内存（32位） */
void insl(uint32_t port, void *addr, int cnt);

/* 从内存批量地写入数据到I/O端口（32位） */
void outsl(uint32_t port, const void *addr, int cnt);

/* 获取当前的CR0寄存器的值 */
uint32_t get_cr0(void);

/* 将值写入CR0寄存器 */
void set_cr0(uint32_t cr0);

void enable_intr(void);		// 开启中断
void disable_intr(void);	// 关闭中断
void krn_halt(void);		// 内核停机

#endif // INCLUDE_COMMON_H_
