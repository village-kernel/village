###########################################################################
# Makefile
# The Makefile of vk.hardware/DEV
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# includes
######################################
INCLUDES-y += -I./vk.hardware/DEV/config -I./vk.hardware/DEV/inc
	

######################################
# sources
######################################
# ASM sources
ASM_SOURCES-y += 

# C sources
C_SOURCES-y +=

# Cpp sources
CPP_SOURCES-$(CONFIG_DMAFIFO) += vk.hardware/Dev/src/DmaFifo.cpp
CPP_SOURCES-$(CONFIG_ILI9488) += vk.hardware/Dev/src/ILI9488.cpp
CPP_SOURCES-$(CONFIG_SDCARD) += vk.hardware/Dev/src/SdCard.cpp
CPP_SOURCES-$(CONFIG_SPIFLASH) += vk.hardware/Dev/src/SpiFlash.cpp
CPP_SOURCES-$(CONFIG_UARTSERIAL) += vk.hardware/Dev/src/UartSerial.cpp
CPP_SOURCES-$(CONFIG_USBSTORAGE) += vk.hardware/Dev/src/UsbStorage.cpp
