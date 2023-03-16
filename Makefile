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


#######################################
# paths
#######################################
# Build path
BUILD_DIR := vk.build


#######################################
# remove
#######################################
ifeq ($(OS), Windows_NT)
  RM = del /Q
else
  RM = rm -rf
endif


######################################
# include other makefile
######################################
-include vk.application/Makefile
-include vk.hardware/Makefile
-include vk.kernel/Makefile
-include vk.gui/Makefile


#######################################
# cross compile tool
#######################################
GCC_PREFIX ?= $(CONFIG_CROSS_COMPILE:"%"=%)
CPP = $(GCC_PREFIX)g++
CC  = $(GCC_PREFIX)gcc
AS  = $(GCC_PREFIX)gcc -x assembler-with-cpp
CP  = $(GCC_PREFIX)objcopy
SZ  = $(GCC_PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S


# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


# flash firmware
flash:
	openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg \
		-c "program $(BUILD_DIR)/$(TARGET).bin verify reset exit 0x08000000"


#######################################
# build the application
#######################################
INCLUDES =  $(addprefix "-I", $(inc-y))
OBJECTS  =  $(addprefix $(BUILD_DIR)/, $(objs-y))
vpath %.s   $(sort $(src-y))
vpath %.c   $(sort $(src-y))
vpath %.cpp $(sort $(src-y))

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
	$(Q)mkdir $@

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
	$(Q)$(RM) include

distclean:
	$(Q)$(RM) $(BUILD_DIR)
	$(Q)$(RM) include
	$(Q)$(MAKE) -C $(Scripts)/kconfig clean


#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)
