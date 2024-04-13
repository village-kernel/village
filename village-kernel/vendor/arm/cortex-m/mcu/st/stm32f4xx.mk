###########################################################################
# Makefile
# The Makefile of stm32f4xx
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# arch
######################################
# flash CFG
FLASH_CFG := -f interface/stlink-v2.cfg -f target/stm32f4x.cfg

# MCU
MCU  := -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# defines
DEFS := -DARCH_ARM -DUSE_HAL_DRIVER -DSTM32F407xx -D'HSE_VALUE=((uint32_t)8000000)'

# link script
LDSCRIPT-KERNEL-$(CONFIG_STM32F405RG) := -T village-kernel/vendor/arm/cortex-m/mcu/st/LinkerScripts/STM32F4xx/STM32F405RG_flash.ld
LDSCRIPT-KERNEL-$(CONFIG_STM32F407ZE) := -T village-kernel/vendor/arm/cortex-m/mcu/st/LinkerScripts/STM32F4xx/STM32F407ZE_flash.ld
LDSCRIPT-KERNEL-$(CONFIG_STM32F407ZG) := -T village-kernel/vendor/arm/cortex-m/mcu/st/LinkerScripts/STM32F4xx/STM32F407ZG_flash.ld


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
inc-$(CONFIG_STM32F4xx) += village-kernel/vendor/arm/cortex-m/mcu/st/CMSIS/Device/ST/STM32F4xx/Include
inc-$(CONFIG_STM32F4xx) += village-kernel/vendor/arm/cortex-m/mcu/st/STM32F4xx_HAL_Driver/Inc
inc-$(CONFIG_STM32F4xx) += village-kernel/vendor/arm/cortex-m/mcu/st/STM32F4xx_HAL_Driver/Inc/Legacy

src-$(CONFIG_STM32F4xx) += village-kernel/vendor/arm/cortex-m/mcu/st/CMSIS/Device/ST/STM32F4xx/Source/Templates
src-$(CONFIG_STM32F4xx) += village-kernel/vendor/arm/cortex-m/mcu/st/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc

ifeq ($(CONFIG_MANUFACTURER_HAL_DRIVER), y)
src-$(CONFIG_STM32F4xx) += village-kernel/vendor/arm/cortex-m/mcu/st/STM32F4xx_HAL_Driver/Src
endif


######################################
# objects
######################################
objs-$(CONFIG_STM32F4xx)   += system_stm32f4xx.o
objs-$(CONFIG_STM32F401xc) += startup_stm32f401xc.o
objs-$(CONFIG_STM32F401xe) += startup_stm32f401xe.o
objs-$(CONFIG_STM32F405xx) += startup_stm32f405xx.o
objs-$(CONFIG_STM32F407xx) += startup_stm32f407xx.o
objs-$(CONFIG_STM32F410cx) += startup_stm32f410cx.o
objs-$(CONFIG_STM32F410rx) += startup_stm32f410rx.o
objs-$(CONFIG_STM32F410tx) += startup_stm32f410tx.o
objs-$(CONFIG_STM32F411xe) += startup_stm32f411xe.o
objs-$(CONFIG_STM32F412cx) += startup_stm32f412cx.o
objs-$(CONFIG_STM32F412rx) += startup_stm32f412rx.o
objs-$(CONFIG_STM32F412vx) += startup_stm32f412vx.o
objs-$(CONFIG_STM32F412zx) += startup_stm32f412zx.o
objs-$(CONFIG_STM32F413xx) += startup_stm32f413xx.o
objs-$(CONFIG_STM32F415xx) += startup_stm32f415xx.o
objs-$(CONFIG_STM32F417xx) += startup_stm32f417xx.o
objs-$(CONFIG_STM32F423xx) += startup_stm32f423xx.o
objs-$(CONFIG_STM32F427xx) += startup_stm32f427xx.o
objs-$(CONFIG_STM32F429xx) += startup_stm32f429xx.o
objs-$(CONFIG_STM32F437xx) += startup_stm32f437xx.o
objs-$(CONFIG_STM32F439xx) += startup_stm32f439xx.o
objs-$(CONFIG_STM32F446tx) += startup_stm32f446tx.o
objs-$(CONFIG_STM32F469xx) += startup_stm32f469xx.o
objs-$(CONFIG_STM32F479xx) += startup_stm32f479xx.o

ifeq ($(CONFIG_MANUFACTURER_HAL_DRIVER), y)
-include village-kernel/vendor/arm/cortex-m/mcu/st/STM32F4xx_HAL_Driver/Makefile
endif
