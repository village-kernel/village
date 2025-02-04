###########################################################################
# Makefile
# The Makefile of village-kernel/drivers
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-y                                 += village-kernel/drivers/machine/inc
src-y                                 += village-kernel/drivers/machine/src

objs-$(CONFIG_IA32LEGACY)             += vk_ia32legacy_devices.o
objs-$(CONFIG_STM32F4xx)              += vk_stm32f407_devices.o
objs-$(CONFIG_STM32H7xx)              += vk_stm32h743_devices.o


######################################
# platform
######################################
ifeq ($(CONFIG_IA32LEGACY), y)
inc-y                                 += village-kernel/drivers/platform/ia32legacy/inc
src-y                                 += village-kernel/drivers/platform/ia32legacy/src

objs-$(CONFIG_IA32LEGACY_DRV_PCI)     += vk_pci_controller.o
objs-$(CONFIG_IA32LEGACY_DRV_PS2)     += vk_ps2_controller.o

else ifeq ($(CONFIG_STM32F4xx), y)
inc-y                                 += village-kernel/drivers/platform/stm32f4xx/inc
src-y                                 += village-kernel/drivers/platform/stm32f4xx/src

objs-$(CONFIG_STM32F4XX_DRV_HAL)      += vk_drv_hal.o
objs-$(CONFIG_STM32F4XX_DRV_GPIO)     += vk_drv_gpio.o
objs-$(CONFIG_STM32F4XX_DRV_NVIC)     += vk_drv_nvic.o
objs-$(CONFIG_STM32F4XX_DRV_USART)    += vk_drv_usart.o
objs-$(CONFIG_STM32F4XX_DRV_SPI)      += vk_drv_spi.o
objs-$(CONFIG_STM32F4XX_DRV_I2C)      += vk_drv_i2c.o
objs-$(CONFIG_STM32F4XX_DRV_DMA)      += vk_drv_dma.o
objs-$(CONFIG_STM32F4XX_DRV_FSMC)     += vk_drv_fsmc.o
objs-$(CONFIG_STM32F4XX_DRV_EXTI)     += vk_drv_exti.o
objs-$(CONFIG_STM32F4XX_DRV_USB)      += vk_drv_usb.o

else ifeq ($(CONFIG_STM32H7xx), y)
inc-y                                 += village-kernel/drivers/platform/stm32h7xx/inc
src-y                                 += village-kernel/drivers/platform/stm32h7xx/src

objs-$(CONFIG_STM32H7XX_DRV_HAL)      += vk_drv_hal.o
objs-$(CONFIG_STM32H7XX_DRV_GPIO)     += vk_drv_gpio.o
objs-$(CONFIG_STM32H7XX_DRV_LTDC)     += vk_drv_ltdc.o
objs-$(CONFIG_STM32H7XX_DRV_NVIC)     += vk_drv_nvic.o
objs-$(CONFIG_STM32H7XX_DRV_USART)    += vk_drv_usart.o
objs-$(CONFIG_STM32H7XX_DRV_SDIO)     += vk_drv_sdio.o
objs-$(CONFIG_STM32H7XX_DRV_SPI)      += vk_drv_spi.o
objs-$(CONFIG_STM32H7XX_DRV_I2C)      += vk_drv_i2c.o
objs-$(CONFIG_STM32H7XX_DRV_DMA)      += vk_drv_dma.o
objs-$(CONFIG_STM32H7XX_DRV_FSMC)     += vk_drv_fsmc.o
endif


######################################
# block
######################################
inc-y                                 += village-kernel/drivers/peripheral/block/inc
src-y                                 += village-kernel/drivers/peripheral/block/src

objs-$(CONFIG_ATALBADISK)             += vk_ata_lba_disk.o
objs-$(CONFIG_SDIOSDCARD)             += vk_sdio_sdcard.o
objs-$(CONFIG_SPISDCARD)              += vk_spi_sdcard.o
objs-$(CONFIG_SPIW25QXX)              += vk_spi_w25qxx.o


######################################
# display
######################################
inc-y                                 += village-kernel/drivers/peripheral/display/inc
src-y                                 += village-kernel/drivers/peripheral/display/src

objs-$(CONFIG_BOCHS_VBE)              += vk_bochs_vbe.o
objs-$(CONFIG_LCD_ILI9488)            += vk_lcd_ili9488.o


######################################
# dma
######################################
inc-y                                 += village-kernel/drivers/peripheral/dma/inc
src-y                                 += village-kernel/drivers/peripheral/dma/src

objs-$(CONFIG_STM32DMA)               += vk_stm32_dma.o


######################################
# keyboard
######################################
inc-y                                 += village-kernel/drivers/peripheral/keyboard/inc
src-y                                 += village-kernel/drivers/peripheral/keyboard/src

objs-$(CONFIG_PS2KEYBOARD)            += vk_ps2_keyboard.o


######################################
# mouse
######################################
inc-y                                 += village-kernel/drivers/peripheral/mouse/inc
src-y                                 += village-kernel/drivers/peripheral/mouse/src

objs-$(CONFIG_PS2MOUSE)               += vk_ps2_mouse.o


######################################
# serial
######################################
inc-y                                 += village-kernel/drivers/peripheral/serial/inc
src-y                                 += village-kernel/drivers/peripheral/serial/src

objs-$(CONFIG_PIC32UART)              += vk_pic32_uart.o
objs-$(CONFIG_STM32UART)              += vk_stm32_uart.o


######################################
# timer
######################################
inc-y                                 += village-kernel/drivers/peripheral/timer/inc
src-y                                 += village-kernel/drivers/peripheral/timer/src

objs-$(CONFIG_PIT32TIMER)             += vk_pit32_timer.o


######################################
# usb
######################################
inc-y                                 += village-kernel/drivers/peripheral/usb/inc
src-y                                 += village-kernel/drivers/peripheral/usb/src

objs-$(CONFIG_STM32USB)               += vk_stm32_usb.o
