###########################################################################
# Makefile
# The Makefile of village-kernel/drivers/arm/cortex-m
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-y                         += village-kernel/drivers/arm/cortex-m/config
inc-y                         += village-kernel/drivers/arm/cortex-m/inc
src-y                         += village-kernel/drivers/arm/cortex-m/src

######################################
# objects
######################################
objs-$(CONFIG_DMAFIFO)        += DmaFifo.o
objs-$(CONFIG_ILI9488)        += ILI9488.o
objs-$(CONFIG_SDMMC)          += SDMMC.o
objs-$(CONFIG_SPIFLASH)       += SpiFlash.o
objs-$(CONFIG_SPISDCARD)      += SpiSdCard.o
objs-$(CONFIG_UARTSERIAL)     += UartSerial.o
objs-$(CONFIG_USBSTORAGE)     += UsbStorage.o
