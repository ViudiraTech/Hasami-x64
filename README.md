# 欢迎来到 Hasami x64内核项目

![](https://img.shields.io/badge/License-GPLv3-blue) ![](https://img.shields.io/badge/Language-2-orange) ![](https://img.shields.io/badge/hardware-x64-green) ![](https://img.shields.io/badge/firmware-UEFI-yellow)

## 简介

一个C语言和C++写的UEFI x64系统内核，GPL-3.0开源协议

## 编译要求

1. **操作系统**：必须是Linux系统，例如Debian、Ubuntu等。
2. **工具安装**：必须安装好gcc、mingw-w64、make和nasm工具。如果需要测试，请安装qemu虚拟机。

## 编译指南

1. **获取源码**：将源码PULL到本地。
2. **编译**：在已PULL到本地的项目源码根目录内执行make命令，即可开始编译。
3. **编译结果**：编译后会生成两个文件：bootx64.efi和kernel.elf，这两个文件分别为UEFI引导程序和内核文件
4. **清理与测试**：
   - 输入“make clean”清理所有中间文件及引导和内核。
   - 输入“make run”即可通过qemu测试。
   - “make run-db”可以调出调试（控制台显示汇编代码）。

# 贡献者排名

1. **MicroFish** （27份）
1. **Rainy101112** （1份）

括弧内仅仅代表初次上传并且未删除的代码等文件数量，不包括修改、整理等。

# 全部源码被移除的贡献者

无

源码因过旧、BUG、或不需要等其他原因被移除，排名仅代表顺序。

# 项目所使用的开源代码

- Uinxed-Kernel: [https://gitee.com/ViudiraTech/uinxed-kernel.git/](https://gitee.com/ViudiraTech/uinxed-kernel.git/)

## 版权声明

本项目所有商为ViudiraTech。
内核源码为GPL-3.0开源协议
Copyright © 2020 ViudiraTech，保留所有权利。
