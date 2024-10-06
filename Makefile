BOOTX64_C		= ./boot/bootx64.c
BOOTX64_EFI		= ./bootx64.efi

KERNEL_CPP		= ./init/main.cpp
KERNEL_O		= ./init/main.o
KERNEL_ELF		= ./kernel.elf

OTHER_OBJ		= ./drivers/vga/video.o ./kernel/fonts/fonts.o ./lib/math.o ./lib/stdlib.o \
                  ./lib/string.o ./kernel/debug/printk.o ./drivers/common.o

MINGW_GCC		= x86_64-w64-mingw32-gcc
GPP				= g++
LD				= ld

GCC_FLAGS		= -W -Wno-missing-field-initializers -Wextra -e efi_main -nostdinc -nostdlib -fno-builtin -Wl,--subsystem,10 -I ./boot/include/ -o
GPP_FLAGS		= -O2 -W -m64 -Wimplicit-fallthrough=0 -g -ffreestanding -fno-exceptions -fno-rtti -std=c++17 -I ./include/ -I ./boot/include/ -fshort-wchar -c -o
LD_FLAGS		= -e KernelMain -z norelro --static -o

QEMU			= qemu-system-x86_64

all: info src done

info:
	@echo bootx64 Compile Script.
	@echo Copyright 2020 ViudiraTech. All Rights Reserved.
	@echo Based on the GPL-3.0 open source license.
	@echo

src:
	@echo "\033[32m[Build]\033[0m" Compiling Code Files $(BOOTX64_C)
	@$(MINGW_GCC) $(GCC_FLAGS) $(BOOTX64_EFI) $(BOOTX64_C)

	@echo "\033[32m[Build]\033[0m" Compiling Code Files $(KERNEL_CPP)
	@$(GPP) $(KERNEL_CPP) $(GPP_FLAGS) $(KERNEL_O)

	@$(GPP) ./drivers/vga/video.cpp $(GPP_FLAGS) ./drivers/vga/video.o
	@$(GPP) ./kernel/fonts/fonts.cpp $(GPP_FLAGS) ./kernel/fonts/fonts.o
	@$(GPP) ./lib/math.cpp $(GPP_FLAGS) ./lib/math.o
	@$(GPP) ./lib/stdlib.cpp $(GPP_FLAGS) ./lib/stdlib.o
	@$(GPP) ./lib/math.cpp $(GPP_FLAGS) ./lib/math.o
	@$(GPP) ./lib/string.cpp $(GPP_FLAGS) ./lib/string.o
	@$(GPP) ./kernel/debug/printk.cpp $(GPP_FLAGS) ./kernel/debug/printk.o
	@$(GPP) ./drivers/common.cpp $(GPP_FLAGS) ./drivers/common.o

	@echo "\033[32m[Build]\033[0m" Linking Obj Files $(KERNEL_O)
	@$(LD) $(LD_FLAGS) $(KERNEL_ELF) $(KERNEL_O) $(OTHER_OBJ)

done:
	@echo "\033[32m[Done]\033[0m" Compilation complete.
	@echo

clean:
	@rm -rf $(BOOTX64_EFI)
	@rm -rf $(KERNEL_O)
	@rm -rf $(KERNEL_ELF)
	@rm -rf $(OTHER_OBJ)

.PHONY:qemu_uefi
run:
	@mkdir -p ./esp/EFI/BOOT
	@cp $(BOOTX64_EFI) ./esp/EFI/BOOT
	@cp $(KERNEL_ELF) ./esp
	$(QEMU) -bios ./bios/OVMF.fd -net none -drive file=fat:rw:esp,index=0,format=vvfat
	@rm -rf ./esp/

.PHONY:qemu_uefi_debug
run_db:
	@mkdir -p ./esp/EFI/BOOT
	@cp $(BOOTX64_EFI) ./esp/EFI/BOOT
	@cp $(KERNEL_ELF) ./esp
	$(QEMU) -bios ./bios/OVMF.fd -net none -drive file=fat:rw:esp,index=0,format=vvfat -d in_asm
	@rm -rf ./esp/
