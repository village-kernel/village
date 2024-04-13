###########################################################################
# Makefile
# The Makefile of village-kernel/vendor/x86/bios
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
LDSCRIPT-KERNEL := -T village-kernel/vendor/x86/bios/cpu/lds/kernel.lds


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
inc-y                                 += village-kernel/vendor/x86/bios/cpu/crt0
src-y                                 += village-kernel/vendor/x86/bios/cpu/crt0

inc-y                                 += village-kernel/vendor/x86/bios/driver/inc
src-y                                 += village-kernel/vendor/x86/bios/driver/src

objs-y                                += crt0_kernel.o
objs-$(CONFIG_ATALBADISK)             += AtaLbaDisk.o
objs-$(CONFIG_BOCHSVBE)               += BochsVBE.o
objs-$(CONFIG_GENERALTIMER)           += GeneralTimer.o
objs-$(CONFIG_PS2KEYBOARD)            += PS2KeyBoard.o
objs-$(CONFIG_PS2MOUSE)               += PS2Mouse.o
objs-$(CONFIG_SERIALPORT)             += SerialPort.o


######################################
# libhw
######################################
libs-y                                += hw

inc-y                                 += village-kernel/vendor/x86/bios/cpu/core
src-y                                 += village-kernel/vendor/x86/bios/cpu/core 

inc-y                                 += village-kernel/vendor/x86/bios/hal/inc
src-y                                 += village-kernel/vendor/x86/bios/hal/src

objs-hw-y                             += i386.o
objs-hw-$(CONFIG_HAL_PCI_CONTROLLER)  += PCIController.o
objs-hw-$(CONFIG_HAL_PS2_CONTROLLER)  += PS2Controller.o
