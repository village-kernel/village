###########################################################################
# Makefile
# The Makefile of vk.hardware
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
libs-y                       += hw

######################################
# paths
######################################
inc-y                        += vk.hardware/x86/cpu/gcc
inc-y                        += vk.hardware/x86/cpu/core
inc-y                        += vk.hardware/x86/cpu/hw/inc

src-y                        += vk.hardware/x86/cpu/gcc
src-y                        += vk.hardware/x86/cpu/core
src-y                        += vk.hardware/x86/cpu/hw/src

######################################
# objects
######################################
objs-bs-$(CONFIG_BOOTSECTION)    += boot.o

ifneq ($(CONFIG_VKLIBC), y)
objs-hw-y                        += syscalls.o
objs-hw-y                        += sysmem.o
endif
objs-hw-y                        += i386.o

objs-y                           += crt0.o
objs-y                           += init.o
objs-y                           += isr.o


######################################
# arch
######################################
# MCU
MCU  := -m32

# defines
DEFS := -DARCH_X86

# link script
LDSCRIPT-BS     := -T vk.hardware/x86/cpu/lds/bs.ld
LDSCRIPT-BL     := -T vk.hardware/x86/cpu/lds/bl.ld
LDSCRIPT-KERNEL := -T vk.hardware/x86/cpu/lds/kernel.ld


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
BSLDFLAGS += -Wl,--no-warn-rwx-segment

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
BLDFLAGS  += -Wl,-static

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
KLDFLAGS  += -Wl,-static -pie

# mod ld flags
ifeq ($(CONFIG_VKLIBC), y)
MLDFLAGS  += $(MCU) -ffreestanding -nostdlib
else
MLDFLAGS  += $(MCU) -specs=nosys.specs -lc -lm -lnosys
endif
MLDFLAGS  += -Wl,-Map=$(@:.mo=.map),--cref
MLDFLAGS  += -Wl,-Bsymbolic
MLDFLAGS  += -Wl,--gc-sections
MLDFLAGS  += -Wl,--no-warn-rwx-segment
MLDFLAGS  += -Wl,--unresolved-symbols=ignore-in-shared-libs
MLDFLAGS  += -Wl,-m,elf_i386
MLDFLAGS  += -pie

# application ld flags
ifeq ($(CONFIG_VKLIBC), y)
APPLDFLAGS  += $(MCU) -ffreestanding -nostdlib
else
APPLDFLAGS  += $(MCU) -specs=nosys.specs -lc -lm -lnosys
endif
APPLDFLAGS  += -Wl,-Map=$(@:.exec=.map),--cref
APPLDFLAGS  += -Wl,--gc-sections
APPLDFLAGS  += -Wl,--no-warn-rwx-segment
APPLDFLAGS  += -Wl,--unresolved-symbols=ignore-in-shared-libs
APPLDFLAGS  += -Wl,-m,elf_i386
#APPLDFLAGS  += -Wl,-static -pie -e main
APPLDFLAGS  += -pie -e main
