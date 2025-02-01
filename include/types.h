/*
 *
 *		types.h
 *		基本数据类型头文件
 *
 *		2024/10/6 By MicroFish
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留最终解释权。
 *
 */

#ifndef INCLUDE_TYPES_H_
#define INCLUDE_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
#	define null 0
#	define NULL 0
#endif

#ifndef __cplusplus
#	define bool		_Bool
#	define true		1
#	define false	0
#endif

#undef INT8_MIN
#undef INT8_MAX
#undef UINT8_MAX
#undef INT16_MIN
#undef INT16_MAX
#undef UINT16_MAX
#undef INT32_MIN
#undef INT32_MAX
#undef UINT32_MAX
#undef INT64_MIN
#undef INT64_MAX
#undef UINT64_MAX

#define INT8_MIN					__INT8_MIN__
#define INT8_MAX					__INT8_MAX__
#define UINT8_MAX					__UINT8_MAX__
#define INT16_MIN					__INT16_MIN__
#define INT16_MAX					__INT16_MAX__
#define UINT16_MAX					__UINT16_MAX__
#define INT32_MIN					__INT32_MIN__
#define INT32_MAX					__INT32_MAX__
#define UINT32_MAX					__UINT32_MAX__
#define INT64_MIN					__INT64_MIN__
#define INT64_MAX					__INT64_MAX__
#define UINT64_MAX					__UINT64_MAX__

#define I8_MIN						__INT8_MIN__
#define I8_MAX						__INT8_MAX__
#define U8_MAX						__UINT8_MAX__
#define I16_MIN						__INT16_MIN__
#define I16_MAX						__INT16_MAX__
#define U16_MAX						__UINT16_MAX__
#define I32_MIN						__INT32_MIN__
#define I32_MAX						__INT32_MAX__
#define U32_MAX						__UINT32_MAX__
#define I64_MIN						__INT64_MIN__
#define I64_MAX						__INT64_MAX__
#define U64_MAX						__UINT64_MAX__

typedef __INTPTR_TYPE__				intptr_t;
typedef __UINTPTR_TYPE__			uintptr_t;
typedef __INTPTR_TYPE__				ssize_t;
typedef __UINTPTR_TYPE__			size_t;

typedef unsigned char				uchar;
typedef unsigned short				ushort;
typedef unsigned int				uint;
typedef unsigned long				ulong;

typedef __INT8_TYPE__				int8_t;
typedef __UINT8_TYPE__				uint8_t;
typedef __INT16_TYPE__				int16_t;
typedef __UINT16_TYPE__				uint16_t;
typedef __INT32_TYPE__				int32_t;
typedef __UINT32_TYPE__				uint32_t;
typedef __INT64_TYPE__				int64_t;
typedef __UINT64_TYPE__				uint64_t;
typedef float						float32_t;
typedef double						float64_t;

typedef int8_t						i8;
typedef uint8_t						u8;
typedef int16_t						i16;
typedef uint16_t					u16;
typedef int32_t						i32;
typedef uint32_t					u32;
typedef int64_t						i64;
typedef uint64_t					u64;
typedef float32_t					f32;
typedef float64_t					f64;

typedef _Complex float				cfloat;
typedef _Complex double				cdouble;
typedef _Complex double				complex;

typedef _Complex __INT8_TYPE__		cint8_t;
typedef _Complex __UINT8_TYPE__		cuint8_t;
typedef _Complex __INT16_TYPE__		cint16_t;
typedef _Complex __UINT16_TYPE__	cuint16_t;
typedef _Complex __INT32_TYPE__		cint32_t;
typedef _Complex __UINT32_TYPE__	cuint32_t;
typedef _Complex __INT64_TYPE__		cint64_t;
typedef _Complex __UINT64_TYPE__	cuint64_t;
typedef _Complex float				cfloat32_t;
typedef _Complex double				cfloat64_t;

typedef i8 sbyte;
typedef u8 byte;

typedef void VOID;

#ifdef __cplusplus
}
#endif

#endif // INCLUDE_TYPES_H_
