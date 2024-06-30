###########################################################################
# Makefile
# The Makefile of ia32bios boot
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-boot-$(CONFIG_IA32)          += 
src-boot-$(CONFIG_IA32)          += village-boot/legacy/ia32bios


######################################
# objects
######################################
objs-boot-$(CONFIG_IA32)         += boot.o


######################################
# libraries
######################################
libs-boot-$(CONFIG_IA32)         += 


######################################
# link script
######################################
LDSCRIPT-BOOT  := -T village-boot/legacy/ia32bios/boot.lds


#######################################
# compiler flags
#######################################
# boot loader c flags
CFLAGS-BOOT    += -m32 -mno-sse

# boot loader ld flags
LDFLAGS-BOOT   += $(LDSCRIPT-BOOT) -ffreestanding -nostdlib
LDFLAGS-BOOT   += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-boot.map,--cref
LDFLAGS-BOOT   += -Wl,--no-warn-rwx-segment
LDFLAGS-BOOT   += -Wl,-m,elf_i386
