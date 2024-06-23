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
# boot loader ld flags
BLDFLAGS       += $(LDSCRIPT-BOOT) -ffreestanding -nostdlib
BLDFLAGS       += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-boot.map,--cref
BLDFLAGS       += -Wl,--no-warn-rwx-segment
BLDFLAGS       += -Wl,-m,elf_i386
