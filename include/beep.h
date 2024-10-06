/*
 *
 *		beep.h
 *		板载蜂鸣器驱动头文件
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留所有权利。
 *
 */

#ifndef INCLUDE_BEEP_H_
#define INCLUDE_BEEP_H_

#include "types.h"

VOID
system_beep(
	int hertz
	); // 设置板载蜂鸣器状态

#endif // INCLUDE_BEEP_H_
