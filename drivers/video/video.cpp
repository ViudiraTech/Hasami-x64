/*
 *
 *		video.cpp
 *		图像显示驱动
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留最终解释权。
 *
 */

#include "video.h"
#include "string.h"
#include "serial.h"

extern uint8_t ascfont[];

uint32_t *video_mem;
uint32_t width, height;
uint32_t fore_color, back_color;
int32_t x, y;
int32_t cx, cy;
uint32_t c_width, c_height;

int video_serial = 0;

/* 获取Video信息 */
void GetVInfo(FrameBufferConfig &fbc)
{
	video_mem = (uint32_t *)fbc.frame_buffer;
	width = fbc.horizontal_resolution;
	height = fbc.vertical_resolution;;

	set_fore_color(0xffffff);
	set_back_color(0x000000);

	x = 2;
	y = cx = cy = 0;

	c_width = width / 9;
	c_height = height / 16;
}

/* 清屏（默认颜色） */
void video_clear(void)
{
	for (uint32_t i = 0; i < (width * (height)); i++) {
		video_mem[i] = back_color;
	}
	x = 2;
	y = 0;
	cx = cy = 0;
}

/* 清屏（带颜色） */
void video_clear_color(int color)
{
	set_back_color(color);
	for (uint32_t i = 0; i < (width * (height)); i++) {
		video_mem[i] = color;
	}
	x = 2;
	y = 0;
	cx = cy = 0;
}

/* 打印一个空行 */
void video_write_newline(void)
{
	video_scroll();
	cx = 0;
	cy++;
}

/* 屏幕滚动操作 */
void video_scroll(void)
{
	if ((uint32_t)cx > c_width) {
		cx = 0;
		cy++;
	} else cx++;
	if ((uint32_t)cy >= c_height) {
		cy = c_height - 1;
		memcpy(reinterpret_cast<uint8_t*>(video_mem), reinterpret_cast<uint8_t*>(video_mem + width * 16 * sizeof(uint32_t)), width * (height - 16) * sizeof(uint32_t));
		for (uint32_t i = (width * (height - 16)); i != (width * height); i++) {
			video_mem[i] = back_color;
		}
	}
}

/* 在图形界面上进行像素绘制 */
void video_draw_pixel(uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= width || y >= height) {
		return;
	}
	color = (color & 0xff) | (color & 0xff00) | (color & 0xff0000);
	uint32_t  *p = (uint32_t *)video_mem + y * width + x;
	*p = color;
}

/* 在图形界面指定坐标绘制一个矩阵 */
void video_draw_rect(int x0, int y0, int x1, int y1, int color)
{
	int x, y;
	for (y = y0; y <= y1; y++) {
		for (x = x0; x <= x1; x++) {
			(video_mem)[y * width + x] = color;
		}
	}
}

/* 在图形界面指定坐标上显示字符 */
void video_draw_char(char c, int32_t x, int32_t y, int color)
{
	uint8_t *font = ascfont;
	font += c * 16;

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 9; j++) {
			if (font[i] & (0x80 >> j)) {
				video_mem[(y + i) * width + x + j] = color;
			} else video_mem[(y + i) * width + x + j] = back_color;
		}
	}
}

/* 在图形界面指定坐标上打印字符 */
void video_put_char(char c, int color)
{
	// if (video_serial == 1) write_serial(c); // 输出控制台到串口设备（此处会导致某些计算机异常卡顿）
	if (c == '\n') {
		video_scroll();
		cx = 0;
		cy++;
		return;
	} else if (c == '\r') {
		cx = 0;
		return;
	} else if(c == '\t') {
		for (int i = 0; i < 4; i++) video_put_char(' ', color);
		return;
	} else if (c == '\b' && cx > 0) {
		cx -= 1;
		if (cx == 0) {
			cx = c_width - 1;
			if (cy != 0) cy -= 1;
			if (cy == 0) cx = 0, cy = 0;
		}
		int x = (cx+1) * 9 - 7;
		int y = cy * 16;
		video_draw_rect(x, y, x + 9, y + 16, back_color);
		return;
	}
	video_scroll();
	video_draw_char(c, cx * 9 - 7, cy * 16, color);
}

/* 在图形界面指定坐标上打印字符串（默认颜色） */
void video_put_string(const char *str)
{
	for (;*str; ++str) {
		char c = *str;
		video_put_char(c, fore_color);
	}
}

/* 在图形界面指定坐标上打印字符串（带颜色） */
void video_put_string_color(const char *str, int color)
{
	for (;*str; ++str) {
		char c = *str;
		video_put_char(c, color);
	}
}

/* VBE输出映射到串口 */
void video_to_serial(int op)
{
	if (op == 1)
		video_serial = 1;
	else
		video_serial = 0;
}

/* 设置前景色 */
void set_fore_color(int color)
{
	fore_color = color;
}

/* 设置背景色 */
void set_back_color(int color)
{
	back_color = color;
}
