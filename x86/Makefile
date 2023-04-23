GCC_PREFIX ?= i686-elf-
CXX = $(GCC_PREFIX)g++
CC  = $(GCC_PREFIX)gcc
AS  = $(GCC_PREFIX)gcc -x assembler-with-cpp
AR  = $(GCC_PREFIX)ar
LD  = $(GCC_PREFIX)ld
CP  = $(GCC_PREFIX)objcopy
SZ  = $(GCC_PREFIX)size
ST  = $(GCC_PREFIX)strip
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

ASFLAG = --32 -gstabs
CFLAG  = -m32 -o0 -gdwarf-2 -ffreestanding
#CFLAG  = -m32 -o0 -ffreestanding
#LDFLAG = -m elf_i386 -Tbootloader.ld
LDFLAG1 = -m elf_i386 -Ttext 0x1000
LDFLAG2 = -m elf_i386 --oformat binary -Ttext 0x7c00

boot:
	$(AS) -c $(CFLAG) src/BootEntry.s -o BootEntry.o
	$(CC) -c $(CFLAG) src/Bootloader.cpp -o Bootloader.o
	$(LD) $(LDFLAG1) BootEntry.o Bootloader.o -o Bootloader.elf
	$(BIN) Bootloader.elf Bootloader.bin

	$(AS) -c $(CFLAG) src/BootSection.s -o BootSection.o
	$(LD) $(LDFLAG2) BootSection.o -o BootSection.bin
	cat BootSection.bin Bootloader.bin BootSection.bin > os-image

clean:
	rm -rf *.o *.elf *.hex *.bin
