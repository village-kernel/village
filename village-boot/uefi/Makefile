###########################################################################
# Makefile
# The Makefile of uefi boot
#
# $Copyright: Copyright (C) village
############################################################################

#######################################
# compiler flags
#######################################
# cpu arch
CPU           := -m32 -mno-sse -mno-mmx -DCONFIG_32_BIT
CPUEM         := -melf_i386

# c flags
CFLAGS        += -Wno-error=pragmas -mno-red-zone -mno-avx -fPIE
CFLAGS        += -g -O2 -Wall -Wextra -Wno-pointer-sign
CFLAGS        += -funsigned-char -fshort-wchar -fno-strict-aliasing
CFLAGS        += -ffreestanding -fno-stack-protector -fno-stack-check
CFLAGS        += -fno-merge-all-constants -std=c11
CFLAGS        += -maccumulate-outgoing-args

# ld flags
LDFLAGS       += -nostdlib --warn-common --no-undefined --fatal-warnings --build-id=sha1
LDFLAGS       += -z nocombreloc -shared -Bsymbolic
LDFLAGS       += -T ./uefi/elf_ia32_efi.lds

# copy flags
CPFLAGS       += -j .text -j .sdata -j .data -j .dynamic -j .rodata -j .rel
CPFLAGS       += -j .rela -j .rel.* -j .rela.* -j .rel* -j .rela*
CPFLAGS       += -j .areloc -j .reloc --target efi-app-ia32

# includes
INCLUDES      += -I./uefi/

#######################################
# build task
#######################################
all:
	x86_64-elf-gcc $(CPU) $(CFLAGS) $(INCLUDES) -c ./uefi/crt0_efi_ia32.c -o ./uefi/crt0_efi_ia32.o
	x86_64-elf-gcc $(CPU) $(CFLAGS) $(INCLUDES) -c ./boot/boot.c -o ./boot/boot.o
	x86_64-elf-ld  $(CPUEM) $(LDFLAGS) ./uefi/crt0_efi_ia32.o ./boot/boot.o -o boot.so
	x86_64-elf-objcopy $(CPFLAGS) boot.so boot.efi

test:
	qemu-system-i386 -s -pflash ./ovmf/bios32.bin -m 64 -hda fat:rw:./

clean:
	rm ./uefi/*.o ./boot/*.o *.so *.efi  
