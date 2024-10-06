/*
 *
 *		serial.h
 *		计算机串口驱动头文件
 *
 *		2024/10/7 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留所有权利。
 *
 */

#ifndef INCLUDE_SERIAL_H_
#define INCLUDE_SERIAL_H_

#include "types.h"

#define SERIAL_PORT 0x3f8		// 默认使用COM1串口

int
init_serial(
	VOID
	); // 初始化串口

int
serial_received(
	VOID
	); // 检测串口读是否就绪

char
read_serial(
	VOID
	); // 读串口

int
is_transmit_empty(
	VOID
	); // 检测串口写是否空闲

VOID
write_serial(
	char a
	); // 写串口

#endif // INCLUDE_SERIAL_H_
