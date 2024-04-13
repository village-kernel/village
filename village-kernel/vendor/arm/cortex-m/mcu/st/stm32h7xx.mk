###########################################################################
# Makefile
# The Makefile of stm32h7xx
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# arch
######################################
# flash CFG
FLASH_CFG := -f interface/stlink-v2.cfg -f target/stm32h7x.cfg

# MCU
MCU  := -mcpu=cortex-m7 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard

# defines
DEFS := -DARCH_ARM -DUSE_HAL_DRIVER -DSTM32H750xx -D'HSE_VALUE=((uint32_t)8000000)'

# link script
LDSCRIPT-KERNEL-$(CONFIG_STM32H750VB) := -T village-kernel/vendor/arm/cortex-m/mcu/st/LinkerScripts/STM32H7xx/STM32H750VB_flash.ld


#######################################
# compiler flags
#######################################
# gcc flags
CFLAGS    += $(MCU) $(DEFS) $(OPT) $(INCLUDES)
CFLAGS    += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(dir $<)/$(@:.o=.list)
CFLAGS    += -MMD -MP -MF"$(BUILD_DIR)/$(dir $<)/$(@:%.o=%.d)"
CFLAGS    += -Wall -fdata-sections -ffunction-sections -fno-common
CFLAGS    += -mword-relocations -mlong-calls
CXXFLAGS  += $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit -fno-threadsafe-statics

# kernel ld flags
KLDFLAGS  += $(MCU) $(LDSCRIPT-KERNEL-y)
KLDFLAGS  += -ffreestanding -nostdlib
KLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-kernel.map,--cref
KLDFLAGS  += -Wl,--gc-sections
KLDFLAGS  += -Wl,--no-warn-rwx-segment
KLDFLAGS  += -Wl,-static -pie


######################################
# paths
######################################
inc-$(CONFIG_STM32H7xx) += village-kernel/vendor/arm/cortex-m/mcu/st/CMSIS/Device/ST/STM32H7xx/Include
inc-$(CONFIG_STM32H7xx) += village-kernel/vendor/arm/cortex-m/mcu/st/STM32H7xx_HAL_Driver/Inc
inc-$(CONFIG_STM32H7xx) += village-kernel/vendor/arm/cortex-m/mcu/st/STM32H7xx_HAL_Driver/Inc/Legacy

src-$(CONFIG_STM32H7xx) += village-kernel/vendor/arm/cortex-m/mcu/st/CMSIS/Device/ST/STM32H7xx/Source/Templates
src-$(CONFIG_STM32H7xx) += village-kernel/vendor/arm/cortex-m/mcu/st/CMSIS/Device/ST/STM32H7xx/Source/Templates/gcc

ifeq ($(CONFIG_MANUFACTURER_HAL_DRIVER), y)
src-$(CONFIG_STM32H7xx) += village-kernel/vendor/arm/cortex-m/mcu/st/STM32H7xx_HAL_Driver/Src
endif


######################################
# objects
######################################
objs-$(CONFIG_STM32H7xx)    += system_stm32h7xx.c
objs-$(CONFIG_STM32H7a3xx)  += startup_stm32h7a3xx.o
objs-$(CONFIG_STM32H7a3xxq) += startup_stm32h7a3xxq.o
objs-$(CONFIG_STM32H7b0xx)  += startup_stm32h7b0xx.o
objs-$(CONFIG_STM32H7b0xxq) += startup_stm32h7b0xxq.o
objs-$(CONFIG_STM32H7b3xx)  += startup_stm32h7b3xx.o
objs-$(CONFIG_STM32H7b3xxq) += startup_stm32h7b3xxq.o
objs-$(CONFIG_STM32H723xx)  += startup_stm32h723xx.o
objs-$(CONFIG_STM32H725xx)  += startup_stm32h725xx.o
objs-$(CONFIG_STM32H730xx)  += startup_stm32h730xx.o
objs-$(CONFIG_STM32H730xxq) += startup_stm32h730xxq.o
objs-$(CONFIG_STM32H733xx)  += startup_stm32h733xx.o
objs-$(CONFIG_STM32H735xx)  += startup_stm32h735xx.o
objs-$(CONFIG_STM32H742xx)  += startup_stm32h742xx.o
objs-$(CONFIG_STM32H743xx)  += startup_stm32h743xx.o
objs-$(CONFIG_STM32H745xg)  += startup_stm32h745xg.o
objs-$(CONFIG_STM32H745xx)  += startup_stm32h745xx.o
objs-$(CONFIG_STM32H747xg)  += startup_stm32h747xg.o
objs-$(CONFIG_STM32H747xx)  += startup_stm32h747xx.o
objs-$(CONFIG_STM32H750xx)  += startup_stm32h750xx.o
objs-$(CONFIG_STM32H753xx)  += startup_stm32h753xx.o
objs-$(CONFIG_STM32H755xx)  += startup_stm32h755xx.o
objs-$(CONFIG_STM32H757xx)  += startup_stm32h757xx.o

ifeq ($(CONFIG_MANUFACTURER_HAL_DRIVER), y)
-include village-kernel/vendor/arm/cortex-m/mcu/st/STM32H7xx_HAL_Driver/Makefile
endif
