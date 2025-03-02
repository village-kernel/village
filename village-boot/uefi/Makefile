###########################################################################
# Makefile
# The Makefile of uefi boot
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-boot-y                       += village-boot/uefi/uefi
src-boot-y                       += village-boot/uefi/uefi
src-boot-y                       += village-boot/uefi/boot


######################################
# objects
######################################
objs-boot-y                      += boot.o
objs-boot-$(CONFIG_IA32)         += crt0_efi_ia32.o


######################################
# libraries
######################################
libs-boot-y                      += 


######################################
# link script
######################################
LDSCRIPT-BOOT-$(CONFIG_IA32)     := -T village-boot/uefi/uefi/elf_ia32_efi.lds
LDSCRIPT-BOOT                    := $(LDSCRIPT-BOOT-y)


#######################################
# compiler flags
#######################################
# c flags
CFLAGS-BOOT        += -m32 -mno-sse -mno-mmx -DCONFIG_32_BIT
CFLAGS-BOOT        += -Wno-error=pragmas -mno-red-zone -mno-avx -fPIE
CFLAGS-BOOT        += -g -O2 -Wall -Wextra -Wno-pointer-sign
CFLAGS-BOOT        += -funsigned-char -fshort-wchar -fno-strict-aliasing
CFLAGS-BOOT        += -ffreestanding -fno-stack-protector -fno-stack-check
CFLAGS-BOOT        += -fno-merge-all-constants -std=c11
CFLAGS-BOOT        += -maccumulate-outgoing-args

# ld flags
LDFLAGS-BOOT       += -Map $(BUILD_DIR)/$(TARGET)-boot.map --cref
LDFLAGS-BOOT       += -nostdlib -z nocombreloc -shared -Bsymbolic
LDFLAGS-BOOT       += --warn-common --no-undefined --fatal-warnings --build-id=sha1
LDFLAGS-BOOT       += -melf_i386
LDFLAGS-BOOT       += $(LDSCRIPT-BOOT)

# efi flags
EFIFLAGS-BOOT      += -j .text -j .sdata -j .data -j .dynamic -j .rodata -j .rel
EFIFLAGS-BOOT      += -j .rela -j .rel.* -j .rela.* -j .rel* -j .rela*
EFIFLAGS-BOOT      += -j .areloc -j .reloc --target efi-app-ia32
