/*
 *
 *		video.h
 *		图像显示驱动头文件
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留所有权利。
 *
 */

#ifndef INCLUDE_VIDEO_H_
#define INCLUDE_VIDEO_H_

extern "C" {
#include "bootx64.h"
}

#include "fbc.h"

/* 获取Video信息 */
VOID
GetVInfo(
	FrameBufferConfig &fbc
	);

/* 清屏（默认颜色） */
VOID
video_clear(
	VOID
	);

/* 清屏（带颜色） */
VOID
video_clear_color(
	int color
	);

/* 打印一个空行 */
VOID
video_write_newline(
	VOID
	);

/* 屏幕滚动操作 */
VOID
video_scroll(
	VOID
	);

/* 在图形界面上进行像素绘制 */
VOID
video_draw_pixel(
	uint32_t x,
	uint32_t y,
	uint32_t color
	);

/* 在图形界面指定坐标绘制一个矩阵 */
VOID
video_draw_rect(
	int x0,
	int y0,
	int x1,
	int y1,
	int color
	);

/* 在图形界面指定坐标上显示字符 */
VOID
video_draw_char(
	char c,
	int32_t x,
	int32_t y,
	int color
	);

/* 在图形界面指定坐标上打印字符 */
VOID
video_put_char(
	char c,
	int color
	);

/* 在图形界面指定坐标上打印字符串（默认颜色） */
VOID
video_put_string(
	const char *str
	);

/* 在图形界面指定坐标上打印字符串（带颜色） */
VOID
video_put_string_color(
	const char *str,
	int color
	);

/* 设置前景色 */
VOID
set_fore_color(
	int color
	);

/* 设置背景色 */
VOID
set_back_color(
	int color
	);

#endif // INCLUDE_VIDEO_H_
