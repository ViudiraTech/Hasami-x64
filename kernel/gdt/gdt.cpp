/*
 *
 *		gdt.cpp
 *		设置全局描述符程序
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留最终解释权。
 *
 */

#include "gdt.h"
#include "string.h"
#include "printk.h"

/* 全局描述符表长度 */
#define GDT_LENGTH 5
#define kernel_data_selector 0x10

/* 全局描述符表定义 */
gdt_entry_t gdt_entries[GDT_LENGTH];

/* GDTR */
gdt_ptr_t gdt_ptr;

static void gdt_set_gate(int64_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);

/* 初始化全局描述符表 */
void init_gdt(void)
{
	print_busy("Initializing the global descriptor table...\r"); // 提示用户正在初始化全局描述符表，并回到行首等待覆盖

	/* 全局描述符表界限 e.g. 从 0 开始，所以总长要 - 1 */
	gdt_ptr.limit	= sizeof(gdt_entry_t) * GDT_LENGTH - 1;
	gdt_ptr.base	= (uint64_t)&gdt_entries;

	/* 采用 Intel 平坦模型 */
	gdt_set_gate(0, 0, 0, 0, 0);				// 按照 Intel 文档要求，第一个描述符必须全 0
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9B, 0xA0);	// 指令段
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x93, 0xA0);	// 数据段
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFB, 0xA0);	// 用户模式代码段
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF3, 0xA0);	// 用户模式数据段

	asm volatile (
		"lgdt [gdt_ptr]\n"
		:
		: [gdt_ptr] "*p" (&gdt_ptr)
	);
	asm volatile (
		"mov %[dsel], %%ds\n"
		"mov %[dsel], %%fs\n"
		"mov %[dsel], %%gs\n"
		"mov %[dsel], %%es\n"
		"mov %[dsel], %%ss\n"
		:
		: [dsel] "rm" (kernel_data_selector)
	);
	print_succ("Global Descriptor Table initialized successfully.\n"); // 提示用户gdt初始化完成
}

/* 全局描述符表构造函数，根据下标构造 */
static void gdt_set_gate(int64_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran)
{
	gdt_entries[num].base_low		= (base & 0xFFFF);
	gdt_entries[num].base_middle	= (base >> 16) & 0xFF;
	gdt_entries[num].base_high		= (base >> 24) & 0xFF;
	gdt_entries[num].limit_low		= (limit & 0xFFFF);
	gdt_entries[num].granularity	= (limit >> 16) & 0x0F;
	gdt_entries[num].granularity	|= gran & 0xF0;
	gdt_entries[num].access			= access;
}
