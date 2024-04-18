###########################################################################
# Makefile
# The Makefile of village-kernel/arch/x86/bios
#
# $Copyright: Copyright (C) village
############################################################################

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
LDSCRIPT-KERNEL := -T village-kernel/arch/x86/bios/cpu/lds/kernel.lds


#######################################
# compiler flags
#######################################
# gcc flags
CFLAGS    += $(MCU) $(DEFS) $(OPT) $(INCLUDES)
CFLAGS    += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(dir $<)/$(@:.o=.list)
CFLAGS    += -Wall -fdata-sections -ffunction-sections -fno-common
CXXFLAGS  += $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit -fno-threadsafe-statics

# kernel ld flags
KLDFLAGS  += $(MCU) $(LDSCRIPT-KERNEL)
KLDFLAGS  += -ffreestanding -nostdlib
KLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-kernel.map,--cref
KLDFLAGS  += -Wl,--gc-sections
KLDFLAGS  += -Wl,--no-warn-rwx-segment
KLDFLAGS  += -Wl,-m,elf_i386
KLDFLAGS  += -Wl,-static -pie


######################################
# kernel code
######################################
inc-y                                 += village-kernel/arch/x86/bios/cpu/crt0
src-y                                 += village-kernel/arch/x86/bios/cpu/crt0

objs-y                                += crt0_kernel.o


######################################
# libhw
######################################
libs-y                                += hw

inc-y                                 += village-kernel/arch/x86/bios/cpu/core
src-y                                 += village-kernel/arch/x86/bios/cpu/core 

inc-y                                 += village-kernel/arch/x86/bios/hal/inc
src-y                                 += village-kernel/arch/x86/bios/hal/src

objs-hw-y                             += i386.o
objs-hw-$(CONFIG_HAL_PCI_CONTROLLER)  += PCIController.o
objs-hw-$(CONFIG_HAL_PS2_CONTROLLER)  += PS2Controller.o
