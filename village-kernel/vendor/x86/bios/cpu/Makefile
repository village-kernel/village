###########################################################################
# Makefile
# The Makefile of village-kernel/vendor
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
inc-y                            += village-kernel/vendor/x86/bios/cpu/core
inc-y                            += village-kernel/vendor/x86/bios/cpu/crt0

src-y                            += village-kernel/vendor/x86/bios/cpu/core 
src-y                            += village-kernel/vendor/x86/bios/cpu/crt0


######################################
# objects
######################################
objs-hw-y                        += i386.o
objs-y                           += crt0_kernel.o


######################################
# arch
######################################
# MCU
MCU   := -m32 -mno-sse

# MCU EM
MCUEM := -melf_i386

# defines
DEFS  := -DARCH_X86


######################################
# link script
######################################
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
