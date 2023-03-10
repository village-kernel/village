###########################################################################
# Makefile
# The Top Makefile of village-target project
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# target
######################################
TARGET := village-target

######################################
# building variables
######################################
# silence build
SILENCE = 1
# debug build?
DEBUG = 1
# optimization
OPT = -O0


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
# includes
######################################
-include vk.application/Makefile
-include vk.hardware/Makefile
-include vk.kernel/Makefile
-include vk.gui/Makefile


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CPP = $(GCC_PATH)/$(PREFIX)g++
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CPP = $(PREFIX)g++
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
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
# list of ASM program objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
# list of c objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of cpp objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

ifeq ($(SILENCE), 1)
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@echo $(notdir $@)
	@$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@echo $(notdir $@)
	@$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	@echo $(notdir $@)
	@$(CPP) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@echo output $@
	@$(CPP) $(OBJECTS) $(LDFLAGS) -o $@
	@$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo output $@
	@$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo output $@
	@$(BIN) $< $@

$(BUILD_DIR):
	@mkdir $@
else
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	$(CPP) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CPP) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@
endif


#######################################
# menuconfig
#######################################
Scripts      := ./vk.scripts
Kconfig      := ./Kconfig

menuconfig: $(Scripts)/kconfig/mconf
	@$< $(Kconfig)
	@$(MAKE) silentoldconfig

silentoldconfig: $(Scripts)/kconfig/conf
	@mkdir -p include/config include/generated
	@$< -s --$@ $(Kconfig)

$(Scripts)/kconfig/mconf:
	@$(MAKE) -C $(Scripts)/kconfig

$(Scripts)/kconfig/conf:
	@$(MAKE) -C $(Scripts)/kconfig


#######################################
# clean up
#######################################
clean:
	@$(RM) $(BUILD_DIR)
	@$(RM) include

distclean:
	@$(RM) $(BUILD_DIR)
	@$(RM) include
	@$(MAKE) -C $(Scripts)/kconfig clean


#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)
