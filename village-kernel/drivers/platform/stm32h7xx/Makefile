###########################################################################
# Makefile
# The Makefile of stm32h7xx
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# flags
######################################
# flash cmd
FLASH_CMD := openocd -f interface/stlink-v2.cfg -f target/stm32h7x.cfg -c "program $(BUILD_DIR)/$(TARGET)-kernel.hex verify reset exit"

# MCU
MCU       := -mcpu=cortex-m7 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard

# defines
DEFS      := -DARCH_ARM -D'HSE_VALUE=((uint32_t)25000000)'
ifeq ($(CONFIG_STM32H743II), y)
DEFS      += -DSTM32H743xx
else ifeq ($(CONFIG_STM32H750VB), y)
DEFS      += -DSTM32H750xx
endif

# link script
LDSCRIPT-KERNEL-$(CONFIG_STM32H743II)            := -T village-kernel/drivers/platform/stm32h7xx/lds/STM32H743II_flash.ld
LDSCRIPT-KERNEL-$(CONFIG_STM32H750VB)            := -T village-kernel/drivers/platform/stm32h7xx/lds/STM32H750VB_flash.ld


#######################################
# compiler flags
#######################################
# gcc flags
CFLAGS                                           += $(MCU) $(DEFS)
CFLAGS                                           += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(dir $<)/$(@:.o=.list)
CFLAGS                                           += -MMD -MP -MF"$(BUILD_DIR)/$(dir $<)/$(@:%.o=%.d)"
CFLAGS                                           += -Wall -fdata-sections -ffunction-sections -fno-common
CFLAGS                                           += -mword-relocations -mlong-calls
CXXFLAGS                                         += $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit -fno-threadsafe-statics

# kernel ld flags
LDFLAGS-KERNEL                                   += $(MCU) $(LDSCRIPT-KERNEL-y)
LDFLAGS-KERNEL                                   += -ffreestanding -nostdlib
LDFLAGS-KERNEL                                   += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-kernel.map,--cref
LDFLAGS-KERNEL                                   += -Wl,--gc-sections
LDFLAGS-KERNEL                                   += -Wl,--no-warn-rwx-segment
LDFLAGS-KERNEL                                   += -Wl,-static -pie


######################################
# crt0
######################################
inc-y                                            += village-kernel/drivers/platform/stm32h7xx/cmsis
src-y                                            += village-kernel/drivers/platform/stm32h7xx/crt0

objs-$(CONFIG_STM32H7a3xx)                       += crt0_kernel_stm32h7a3xx.o
objs-$(CONFIG_STM32H7a3xxq)                      += crt0_kernel_stm32h7a3xxq.o
objs-$(CONFIG_STM32H7b0xx)                       += crt0_kernel_stm32h7b0xx.o
objs-$(CONFIG_STM32H7b0xxq)                      += crt0_kernel_stm32h7b0xxq.o
objs-$(CONFIG_STM32H7b3xx)                       += crt0_kernel_stm32h7b3xx.o
objs-$(CONFIG_STM32H7b3xxq)                      += crt0_kernel_stm32h7b3xxq.o
objs-$(CONFIG_STM32H723xx)                       += crt0_kernel_stm32h723xx.o
objs-$(CONFIG_STM32H725xx)                       += crt0_kernel_stm32h725xx.o
objs-$(CONFIG_STM32H730xx)                       += crt0_kernel_stm32h730xx.o
objs-$(CONFIG_STM32H730xxq)                      += crt0_kernel_stm32h730xxq.o
objs-$(CONFIG_STM32H733xx)                       += crt0_kernel_stm32h733xx.o
objs-$(CONFIG_STM32H735xx)                       += crt0_kernel_stm32h735xx.o
objs-$(CONFIG_STM32H742xx)                       += crt0_kernel_stm32h742xx.o
objs-$(CONFIG_STM32H743xx)                       += crt0_kernel_stm32h743xx.o
objs-$(CONFIG_STM32H745xg)                       += crt0_kernel_stm32h745xg.o
objs-$(CONFIG_STM32H745xx)                       += crt0_kernel_stm32h745xx.o
objs-$(CONFIG_STM32H747xg)                       += crt0_kernel_stm32h747xg.o
objs-$(CONFIG_STM32H747xx)                       += crt0_kernel_stm32h747xx.o
objs-$(CONFIG_STM32H750xx)                       += crt0_kernel_stm32h750xx.o
objs-$(CONFIG_STM32H753xx)                       += crt0_kernel_stm32h753xx.o
objs-$(CONFIG_STM32H755xx)                       += crt0_kernel_stm32h755xx.o
objs-$(CONFIG_STM32H757xx)                       += crt0_kernel_stm32h757xx.o


######################################
# core
######################################
inc-y                                            += village-kernel/drivers/platform/stm32h7xx/core/inc
src-y                                            += village-kernel/drivers/platform/stm32h7xx/core/src

objs-y                                           += system_stm32h7xx.o


######################################
# hal
######################################
inc-y                                            += village-kernel/drivers/platform/stm32h7xx/hal/inc
src-y                                            += village-kernel/drivers/platform/stm32h7xx/hal/src

objs-$(CONFIG_STM32H7XX_DRV_HAL)                 += vk_drv_hal.o
objs-$(CONFIG_STM32H7XX_DRV_GPIO)                += vk_drv_gpio.o
objs-$(CONFIG_STM32H7XX_DRV_LTDC)                += vk_drv_ltdc.o
objs-$(CONFIG_STM32H7XX_DRV_NVIC)                += vk_drv_nvic.o
objs-$(CONFIG_STM32H7XX_DRV_USART)               += vk_drv_usart.o
objs-$(CONFIG_STM32H7XX_DRV_SDIO)                += vk_drv_sdio.o
objs-$(CONFIG_STM32H7XX_DRV_SPI)                 += vk_drv_spi.o
objs-$(CONFIG_STM32H7XX_DRV_I2C)                 += vk_drv_i2c.o
objs-$(CONFIG_STM32H7XX_DRV_DMA)                 += vk_drv_dma.o
objs-$(CONFIG_STM32H7XX_DRV_FSMC)                += vk_drv_fsmc.o
