###########################################################################
# Makefile
# The Makefile of vk.hardware
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-y += ./vk.hardware/BSP/ST/CMSIS/Include

inc-$(CONFIG_USBSTORAGE) +=	./vk.hardware/BSP/ST/STM32_USB_Device_Library/Class/MSC/Inc
inc-$(CONFIG_USBSTORAGE) +=	./vk.hardware/BSP/ST/STM32_USB_Device_Library/Core/Inc
inc-$(CONFIG_USBSTORAGE) +=	./vk.hardware/BSP/ST/STM32_USB_Device_Library/Storage/Inc

src-$(CONFIG_USBSTORAGE) +=	./vk.hardware/BSP/ST/GCC
src-$(CONFIG_USBSTORAGE) +=	./vk.hardware/BSP/ST/STM32_USB_Device_Library/Class/MSC/Src
src-$(CONFIG_USBSTORAGE) +=	./vk.hardware/BSP/ST/STM32_USB_Device_Library/Core/Src
src-$(CONFIG_USBSTORAGE) +=	./vk.hardware/BSP/ST/STM32_USB_Device_Library/Storage/Src


######################################
# objects
######################################
objs-y                    += syscalls.o
objs-y                    += sysmem.o

objs-$(CONFIG_USBSTORAGE) += usbd_msc_bot.o
objs-$(CONFIG_USBSTORAGE) += usbd_msc_data.o
objs-$(CONFIG_USBSTORAGE) += usbd_msc_scsi.o
objs-$(CONFIG_USBSTORAGE) += usbd_msc.o
objs-$(CONFIG_USBSTORAGE) += usbd_core.o
objs-$(CONFIG_USBSTORAGE) += usbd_ctlreq.o
objs-$(CONFIG_USBSTORAGE) += usbd_ioreq.o
objs-$(CONFIG_USBSTORAGE) += usbd_conf.o
objs-$(CONFIG_USBSTORAGE) += usbd_desc.o


######################################
# dependencies
######################################
ifeq ($(CONFIG_STM32F4xx), y)
-include vk.hardware/BSP/ST/MakefileF4
else ifeq ($(CONFIG_STM32H7xx), y)
-include vk.hardware/BSP/ST/MakefileH7
endif
