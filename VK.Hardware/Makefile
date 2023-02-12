###########################################################################
# Makefile
# The Makefile of VK.Hardware
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# includes
######################################
INCLUDES += -I./VK.Hardware/BSP/ST/stm32f4xx/CMSIS/Include \
	-I./VK.Hardware/BSP/ST/stm32f4xx/CMSIS/Device/ST/STM32F4xx/Include \
	-I./VK.Hardware/BSP/ST/stm32f4xx/STM32F4xx_HAL_Driver/Inc \
	-I./VK.Hardware/BSP/ST/stm32f4xx/STM32F4xx_HAL_Driver/Inc/Legacy \
	-I./VK.Hardware/HAL/ST/stm32f4xx/inc \

######################################
# sources
######################################
# ASM sources
ASM_SOURCES += VK.Hardware/BSP/ST/stm32f4xx/StartupFiles/startup_stm32f407xx.s

# C sources
C_SOURCES += $(wildcard ./VK.Hardware/BSP/ST/stm32f4xx/STM32F4xx_HAL_Driver/Src/*.c) \
	$(wildcard ./VK.Hardware/BSP/ST/stm32f4xx/CMSIS/Source/*.c)

# Cpp sources
CPP_SOURCES += $(wildcard ./VK.Hardware/HAL/ST/stm32f4xx/src/*.cpp)


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
LDSCRIPT := VK.Hardware/BSP/ST/stm32f4xx/LinkerScripts/STM32F407ZE_flash.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR = 

# LDFLAGS
LDFLAGS := $(MCU) -specs=nano.specs -specs=nosys.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
