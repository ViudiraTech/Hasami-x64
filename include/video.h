/*
 *
 *		video.h
 *		图像显示驱动头文件
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留最终解释权。
 *
 */

#ifndef INCLUDE_VIDEO_H_
#define INCLUDE_VIDEO_H_

extern "C" {
#include "bootx64.h"
}

#include "fbc.h"

/* 获取Video信息 */
void GetVInfo(FrameBufferConfig &fbc);

/* 清屏（默认颜色） */
void video_clear(void);

/* 清屏（带颜色） */
void video_clear_color(int color);

/* 打印一个空行 */
void video_write_newline(void);

/* 屏幕滚动操作 */
void video_scroll(void);

/* 在图形界面上进行像素绘制 */
void video_draw_pixel(uint32_t x, uint32_t y, uint32_t color);

/* 在图形界面指定坐标绘制一个矩阵 */
void video_draw_rect(int x0, int y0, int x1, int y1, int color);

/* 在图形界面指定坐标上显示字符 */
void video_draw_char(char c, int32_t x, int32_t y, int color);

/* 在图形界面指定坐标上打印字符 */
void video_put_char(char c, int color);

/* 在图形界面指定坐标上打印字符串（默认颜色） */
void video_put_string(const char *str);

/* 在图形界面指定坐标上打印字符串（带颜色） */
void video_put_string_color(const char *str, int color);

/* VBE输出映射到串口 */
void video_to_serial(int op);

/* 设置前景色 */
void set_fore_color(int color);

/* 设置背景色 */
void set_back_color(int color);

#endif // INCLUDE_VIDEO_H_
