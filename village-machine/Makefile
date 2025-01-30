###########################################################################
# Makefile
# The Makefile of village-machine
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-y                                 += village-machine/machine/inc
src-y                                 += village-machine/machine/src

objs-$(CONFIG_IA32LEGACY)             += vk_ia32legacy_devices.o
objs-$(CONFIG_STM32F4xx)              += vk_stm32f407_devices.o
objs-$(CONFIG_STM32H7xx)              += vk_stm32h743_devices.o


######################################
# platform
######################################
## ia32legacy
ifeq ($(CONFIG_IA32LEGACY), y)
include village-machine/platform/ia32legacy/Makefile

## stm32f4xx
else ifeq ($(CONFIG_STM32F4xx), y)
include village-machine/platform/stm32f4xx/Makefile

## stm32h7xx
else ifeq ($(CONFIG_STM32H7xx), y)
include village-machine/platform/stm32h7xx/Makefile
endif


######################################
# block
######################################
inc-y                                 += village-machine/peripheral/block/inc
src-y                                 += village-machine/peripheral/block/src

objs-$(CONFIG_ATALBADISK)             += vk_ata_lba_disk.o
objs-$(CONFIG_SDIOSDCARD)             += vk_sdio_sdcard.o
objs-$(CONFIG_SPISDCARD)              += vk_spi_sdcard.o
objs-$(CONFIG_SPIW25QXX)              += vk_spi_w25qxx.o


######################################
# display
######################################
inc-y                                 += village-machine/peripheral/display/inc
src-y                                 += village-machine/peripheral/display/src

objs-$(CONFIG_BOCHS_VBE)              += vk_bochs_vbe.o
objs-$(CONFIG_LCD_ILI9488)            += vk_lcd_ili9488.o


######################################
# dma
######################################
inc-y                                 += village-machine/peripheral/dma/inc
src-y                                 += village-machine/peripheral/dma/src

objs-$(CONFIG_STM32DMA)               += vk_stm32_dma.o


######################################
# keyboard
######################################
inc-y                                 += village-machine/peripheral/keyboard/inc
src-y                                 += village-machine/peripheral/keyboard/src

objs-$(CONFIG_PS2KEYBOARD)            += vk_ps2_keyboard.o


######################################
# mouse
######################################
inc-y                                 += village-machine/peripheral/mouse/inc
src-y                                 += village-machine/peripheral/mouse/src

objs-$(CONFIG_PS2MOUSE)               += vk_ps2_mouse.o


######################################
# serial
######################################
inc-y                                 += village-machine/peripheral/serial/inc
src-y                                 += village-machine/peripheral/serial/src

objs-$(CONFIG_PIC32UART)              += vk_pic32_uart.o
objs-$(CONFIG_STM32UART)              += vk_stm32_uart.o


######################################
# timer
######################################
inc-y                                 += village-machine/peripheral/timer/inc
src-y                                 += village-machine/peripheral/timer/src

objs-$(CONFIG_PIT32TIMER)             += vk_pit32_timer.o


######################################
# usb
######################################
inc-y                                 += village-machine/peripheral/usb/inc
src-y                                 += village-machine/peripheral/usb/src

objs-$(CONFIG_STM32USB)               += vk_stm32_usb.o
