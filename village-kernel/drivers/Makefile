###########################################################################
# Makefile
# The Makefile of village-kernel/drivers
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-y                                 += village-kernel/drivers/include


######################################
# block
######################################
inc-y                                 += village-kernel/drivers/block
src-y                                 += village-kernel/drivers/block

objs-$(CONFIG_ATALBADISK)             += AtaLbaDisk.o
objs-$(CONFIG_SDIOSDCARD)             += SdioSdCard.o
objs-$(CONFIG_SPISDCARD)              += SpiSdCard.o
objs-$(CONFIG_SPIW25QXX)              += SpiW25qxx.o


######################################
# display
######################################
inc-y                                 += village-kernel/drivers/display
src-y                                 += village-kernel/drivers/display

objs-$(CONFIG_BOCHSVBE)               += BochsVBE.o
objs-$(CONFIG_ILI9488)                += ILI9488.o


######################################
# dma
######################################
inc-y                                 += village-kernel/drivers/dma
src-y                                 += village-kernel/drivers/dma

objs-$(CONFIG_DMAFIFO)                += DmaFifo.o


######################################
# keyboard
######################################
inc-y                                 += village-kernel/drivers/keyboard
src-y                                 += village-kernel/drivers/keyboard

objs-$(CONFIG_PS2KEYBOARD)            += PS2KeyBoard.o


######################################
# mouse
######################################
inc-y                                 += village-kernel/drivers/mouse
src-y                                 += village-kernel/drivers/mouse

objs-$(CONFIG_PS2MOUSE)               += PS2Mouse.o


######################################
# serial
######################################
inc-y                                 += village-kernel/drivers/serial
src-y                                 += village-kernel/drivers/serial

objs-$(CONFIG_SERIALPORT)             += SerialPort.o
objs-$(CONFIG_SERIALUART)             += SerialUart.o


######################################
# timer
######################################
inc-y                                 += village-kernel/drivers/timer
src-y                                 += village-kernel/drivers/timer

objs-$(CONFIG_GENERALTIMER)           += GeneralTimer.o


######################################
# usb
######################################
inc-y                                 += village-kernel/drivers/usb
src-y                                 += village-kernel/drivers/usb

objs-$(CONFIG_USBSTORAGE)             += UsbStorage.o
