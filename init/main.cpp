/*
 *
 *		main.h
 *		UEFI启动内核测试文件
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留所有权利。
 *
 */

extern "C" {
#include "bootx64.h"
}

#include "fbc.h"
#include "video.h"
#include "printk.h"
#include "version.h"
#include "gdt.h"
#include "common.h"

extern "C" VOID
KernelMain(
	FrameBufferConfig &fbc,
	EFI_SYSTEM_TABLE &SystemTable,
	BOOT_CONFIG *BootConfig
	)
{
	disable_intr();	// 关闭中断
	GetVInfo(fbc);	// 获取Video信息
	video_clear();	// 清屏

	video_to_serial(1);
	printk("Hasami x64 " KERNL_VERS "(build-%d)\n", KERNL_BUID);			// 打印内核信息
	printk(PROJK_COPY "\n");												// 打印版权信息
	printk("This version compiles at " BUILD_DATE " " BUILD_TIME "\n\n");	// 打印编译日期时间

	printk("Initializing operating system kernel components.\n");			// 提示用户正在初始化内核
	init_gdt(); // 初始化GDT

	video_to_serial(0);
	while (1);
}
