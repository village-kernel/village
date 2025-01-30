###########################################################################
# Makefile
# The Makefile of stm32f4xx
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# flags
######################################
# flash cmd
FLASH_CMD := openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg -c "program $(BUILD_DIR)/$(TARGET)-kernel.hex verify reset exit"

# MCU
MCU       := -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# defines
DEFS      := -DARCH_ARM -DSTM32F407xx -D'HSE_VALUE=((uint32_t)8000000)'

# link script
LDSCRIPT-KERNEL-$(CONFIG_STM32F405RG)            := -T village-machine/platform/stm32f4xx/lds/STM32F405RG_flash.ld
LDSCRIPT-KERNEL-$(CONFIG_STM32F407ZE)            := -T village-machine/platform/stm32f4xx/lds/STM32F407ZE_flash.ld
LDSCRIPT-KERNEL-$(CONFIG_STM32F407ZG)            := -T village-machine/platform/stm32f4xx/lds/STM32F407ZG_flash.ld


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
inc-y                                            += village-machine/platform/stm32f4xx/cmsis
src-y                                            += village-machine/platform/stm32f4xx/core/src

objs-$(CONFIG_STM32F401xc)                       += crt0_kernel_stm32f401xc.o
objs-$(CONFIG_STM32F401xe)                       += crt0_kernel_stm32f401xe.o
objs-$(CONFIG_STM32F405xx)                       += crt0_kernel_stm32f405xx.o
objs-$(CONFIG_STM32F407xx)                       += crt0_kernel_stm32f407xx.o
objs-$(CONFIG_STM32F410cx)                       += crt0_kernel_stm32f410cx.o
objs-$(CONFIG_STM32F410rx)                       += crt0_kernel_stm32f410rx.o
objs-$(CONFIG_STM32F410tx)                       += crt0_kernel_stm32f410tx.o
objs-$(CONFIG_STM32F411xe)                       += crt0_kernel_stm32f411xe.o
objs-$(CONFIG_STM32F412cx)                       += crt0_kernel_stm32f412cx.o
objs-$(CONFIG_STM32F412rx)                       += crt0_kernel_stm32f412rx.o
objs-$(CONFIG_STM32F412vx)                       += crt0_kernel_stm32f412vx.o
objs-$(CONFIG_STM32F412zx)                       += crt0_kernel_stm32f412zx.o
objs-$(CONFIG_STM32F413xx)                       += crt0_kernel_stm32f413xx.o
objs-$(CONFIG_STM32F415xx)                       += crt0_kernel_stm32f415xx.o
objs-$(CONFIG_STM32F417xx)                       += crt0_kernel_stm32f417xx.o
objs-$(CONFIG_STM32F423xx)                       += crt0_kernel_stm32f423xx.o
objs-$(CONFIG_STM32F427xx)                       += crt0_kernel_stm32f427xx.o
objs-$(CONFIG_STM32F429xx)                       += crt0_kernel_stm32f429xx.o
objs-$(CONFIG_STM32F437xx)                       += crt0_kernel_stm32f437xx.o
objs-$(CONFIG_STM32F439xx)                       += crt0_kernel_stm32f439xx.o
objs-$(CONFIG_STM32F446tx)                       += crt0_kernel_stm32f446tx.o
objs-$(CONFIG_STM32F469xx)                       += crt0_kernel_stm32f469xx.o
objs-$(CONFIG_STM32F479xx)                       += crt0_kernel_stm32f479xx.o


######################################
# core
######################################
inc-y                                            += village-machine/platform/stm32f4xx/core/inc
src-y                                            += village-machine/platform/stm32f4xx/crt0

objs-y                                           += system_stm32f4xx.o


######################################
# hal
######################################
inc-y                                            += village-machine/platform/stm32f4xx/hal/inc
src-y                                            += village-machine/platform/stm32f4xx/hal/src

objs-$(CONFIG_STM32F4XX_DRV_HAL)                 += vk_drv_hal.o
objs-$(CONFIG_STM32F4XX_DRV_GPIO)                += vk_drv_gpio.o
objs-$(CONFIG_STM32F4XX_DRV_NVIC)                += vk_drv_nvic.o
objs-$(CONFIG_STM32F4XX_DRV_USART)               += vk_drv_usart.o
objs-$(CONFIG_STM32F4XX_DRV_SPI)                 += vk_drv_spi.o
objs-$(CONFIG_STM32F4XX_DRV_I2C)                 += vk_drv_i2c.o
objs-$(CONFIG_STM32F4XX_DRV_DMA)                 += vk_drv_dma.o
objs-$(CONFIG_STM32F4XX_DRV_FSMC)                += vk_drv_fsmc.o
objs-$(CONFIG_STM32F4XX_DRV_EXTI)                += vk_drv_exti.o
objs-$(CONFIG_STM32F4XX_DRV_USB)                 += vk_drv_usb.o
