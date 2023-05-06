###########################################################################
# Makefile
# The Makefile of vk.hardware
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-y += vk.hardware/BSP/ST/CMSIS/Include

inc-$(CONFIG_USBSTORAGE) +=	vk.hardware/BSP/ST/STM32_USB_Device_Library/Class/MSC/Inc
inc-$(CONFIG_USBSTORAGE) +=	vk.hardware/BSP/ST/STM32_USB_Device_Library/Core/Inc
inc-$(CONFIG_USBSTORAGE) +=	vk.hardware/BSP/ST/STM32_USB_Device_Library/Storage/Inc

src-y                    +=	vk.hardware/BSP/ST/GCC
src-$(CONFIG_USBSTORAGE) +=	vk.hardware/BSP/ST/STM32_USB_Device_Library/Class/MSC/Src
src-$(CONFIG_USBSTORAGE) +=	vk.hardware/BSP/ST/STM32_USB_Device_Library/Core/Src
src-$(CONFIG_USBSTORAGE) +=	vk.hardware/BSP/ST/STM32_USB_Device_Library/Storage/Src


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


#######################################
# compiler flags
#######################################
# gcc flags
CFLAGS    += $(MCU) $(DEFS) $(OPT) $(INCLUDES)
CFLAGS    += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(dir $<)/$(@:.o=.list)
CFLAGS    += -MMD -MP -MF"$(BUILD_DIR)/$(dir $<)/$(@:%.o=%.d)"
CFLAGS    += -Wall -fdata-sections -ffunction-sections -fno-common
CFLAGS    += -mword-relocations -mlong-calls
CXXFLAGS  += $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit

# bootloader ld flags
BLDFLAGS  += $(MCU) $(LDSCRIPTB-BOOT-y) -specs=nano.specs -lc -lm -lnosys
BLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-boot.map,--cref
BLDFLAGS  += -Wl,--gc-sections
BLDFLAGS  += -Wl,--no-warn-rwx-segment

# kernel ld flags
KLDFLAGS  += $(MCU) $(LDSCRIPT-KERNEL-y) -specs=nano.specs -lc -lm -lnosys
KLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-kernel.map,--cref
KLDFLAGS  += -Wl,--gc-sections
KLDFLAGS  += -Wl,--no-warn-rwx-segment

# mod ld flags
MLDFLAGS   = $(MCU) -T vk.scripts/ldscript/module.ld
MLDFLAGS  += -Wl,-Map=$(@:.mo=.map),--cref
MLDFLAGS  += -r -Bsymbolic -nostartfiles
