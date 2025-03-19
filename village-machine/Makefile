###########################################################################
# Makefile
# The Makefile of village-machine
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# board
######################################
inc-y                                 += village-machine/board
src-y                                 += village-machine/board

objs-$(CONFIG_IA32LEGACY_BOARD)       += vk_ia32legacy_board.o
objs-$(CONFIG_STM32F407_BOARD)        += vk_stm32f407_board.o
objs-$(CONFIG_STM32H743_BOARD)        += vk_stm32h743_board.o


######################################
# chipdrv
######################################
ifeq ($(CONFIG_IA32LEGACY), y)
inc-y                                 += village-machine/chipdrv/ia32legacy/inc
src-y                                 += village-machine/chipdrv/ia32legacy/src

objs-$(CONFIG_IA32LEGACY_DRV_PCI)     += vk_pci_controller.o
objs-$(CONFIG_IA32LEGACY_DRV_PS2)     += vk_ps2_controller.o

else ifeq ($(CONFIG_STM32F4xx), y)
inc-y                                 += village-machine/chipdrv/stm32f4xx/inc
src-y                                 += village-machine/chipdrv/stm32f4xx/src

objs-$(CONFIG_STM32F4XX_DRV_HAL)      += vk_drv_hal.o
objs-$(CONFIG_STM32F4XX_DRV_GPIO)     += vk_drv_gpio.o
objs-$(CONFIG_STM32F4XX_DRV_NVIC)     += vk_drv_nvic.o
objs-$(CONFIG_STM32F4XX_DRV_USART)    += vk_drv_usart.o
objs-$(CONFIG_STM32F4XX_DRV_SPI)      += vk_drv_spi.o
objs-$(CONFIG_STM32F4XX_DRV_I2C)      += vk_drv_i2c.o
objs-$(CONFIG_STM32F4XX_DRV_DMA)      += vk_drv_dma.o
objs-$(CONFIG_STM32F4XX_DRV_LCD_8080) += vk_drv_lcd_8080.o
objs-$(CONFIG_STM32F4XX_DRV_EXTI)     += vk_drv_exti.o
objs-$(CONFIG_STM32F4XX_DRV_USB)      += vk_drv_usb.o

else ifeq ($(CONFIG_STM32H7xx), y)
inc-y                                 += village-machine/chipdrv/stm32h7xx/inc
src-y                                 += village-machine/chipdrv/stm32h7xx/src

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
# platdrv
######################################

######################################
# block
######################################
inc-y                                 += village-machine/platdrv/block/inc
src-y                                 += village-machine/platdrv/block/src

objs-$(CONFIG_ATALBADISK)             += vk_ata_lba_disk.o
objs-$(CONFIG_SDIOSDCARD)             += vk_sdio_sdcard.o
objs-$(CONFIG_SPISDCARD)              += vk_spi_sdcard.o
objs-$(CONFIG_SPIW25QXX)              += vk_spi_w25qxx.o


######################################
# display
######################################
inc-y                                 += village-machine/platdrv/display/inc
src-y                                 += village-machine/platdrv/display/src

objs-$(CONFIG_BOCHS_VBE)              += vk_bochs_vbe.o
objs-$(CONFIG_LCD_ILI9488)            += vk_lcd_ili9488.o


######################################
# dma
######################################
inc-y                                 += village-machine/platdrv/dma/inc
src-y                                 += village-machine/platdrv/dma/src

objs-$(CONFIG_STM32DMA)               += vk_stm32_dma.o


######################################
# keyboard
######################################
inc-y                                 += village-machine/platdrv/keyboard/inc
src-y                                 += village-machine/platdrv/keyboard/src

objs-$(CONFIG_PS2KEYBOARD)            += vk_ps2_keyboard.o


######################################
# mouse
######################################
inc-y                                 += village-machine/platdrv/mouse/inc
src-y                                 += village-machine/platdrv/mouse/src

objs-$(CONFIG_PS2MOUSE)               += vk_ps2_mouse.o


######################################
# serial
######################################
inc-y                                 += village-machine/platdrv/serial/inc
src-y                                 += village-machine/platdrv/serial/src

objs-$(CONFIG_PIC32UART)              += vk_pic32_uart.o
objs-$(CONFIG_STM32UART)              += vk_stm32_uart.o


######################################
# timer
######################################
inc-y                                 += village-machine/platdrv/timer/inc
src-y                                 += village-machine/platdrv/timer/src

objs-$(CONFIG_PIT32TIMER)             += vk_pit32_timer.o


######################################
# usb
######################################
inc-y                                 += village-machine/platdrv/usb/inc
src-y                                 += village-machine/platdrv/usb/src

objs-$(CONFIG_STM32USB)               += vk_stm32_usb.o


######################################
# vendor
######################################
## ia32legacy
ifeq ($(CONFIG_IA32LEGACY), y)
include village-machine/vendor/ia32legacy/Makefile

## stm32f4xx
else ifeq ($(CONFIG_STM32F4xx), y)
include village-machine/vendor/stm32f4xx/Makefile

## stm32h7xx
else ifeq ($(CONFIG_STM32H7xx), y)
include village-machine/vendor/stm32h7xx/Makefile
endif
