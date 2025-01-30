###########################################################################
# Makefile
# The Makefile of village-machine/platform/ia32/legacy
#
# $Copyright: Copyright (C) village
############################################################################

#######################################
# compiler flags
#######################################
# CPU
MCU                                   := -m32 -mno-sse -mno-mmx 

# CPU EM
EMULATION                             := -melf_i386 

# link script
LDSCRIPT-KERNEL                       := -T village-machine/platform/ia32legacy/lds/kernel.lds

# gcc flags
CFLAGS                                += $(MCU) -DARCH_X86
CFLAGS                                += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(dir $<)/$(@:.o=.list)
CFLAGS                                += -Wall -fdata-sections -ffunction-sections -fno-common
CXXFLAGS                              += $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit -fno-threadsafe-statics

# kernel ld flags
LDFLAGS-KERNEL                        += $(MCU) $(LDSCRIPT-KERNEL)
LDFLAGS-KERNEL                        += -ffreestanding -nostdlib
LDFLAGS-KERNEL                        += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-kernel.map,--cref
LDFLAGS-KERNEL                        += -Wl,--gc-sections
LDFLAGS-KERNEL                        += -Wl,--no-warn-rwx-segment
LDFLAGS-KERNEL                        += -Wl,-m,elf_i386
LDFLAGS-KERNEL                        += -Wl,-static -pie


######################################
# crt0
######################################
inc-y                                 += village-machine/platform/ia32legacy/crt0
src-y                                 += village-machine/platform/ia32legacy/crt0

objs-y                                += crt0_kernel.o


######################################
# core
######################################
inc-y                                 += village-machine/platform/ia32legacy/core
src-y                                 += village-machine/platform/ia32legacy/core 

objs-y                                += i386.o
objs-y                                += div64.o


######################################
# hal
######################################
inc-y                                 += village-machine/platform/ia32legacy/hal/inc
src-y                                 += village-machine/platform/ia32legacy/hal/src

objs-$(CONFIG_IA32LEGACY_DRV_PCI)     += vk_pci_controller.o
objs-$(CONFIG_IA32LEGACY_DRV_PS2)     += vk_ps2_controller.o
