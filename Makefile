# =====================================================
#
#		Makefile
#		Hasami 编译文件
#
#		2024/10/6 By Rainy101112
#		基于 GPL-3.0 开源协议
#		Copyright © 2020 ViudiraTech，保留所有权利。
#
# =====================================================

KERNEL_CPP		= ./init/main.cpp
KERNEL_O		= ./init/main.o
KERNEL_ELF		= ./kernel.elf

MINGW_GCC		= x86_64-w64-mingw32-gcc
GPP				= g++
LD				= ld
ASM				= nasm

GCC_FLAGS		= -W -Wno-missing-field-initializers -Wextra -e efi_main -nostdinc -nostdlib -fno-builtin -Wl,--subsystem,10 -I ./boot/include/ -o
GPP_FLAGS		= -O2 -W -m64 -Wimplicit-fallthrough=0 -g -ffreestanding -fno-exceptions -fno-rtti -std=c++17 -I ./include/ -I ./boot/include/ -fshort-wchar -c -o
ASM_FLAGS		= -f elf64 -g -F stabs
LD_FLAGS		= -e KernelMain -z norelro --static -m elf_x86_64 -nostdlib -o

QEMU			= qemu-system-x86_64

BOOTX64_C		= ./boot/bootx64.c
BOOTX64_EFI		= ./bootx64.efi
CPP_SOURCES		= $(shell find . -name "*.cpp" -type f -not -path "./init/*")
CPP_OBJECTS		= $(patsubst %.cpp, %.o, $(CPP_SOURCES))
S_SOURCES		= $(shell find . -name "*.s")
S_OBJECTS		= $(patsubst %.s, %.o, $(S_SOURCES))

all: info .c.o kernel link done

info:
	@echo Hasami-x64 Compile Script.
	@echo Copyright 2020 ViudiraTech. All Rights Reserved.
	@echo Based on the GPL-3.0 open source license.
	@echo

.s.o:
	@echo "\033[32m[Build]\033[0m" Compiling Assembly $< ...
	@$(ASM) $(ASM_FLAGS) $<

.c.o:
	@echo "\033[32m[Build]\033[0m" Compiling Code Files $(BOOTX64_C) ...
	@$(MINGW_GCC) $(GCC_FLAGS) $(BOOTX64_EFI) $(BOOTX64_C)

kernel:
	@echo "\033[32m[Build]\033[0m" Compiling Code Files $(KERNEL_CPP) ...
	@$(GPP) $(KERNEL_CPP) $(GPP_FLAGS) $(KERNEL_O)

%.o: %.cpp
	@echo "\033[32m[Build]\033[0m" Compiling Code Files ./$< ...
	@$(GPP) ./$< $(GPP_FLAGS) $@

link:$(KERNEL_O) $(CPP_OBJECTS) $(S_OBJECTS)
	@echo
	@echo "\033[32m[Link]\033[0m" Linking Obj Files $(KERNEL_O) ...
	@$(LD) $(LD_FLAGS) $(KERNEL_ELF) $(KERNEL_O) $(CPP_OBJECTS) $(S_OBJECTS) ./lib/klogo.obj

done:
	@echo "\033[32m[Done]\033[0m" Compilation complete.
	@echo

.PHONY: clean
clean:
	rm -rf $(BOOTX64_EFI) $(KERNEL_O) $(KERNEL_ELF) $(CPP_OBJECTS) $(S_OBJECTS)

.PHONY: qemu_uefi
run:
	@mkdir -p ./esp/EFI/BOOT
	@cp $(BOOTX64_EFI) ./esp/EFI/BOOT
	@cp $(KERNEL_ELF) ./esp
	$(QEMU) -bios ./bios/OVMF.fd -serial stdio -net none -drive file=fat:rw:esp,index=0,format=vvfat
	@rm -rf ./esp/

.PHONY: qemu_uefi_debug
run_db:
	@mkdir -p ./esp/EFI/BOOT
	@cp $(BOOTX64_EFI) ./esp/EFI/BOOT
	@cp $(KERNEL_ELF) ./esp
	$(QEMU) -bios ./bios/OVMF.fd -serial stdio -net none -drive file=fat:rw:esp,index=0,format=vvfat -d in_asm
	@rm -rf ./esp/
