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

CFLAG  = -m32
LDFLAG = -m elf_i386 -Tbootloader.ld

boot:
	$(AS)  -c $(CFLAG) src/boot.s -o boot.o
#	$(CXX) -c $(CFLAG) src/Bootloader.cpp -o Bootloader.o
	$(LD) $(LDFLAG) boot.o -o boot.elf
	$(HEX) boot.elf boot.hex
	$(BIN) boot.elf boot.bin

clean:
	rm -rf Bootloader.o boot.o boot.elf boot.hex boot.bin
