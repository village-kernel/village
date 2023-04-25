###########################################################################
# Makefile
# The Makefile of vk.hardware
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-y                    += vk.hardware/BSP/x86/GCC
src-y                    += vk.hardware/BSP/x86/GCC


######################################
# objects
######################################
objs-bs-$(CONFIG_BOOTSECTION) += boot.o
objs-bl-$(CONFIG_BOOTLOADER)  += startup.o
objs-y                        += startup.o


######################################
# arch
######################################
# MCU
MCU  := -m32

# defines
DEFS := 

# link script
LDSCRIPT-BS     := -T vk.hardware/BSP/x86/LinkerScripts/bs.ld
LDSCRIPT-BL     := -T vk.hardware/BSP/x86/LinkerScripts/bl.ld
LDSCRIPT-KERNEL := -T vk.hardware/BSP/x86/LinkerScripts/kernel.ld


#######################################
# compiler flags
#######################################
# gcc flags
CFLAGS    += $(MCU) $(DEFS) $(OPT) $(INCLUDES)
CFLAGS    += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(dir $<)/$(@:.o=.lst)
CFLAGS    += -Wall -fdata-sections -ffunction-sections -fno-common
CXXFLAGS  += $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit

# boot section ld flags
BSLDFLAGS += -Wl,-m,elf_i386 $(LDSCRIPT-BS) -ffreestanding -nostdlib

# boot loader ld flags
BLDFLAGS  += $(MCU) $(LDSCRIPT-BL) -ffreestanding -nostdlib
BLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-boot.map,--cref
BLDFLAGS  += -Wl,--gc-sections
BLDFLAGS  += -Wl,--no-warn-rwx-segment
BLDFLAGS  += -Wl,-m,elf_i386

# kernel ld flags
KLDFLAGS  += $(MCU) $(LDSCRIPT-KERNEL) -ffreestanding -nostdlib
KLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-kernel.map,--cref
KLDFLAGS  += -Wl,--gc-sections
KLDFLAGS  += -Wl,--no-warn-rwx-segment
KLDFLAGS  += -Wl,-m,elf_i386 

# mod ld flags
MLDFLAGS   = $(MCU) -T vk.scripts/ldscript/module.ld
MLDFLAGS  += -Wl,-Map=$(@:.mo=.map) --cref
MLDFLAGS  += -Wl,-r -Wl,-Bsymbolic
MLDFLAGS  += -Wl,-m,elf_i386 

