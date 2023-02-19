###########################################################################
# Makefile
# The Makefile of vk.hardware
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# includes
######################################
INCLUDES += -I./vk.hardware/BSP/ST/stm32f4xx/CMSIS/Include \
	-I./vk.hardware/BSP/ST/stm32f4xx/CMSIS/Device/ST/STM32F4xx/Include \
	-I./vk.hardware/BSP/ST/stm32f4xx/STM32F4xx_HAL_Driver/Inc \
	-I./vk.hardware/BSP/ST/stm32f4xx/STM32F4xx_HAL_Driver/Inc/Legacy \
	-I./vk.hardware/HAL/ST/stm32f4xx/inc \

######################################
# sources
######################################
# ASM sources
ASM_SOURCES += vk.hardware/BSP/ST/stm32f4xx/StartupFiles/startup_stm32f407xx.s

# C sources
C_SOURCES += $(wildcard ./vk.hardware/BSP/ST/stm32f4xx/STM32F4xx_HAL_Driver/Src/*.c) \
	$(wildcard ./vk.hardware/BSP/ST/stm32f4xx/CMSIS/Source/*.c) \
	$(wildcard ./vk.hardware/BSP/ST/stm32f4xx/GCC/*.c) \

# Cpp sources
CPP_SOURCES += $(wildcard ./vk.hardware/HAL/ST/stm32f4xx/src/*.cpp)


#######################################
# CFLAGS
#######################################
# MUC
MCU := -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=soft

# defines of gcc
C_DEFS := -DUSE_HAL_DRIVER -DSTM32F407xx

# macros of gcc
C_MACROS := -D'USE_STDPERIPH_DRIVER=1' -D'HSE_VALUE=((uint32_t)8000000)'

# compile gcc flags
CFLAGS += $(MCU) $(C_DEFS) $(C_MACROS) $(INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT := vk.hardware/BSP/ST/stm32f4xx/LinkerScripts/STM32F407ZE_flash.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR = 

# LDFLAGS
LDFLAGS := $(MCU) -specs=nano.specs -specs=nosys.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
