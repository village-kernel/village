###########################################################################
# Makefile
# The Makefile of x86bios boot
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-boot-$(CONFIG_X86BIOS)          += 
src-boot-$(CONFIG_X86BIOS)          += village-boot/x86bios


######################################
# objects
######################################
objs-boot-$(CONFIG_X86BIOS)         += boot.o


######################################
# libraries
######################################
libs-boot-$(CONFIG_X86BIOS)         += 


######################################
# link script
######################################
LDSCRIPT-BOOT  := -T village-boot/x86bios/boot.lds


#######################################
# compiler flags
#######################################
# boot loader ld flags
BLDFLAGS       += $(LDSCRIPT-BOOT) -ffreestanding -nostdlib
BLDFLAGS       += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-boot.map,--cref
BLDFLAGS       += -Wl,--no-warn-rwx-segment
BLDFLAGS       += -Wl,-m,elf_i386
