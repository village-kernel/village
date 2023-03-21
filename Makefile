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
TARGET := village-target

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
# remove
#######################################
ifeq ($(OS), Windows_NT)
  RM = del /Q
else
  RM = rm -rf
endif


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
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


# build modules
modules: $(MODULES_DIR)/$(objs-m:.o=.mo)


# flash firmware
flash:
	openocd $(FLASH_CFG) -c "program $(BUILD_DIR)/$(TARGET).bin verify reset exit 0x08000000"


#######################################
# cross compile tool
#######################################
GCC_PREFIX ?= $(CONFIG_CROSS_COMPILE:"%"=%)
CPP = $(GCC_PREFIX)g++
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
vpath %.s   $(sort $(src-y) $(src-m))
vpath %.c   $(sort $(src-y) $(src-m))
vpath %.cpp $(sort $(src-y) $(src-m))


#######################################
# build the kernel
#######################################
OBJECTS  =  $(addprefix $(BUILD_DIR)/, $(objs-y))

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(Q)echo Compiling $(notdir $@)
	$(Q)$(AS) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(Q)echo Compiling $(notdir $@)
	$(Q)$(CC) -c $(CFLAGS) $(INCLUDES) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	$(Q)echo Compiling $(notdir $@)
	$(Q)$(CPP) -c $(CFLAGS) $(INCLUDES) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(Q)echo output $@
	$(Q)$(CPP) $(OBJECTS) $(LDFLAGS) -o $@
	$(Q)$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(Q)echo output $@
	$(Q)$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(Q)echo output $@
	$(Q)$(BIN) $< $@

$(BUILD_DIR):
	$(Q)mkdir -p $@


#######################################
# build the modules
#######################################
MODULES   =  $(addprefix $(MODULES_DIR)/, $(objs-m))

MCFLAGS   = $(MCU) $(C_DEFS) $(C_MACROS) $(OPT) -mword-relocations -mlong-calls -fno-common
MCPPFLAGS = $(MCFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit 
MLDFLAGS  = $(MCU) -r -Bsymbolic -nostartfiles -T vk.scripts/ldscript/module.ld -Wl,-Map=$(@:.mo=.map)

$(MODULES_DIR)/%.o: %.s Makefile | $(MODULES_DIR)
	$(Q)echo Compiling $(notdir $@)
	$(Q)$(AS) -c $(MCFLAGS) $(INCLUDES) -Wa,-a,-ad,-alms=$(MODULES_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(MODULES_DIR)/%.o: %.c Makefile | $(MODULES_DIR)
	$(Q)echo Compiling $(notdir $@)
	$(Q)$(CC) -c $(MCFLAGS) $(INCLUDES) -Wa,-a,-ad,-alms=$(MODULES_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(MODULES_DIR)/%.o: %.cpp Makefile | $(MODULES_DIR)
	$(Q)echo Compiling $(notdir $@)
	$(Q)$(CPP) -c $(MCPPFLAGS) $(INCLUDES) -Wa,-a,-ad,-alms=$(MODULES_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(MODULES_DIR)/%.mo: $(MODULES) Makefile
	$(Q)echo Making $(notdir $@)
	$(Q)$(CC) $(MLDFLAGS) $< -o $(@:.mo=.elf)
	$(Q)$(ST) -g -o $@ $(@:.mo=.elf)

$(MODULES_DIR):
	$(Q)mkdir -p $@


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
	$(Q)$(RM) $(BUILD_DIR)
	$(Q)$(RM) $(MODULES_DIR)
	$(Q)$(RM) include

distclean: clean
	$(Q)$(MAKE) -C $(Scripts)/kconfig clean


#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)
-include $(wildcard $(MODULES_DIR)/*.d)
