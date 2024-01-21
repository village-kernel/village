###########################################################################
# Makefile
# The Makefile of vk.hardware
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
libs-y                          += hw


######################################
# paths
######################################
inc-y                            += vk.hardware/x86/bios/cpu/gcc
inc-y                            += vk.hardware/x86/bios/cpu/core
inc-y                            += vk.hardware/x86/bios/cpu/hw/inc
    
src-y                            += vk.hardware/x86/bios/cpu/gcc
src-y                            += vk.hardware/x86/bios/cpu/core
src-y                            += vk.hardware/x86/bios/cpu/hw/src


######################################
# objects
######################################
ifneq ($(CONFIG_VKLIBC), y)
objs-hw-y                        += syscalls.o
objs-hw-y                        += sysmem.o
endif
objs-hw-y                        += i386.o

objs-y                           += crt0.o
objs-y                           += isr.o


######################################
# arch
######################################
# MCU
MCU   := -m32 -mno-sse

# MCU EM
MCUEM := -melf_i386

# defines
DEFS  := -DARCH_X86

# link script
LDSCRIPT-BOOT   := -T vk.hardware/x86/bios/cpu/lds/boot.ld
LDSCRIPT-KERNEL := -T vk.hardware/x86/bios/cpu/lds/kernel.ld


#######################################
# compiler flags
#######################################
# gcc flags
CFLAGS    += $(MCU) $(DEFS) $(OPT) $(INCLUDES)
CFLAGS    += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(dir $<)/$(@:.o=.list)
CFLAGS    += -Wall -fdata-sections -ffunction-sections -fno-common
CXXFLAGS  += $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit -fno-threadsafe-statics

# boot loader ld flags
BLDFLAGS  += $(LDSCRIPT-BOOT) -ffreestanding -nostdlib
BLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-bl.map,--cref
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
KLDFLAGS  += -Wl,-static -pie

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
APPLDFLAGS  += -pie -e main
