/*
 *
 *		idt.h
 *		设置中断描述符程序头文件
 *
 *		2025/2/1 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留最终解释权。
 *
 */

#ifndef INCLUDE_IDT_H_
#define INCLUDE_IDT_H_

#include "types.h"

struct idt_register {
	uint16_t size;
	void *ptr;
} __attribute__((packed));

struct idt_entry {
	uint16_t offset_low;	// 处理函数指针低16位地址
	uint16_t selector;		// 段选择子
	uint8_t ist;
	uint8_t flags;			// 标志位
	uint16_t offset_mid;	// 处理函数指针中16位地址
	uint32_t offset_hi;		// 处理函数指针高32位地址
	uint32_t reserved;
} __attribute__((packed));

/* 初始化中断描述符表 */
void init_idt(void);

/* 注册一个中断处理函数 */
void register_interrupt_handler(uint16_t vector, void *handler, uint8_t ist, uint8_t flags);

#endif // INCLUDE_IDT_H_
