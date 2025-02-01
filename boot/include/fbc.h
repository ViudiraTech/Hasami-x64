/*
 *
 *		fbc.h
 *		fbc相关定义头文件
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留最终解释权。
 *
 */

#ifndef INCLUDE_FBC_H_
#define INCLUDE_FBC_H_

#include "bootx64.h"

enum PixelFormat {
	kRGBR,
	kBGRR
};

struct FrameBufferConfig {
	uint8_t *frame_buffer;
	uint32_t pixels_per_scan_line;
	uint32_t horizontal_resolution;
	uint32_t vertical_resolution;
	enum PixelFormat pixel_format;
};

#endif // INCLUDE_FBC_H
