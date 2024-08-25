###########################################################################
# Makefile
# The Makefile of village-kernel/drivers
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-y                                 += village-kernel/drivers/platform/inc
src-y                                 += village-kernel/drivers/platform/src

objs-$(CONFIG_IA32LEGACY)             += IA32legacyDevices.o
objs-$(CONFIG_STM32F4xx)              += Stm32f407Devices.o
objs-$(CONFIG_STM32H7xx)              += Stm32h743Devices.o


######################################
# block
######################################
inc-y                                 += village-kernel/drivers/block/inc
src-y                                 += village-kernel/drivers/block/src

objs-$(CONFIG_ATALBADISK)             += AtaLbaDisk.o
objs-$(CONFIG_SDIOSDCARD)             += SdioSdCard.o
objs-$(CONFIG_SPISDCARD)              += SpiSdCard.o
objs-$(CONFIG_SPIW25QXX)              += SpiW25qxx.o


######################################
# display
######################################
inc-y                                 += village-kernel/drivers/display/inc
src-y                                 += village-kernel/drivers/display/src

objs-$(CONFIG_BOCHSVBE)               += BochsVBE.o
objs-$(CONFIG_ILI9488)                += ILI9488.o


######################################
# dma
######################################
inc-y                                 += village-kernel/drivers/dma/inc
src-y                                 += village-kernel/drivers/dma/src

objs-$(CONFIG_STM32DMA)               += Stm32Dma.o


######################################
# keyboard
######################################
inc-y                                 += village-kernel/drivers/keyboard/inc
src-y                                 += village-kernel/drivers/keyboard/src

objs-$(CONFIG_PS2KEYBOARD)            += PS2KeyBoard.o


######################################
# mouse
######################################
inc-y                                 += village-kernel/drivers/mouse/inc
src-y                                 += village-kernel/drivers/mouse/src

objs-$(CONFIG_PS2MOUSE)               += PS2Mouse.o


######################################
# serial
######################################
inc-y                                 += village-kernel/drivers/serial/inc
src-y                                 += village-kernel/drivers/serial/src

objs-$(CONFIG_PIC32UART)              += Pic32Uart.o
objs-$(CONFIG_STM32UART)              += Stm32Uart.o


######################################
# timer
######################################
inc-y                                 += village-kernel/drivers/timer/inc
src-y                                 += village-kernel/drivers/timer/src

objs-$(CONFIG_PIT32TIMER)             += Pit32Timer.o
