###########################################################################
# Makefile
# The Makefile of vk.hardware
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-y                        += vk.hardware/BSP/x86/GCC
src-y                        += vk.hardware/BSP/x86/GCC


######################################
# objects
######################################
ifneq ($(CONFIG_VKLIBC), y)
objs-bl-y                     += syscalls.o
objs-bl-y                     += sysmem.o
objs-y                        += syscalls.o
objs-y                        += sysmem.o
endif

objs-bs-$(CONFIG_BOOTSECTION) += boot.o
objs-bl-$(CONFIG_BOOTLOADER)  += startup.o
objs-y                        += startup.o


######################################
# arch
######################################
# MCU
MCU  := -m32

# defines
DEFS := -DARCH_X86

# link script
LDSCRIPT-BS     := -T vk.hardware/BSP/x86/LinkerScripts/bs.ld
LDSCRIPT-BL     := -T vk.hardware/BSP/x86/LinkerScripts/bl.ld
LDSCRIPT-KERNEL := -T vk.hardware/BSP/x86/LinkerScripts/kernel.ld


#######################################
# compiler flags
#######################################
# gcc flags
CFLAGS    += $(MCU) $(DEFS) $(OPT) $(INCLUDES)
CFLAGS    += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(dir $<)/$(@:.o=.list)
CFLAGS    += -Wall -fdata-sections -ffunction-sections -fno-common
CXXFLAGS  += $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit -fno-threadsafe-statics

# boot section ld flags
BSLDFLAGS += -Wl,-m,elf_i386 $(LDSCRIPT-BS) -ffreestanding -nostdlib

# boot loader ld flags
ifeq ($(CONFIG_VKLIBC), y)
BLDFLAGS  += $(MCU) $(LDSCRIPT-BL) -ffreestanding -nostdlib
else
BLDFLAGS  += $(MCU) $(LDSCRIPT-BL) -specs=nosys.specs -lc -lm -lnosys
endif
BLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-bl.map,--cref
BLDFLAGS  += -Wl,--gc-sections
BLDFLAGS  += -Wl,--no-warn-rwx-segment
BLDFLAGS  += -Wl,-m,elf_i386

# kernel ld flags
ifeq ($(CONFIG_VKLIBC), y)
KLDFLAGS  += $(MCU) $(LDSCRIPT-KERNEL) -ffreestanding -nostdlib
else
KLDFLAGS  += $(MCU) $(LDSCRIPT-KERNEL) -specs=nosys.specs -lc -lm -lnosys
endif
KLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-kernel.map,--cref
KLDFLAGS  += -Wl,--gc-sections
KLDFLAGS  += -Wl,--no-warn-rwx-segment
KLDFLAGS  += -Wl,-m,elf_i386

# mod ld flags
MLDFLAGS   = $(MCU) -T vk.scripts/ldscript/module.ld
MLDFLAGS  += -Wl,-Map=$(@:.mo=.map),--cref
MLDFLAGS  += -Wl,-r -Wl,-Bsymbolic
MLDFLAGS  += -Wl,--no-warn-rwx-segment
MLDFLAGS  += -Wl,-m,elf_i386
