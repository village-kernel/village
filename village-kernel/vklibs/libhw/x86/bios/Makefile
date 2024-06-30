###########################################################################
# Makefile
# The Makefile of village-kernel/vklibs/libhw/x86/bios
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# vklibs/libhw
######################################
# CPU
MCU  := -m32 -mno-sse -mno-mmx 

# CPU EM
EMULATION := -melf_i386 

# link script
LDSCRIPT-KERNEL := -T village-kernel/vklibs/libhw/x86/bios/cpu/lds/kernel.lds


#######################################
# compiler flags
#######################################
# gcc flags
CFLAGS    += $(MCU) -DARCH_X86
CFLAGS    += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(dir $<)/$(@:.o=.list)
CFLAGS    += -Wall -fdata-sections -ffunction-sections -fno-common
CXXFLAGS  += $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit -fno-threadsafe-statics

# kernel ld flags
LDFLAGS-KERNEL  += $(MCU) $(LDSCRIPT-KERNEL)
LDFLAGS-KERNEL  += -ffreestanding -nostdlib
LDFLAGS-KERNEL  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-kernel.map,--cref
LDFLAGS-KERNEL  += -Wl,--gc-sections
LDFLAGS-KERNEL  += -Wl,--no-warn-rwx-segment
LDFLAGS-KERNEL  += -Wl,-m,elf_i386
LDFLAGS-KERNEL  += -Wl,-static -pie


######################################
# kernel code
######################################
inc-y                                 += village-kernel/vklibs/libhw/x86/bios/cpu/crt0
src-y                                 += village-kernel/vklibs/libhw/x86/bios/cpu/crt0

objs-y                                += crt0_kernel.o


######################################
# libhw
######################################
libs-y                                += hw

inc-y                                 += village-kernel/vklibs/libhw/x86/bios/cpu/core
src-y                                 += village-kernel/vklibs/libhw/x86/bios/cpu/core 

inc-y                                 += village-kernel/vklibs/libhw/x86/bios/hal/inc
src-y                                 += village-kernel/vklibs/libhw/x86/bios/hal/src

objs-hw-y                             += i386.o
objs-hw-y                             += div64.o
objs-hw-$(CONFIG_HAL_PCI_CONTROLLER)  += PCIController.o
objs-hw-$(CONFIG_HAL_PS2_CONTROLLER)  += PS2Controller.o
