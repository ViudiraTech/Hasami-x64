/*
 *
 *		printk.h
 *		内核调试和打印信息程序头文件
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留所有权利。
 *
 */

#ifndef INCLUDE_PRINTK_H_
#define INCLUDE_PRINTK_H_

#include "vargs.h"

/* 内核打印字符串 */
VOID
printk(
	const char *format,
	...
	);

/* 内核打印带颜色的字符串 */
VOID
printk_color(
	int fore,
	const char *format,
	...
	);

/* 带前缀的打印函数 */
VOID
print_busy(
	const char *str
	); // 打印带有”[ ** ]“的字符串

VOID
print_succ(
	const char *str
	); // 打印带有”[ OK ]“的字符串

VOID
print_warn(
	const char *str
	); // 打印带有”[WARN]“的字符串

VOID
print_erro(
	const char *str
	); // 打印带有”[ERRO]“的字符串

/* 格式化字符串并将其输出到一个字符数组中 */
int
vsprintf(
	char *buff,
	const char *format,
	va_list args
	);

/* 将格式化的输出存储在字符数组中 */
VOID
sprintf(
	char *str,
	const char *fmt,
	...
	);

#endif // INCLUDE_PRINTK_H_
