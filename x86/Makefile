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
LDFLAG1 = -m elf_i386 -Tbootloader.ld
LDFLAG2 = -m elf_i386 --oformat binary -Ttext 0x7c00

boot:
	$(AS) -c $(CFLAG) src/BootEntry.s -o BootEntry.o
	$(CC) -c $(CFLAG) src/Bootloader.cpp -o Bootloader.o
	$(LD) $(LDFLAG1) BootEntry.o Bootloader.o -o Bootloader.elf
	$(BIN) Bootloader.elf Bootloader.bin

	$(AS) -c $(CFLAG) src/BootSection.s -o BootSection.o
	$(LD) $(LDFLAG2) BootSection.o -o BootSection.bin

	dd if=/dev/zero of=vboot.img bs=512 count=18
	dd if=BootSection.bin of=vboot.img bs=512 seek=0 conv=notrunc
	dd if=Bootloader.bin  of=vboot.img bs=512 seek=1 conv=notrunc

clean:
	rm -rf *.o *.elf *.hex *.bin *.img
