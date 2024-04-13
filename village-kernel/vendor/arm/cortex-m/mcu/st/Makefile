###########################################################################
# Makefile
# The Makefile of village-kernel/vendor/arm/cortex-m/mcu/st
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
libs-y                       += hw


######################################
# paths
######################################
inc-y                        += village-kernel/vendor/arm/cortex-m/mcu/st/CMSIS/Include

inc-$(CONFIG_USBSTORAGE)     +=	village-kernel/vendor/arm/cortex-m/mcu/st/STM32_USB_Device_Library/Class/MSC/Inc
inc-$(CONFIG_USBSTORAGE)     +=	village-kernel/vendor/arm/cortex-m/mcu/st/STM32_USB_Device_Library/Core/Inc
inc-$(CONFIG_USBSTORAGE)     +=	village-kernel/vendor/arm/cortex-m/mcu/st/STM32_USB_Device_Library/Storage/Inc

src-y                        +=	village-kernel/vendor/arm/cortex-m/mcu/st/CMSIS/Source
src-$(CONFIG_USBSTORAGE)     +=	village-kernel/vendor/arm/cortex-m/mcu/st/STM32_USB_Device_Library/Class/MSC/Src
src-$(CONFIG_USBSTORAGE)     +=	village-kernel/vendor/arm/cortex-m/mcu/st/STM32_USB_Device_Library/Core/Src
src-$(CONFIG_USBSTORAGE)     +=	village-kernel/vendor/arm/cortex-m/mcu/st/STM32_USB_Device_Library/Storage/Src


######################################
# objects
######################################
objs-y                       += libcinit.o

objs-hw-$(CONFIG_USBSTORAGE) += usbd_msc_bot.o
objs-hw-$(CONFIG_USBSTORAGE) += usbd_msc_data.o
objs-hw-$(CONFIG_USBSTORAGE) += usbd_msc_scsi.o
objs-hw-$(CONFIG_USBSTORAGE) += usbd_msc.o
objs-hw-$(CONFIG_USBSTORAGE) += usbd_core.o
objs-hw-$(CONFIG_USBSTORAGE) += usbd_ctlreq.o
objs-hw-$(CONFIG_USBSTORAGE) += usbd_ioreq.o
objs-hw-$(CONFIG_USBSTORAGE) += usbd_conf.o
objs-hw-$(CONFIG_USBSTORAGE) += usbd_desc.o


######################################
# dependencies
######################################
ifeq ($(CONFIG_STM32F4xx), y)
-include village-kernel/vendor/arm/cortex-m/mcu/st/stm32f4xx.mk
else ifeq ($(CONFIG_STM32H7xx), y)
-include village-kernel/vendor/arm/cortex-m/mcu/st/stm32h7xx.mk
endif
