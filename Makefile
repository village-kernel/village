###########################################################################
# Makefile
# The Top Makefile of village-target project
#
# $Copyright: Copyright (C) village
############################################################################
-include .config

######################################
# target
######################################
TARGET := village

######################################
# building variables
######################################
# optimization
OPT ?= $(CONFIG_OPT:"%"=%)

# debug build?
ifeq ($(CONFIG_DEBUG), y)
  DEBUG ?= 1
else
  DEBUG ?= 0
endif

# silence build
ifeq ($(CONFIG_VERBOSE_MODE), y)
  Q = 
else
  Q = @
endif

export Q


#######################################
# paths
#######################################
# Build path
BUILD_DIR   := vk.build
MODULES_DIR := $(BUILD_DIR)/modules


######################################
# include other makefile
######################################
-include vk.application/Makefile
-include vk.hardware/Makefile
-include vk.kernel/Makefile
-include vk.gui/Makefile


#######################################
# tasks
#######################################
# default action: build all
all: bootloader kernel module

# flash firmware
flash:
	openocd $(FLASH_CFG) -c "program $(BUILD_DIR)/$(TARGET).bin verify reset exit 0x08000000"


#######################################
# cross compile tool
#######################################
GCC_PREFIX ?= $(CONFIG_CROSS_COMPILE:"%"=%)
CXX = $(GCC_PREFIX)g++
CC  = $(GCC_PREFIX)gcc
AS  = $(GCC_PREFIX)gcc -x assembler-with-cpp
AR  = $(GCC_PREFIX)ar
LD  = $(GCC_PREFIX)ld
CP  = $(GCC_PREFIX)objcopy
SZ  = $(GCC_PREFIX)size
ST  = $(GCC_PREFIX)strip
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S


#######################################
# setting build environment
#######################################
INCLUDES  = $(addprefix "-I", $(inc-y) $(inc-m))
VPATH     = $(addprefix $(BUILD_DIR)/, $(src-y) $(src-m)) $(src-y) $(src-m)


#######################################
# compiler flags
#######################################
ifeq ($(DEBUG), 1)
CFLAGS    += -g -gdwarf-2
endif

ifneq ($(CONFIG_ENVIRONMENT), y)
CFLAGS    += -DKBUILD_NO_ENVIRONNEMNT
endif

# gcc flags
CFLAGS    += $(MCU) $(DEFS) $(OPT) $(INCLUDES)
CFLAGS    += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(dir $<)/$(@:.o=.lst)
CFLAGS    += -MMD -MP -MF"$(BUILD_DIR)/$(dir $<)/$(@:%.o=%.d)"
CFLAGS    += -Wall -fdata-sections -ffunction-sections
CFLAGS    += -mword-relocations -mlong-calls -fno-common
CXXFLAGS  += $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit

# bootloader ld flags
BLDFLAGS  += $(MCU) $(LDSCRIPT-y) -specs=nano.specs -lc -lm -lnosys
BLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-boot.map,--cref
BLDFLAGS  += -Wl,--gc-sections
BLDFLAGS  += -Wl,--no-warn-rwx-segment

# kernel ld flags
KLDFLAGS  += $(MCU) $(LDSCRIPT-y) -specs=nano.specs -lc -lm -lnosys
KLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-kernel.map,--cref
KLDFLAGS  += -Wl,--gc-sections
KLDFLAGS  += -Wl,--no-warn-rwx-segment

# mod ld flags
MLDFLAGS   = $(MCU) -T vk.scripts/ldscript/module.ld
MLDFLAGS  += -Wl,-Map=$(@:.mo=.map),--cref
MLDFLAGS  += -r -Bsymbolic -nostartfiles


#######################################
# mixed compiling
#######################################
%.o: %.s
	$(Q)echo Compiling $@
	$(Q)mkdir -p $(BUILD_DIR)/$(dir $<)
	$(Q)$(AS) -c $(CFLAGS) $< -o $(BUILD_DIR)/$(dir $<)/$@

%.o: %.c
	$(Q)echo Compiling $@
	$(Q)mkdir -p $(BUILD_DIR)/$(dir $<)
	$(Q)$(CC) -c $(CFLAGS) $< -o $(BUILD_DIR)/$(dir $<)/$@

%.o: %.cpp
	$(Q)echo Compiling $@
	$(Q)mkdir -p $(BUILD_DIR)/$(dir $<)
	$(Q)$(CXX) -c $(CXXFLAGS) $< -o $(BUILD_DIR)/$(dir $<)/$@

%.hex: %.elf
	$(Q)echo output $@
	$(Q)$(HEX) $< $@

%.bin: %.elf
	$(Q)echo output $@
	$(Q)$(BIN) $< $@


#######################################
# build the bootloader
#######################################
bootloader: $(objs-y)
	$(Q)$(MAKE) \
	$(BUILD_DIR)/$(TARGET)-boot.elf \
	$(BUILD_DIR)/$(TARGET)-boot.hex \
	$(BUILD_DIR)/$(TARGET)-boot.bin

$(BUILD_DIR)/$(TARGET)-boot.elf: $(objs-y)
	$(Q)echo output $@
	$(Q)$(CXX) $(BLDFLAGS) $^ -o $@
	$(Q)$(SZ) $@


#######################################
# build the kernel
#######################################
kernel: $(objs-y)
	$(Q)$(MAKE) \
	$(BUILD_DIR)/$(TARGET)-kernel.elf \
	$(BUILD_DIR)/$(TARGET)-kernel.hex \
	$(BUILD_DIR)/$(TARGET)-kernel.bin

$(BUILD_DIR)/$(TARGET)-kernel.elf: $(objs-y)
	$(Q)echo output $@
	$(Q)$(CXX) $(KLDFLAGS) $^ -o $@
	$(Q)$(SZ) $@


#######################################
# build the modules
#######################################
module: $(objs-m)
	$(Q)mkdir -p $(MODULES_DIR)
	$(Q)$(MAKE) $(addprefix $(MODULES_DIR)/, $(objs-m:.o=.mo))

$(MODULES_DIR)/%.mo: %.o
	$(Q)echo Generating $(notdir $@)
	$(Q)$(CXX) $(MLDFLAGS) $< -o $(@:.mo=.elf)
	$(Q)$(ST) -g -o $@ $(@:.mo=.elf)


#######################################
# menuconfig
#######################################
Scripts      := ./vk.scripts
Kconfig      := ./Kconfig

menuconfig: $(Scripts)/kconfig/mconf
	$(Q)$< $(Kconfig)

silentoldconfig: $(Scripts)/kconfig/conf
	$(Q)mkdir -p include/config include/generated
	$(Q)$< -s --$@ $(Kconfig)

$(Scripts)/kconfig/mconf:
	$(Q)$(MAKE) -C $(Scripts)/kconfig

$(Scripts)/kconfig/conf:
	$(Q)$(MAKE) -C $(Scripts)/kconfig


#######################################
# clean up
#######################################
clean:
	$(Q)rm -rf $(BUILD_DIR)
	$(Q)rm -rf $(MODULES_DIR)
	$(Q)rm -rf include

modclean:
	$(Q)rm -rf $(MODULES_DIR)

distclean: clean
	$(Q)$(MAKE) -C $(Scripts)/kconfig clean
