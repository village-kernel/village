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

CFLAG  = -m32 -o0 -gdwarf-2 -ffreestanding
LDFLAG = -m elf_i386 -Tbootloader.ld

boot:
	$(AS)  -c $(CFLAG) src/BootSection.s -o BootSection.o
	$(CXX) -c $(CFLAG) src/Bootloader.cpp -o Bootloader.o
	$(LD) $(LDFLAG) BootSection.o -o BootSection.elf
	$(HEX) BootSection.elf BootSection.hex
	$(BIN) BootSection.elf BootSection.bin

clean:
	rm -rf *.o *.elf *.hex *.bin
