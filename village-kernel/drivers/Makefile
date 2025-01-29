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
## ia32legacy
ifeq ($(CONFIG_IA32LEGACY), y)
include village-kernel/drivers/platform/ia32legacy/Makefile

## stm32f4xx
else ifeq ($(CONFIG_STM32F4xx), y)
include village-kernel/drivers/platform/stm32f4xx/Makefile

## stm32h7xx
else ifeq ($(CONFIG_STM32H7xx), y)
include village-kernel/drivers/platform/stm32h7xx/Makefile
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
