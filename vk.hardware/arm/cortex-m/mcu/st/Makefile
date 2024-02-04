###########################################################################
# Makefile
# The Makefile of vk.hardware/arm/cortex-m/mcu/st
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
libs-y                    += hw


######################################
# paths
######################################
inc-y += vk.hardware/arm/cortex-m/mcu/st/CMSIS/Include

inc-$(CONFIG_USBSTORAGE) +=	vk.hardware/arm/cortex-m/mcu/st/STM32_USB_Device_Library/Class/MSC/Inc
inc-$(CONFIG_USBSTORAGE) +=	vk.hardware/arm/cortex-m/mcu/st/STM32_USB_Device_Library/Core/Inc
inc-$(CONFIG_USBSTORAGE) +=	vk.hardware/arm/cortex-m/mcu/st/STM32_USB_Device_Library/Storage/Inc

src-y                    +=	vk.hardware/arm/cortex-m/mcu/st/GCC
src-$(CONFIG_USBSTORAGE) +=	vk.hardware/arm/cortex-m/mcu/st/STM32_USB_Device_Library/Class/MSC/Src
src-$(CONFIG_USBSTORAGE) +=	vk.hardware/arm/cortex-m/mcu/st/STM32_USB_Device_Library/Core/Src
src-$(CONFIG_USBSTORAGE) +=	vk.hardware/arm/cortex-m/mcu/st/STM32_USB_Device_Library/Storage/Src


######################################
# objects
######################################
objs-y                       += libcinit.o
objs-hw-y                    += syscalls.o
objs-hw-y                    += sysmem.o

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
-include vk.hardware/arm/cortex-m/mcu/st/MakefileF4
else ifeq ($(CONFIG_STM32H7xx), y)
-include vk.hardware/arm/cortex-m/mcu/st/MakefileH7
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
CXXFLAGS  += $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit -fno-threadsafe-statics

# bootloader ld flags
ifeq ($(CONFIG_VKLIBC), y)
BLDFLAGS  += $(MCU) $(LDSCRIPT-BOOT-y) -ffreestanding -nostdlib
else
BLDFLAGS  += $(MCU) $(LDSCRIPT-BOOT-y) -specs=nano.specs -lc -lm -lnosys
endif
BLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-boot.map,--cref
BLDFLAGS  += -Wl,--gc-sections
BLDFLAGS  += -Wl,--no-warn-rwx-segment
BLDFLAGS  += -Wl,-static 

# kernel ld flags
ifeq ($(CONFIG_VKLIBC), y)
KLDFLAGS  += $(MCU) $(LDSCRIPT-KERNEL-y) -ffreestanding -nostdlib
else
KLDFLAGS  += $(MCU) $(LDSCRIPT-KERNEL-y) -specs=nano.specs -lc -lm -lnosys
endif
KLDFLAGS  += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-kernel.map,--cref
KLDFLAGS  += -Wl,--gc-sections
KLDFLAGS  += -Wl,--no-warn-rwx-segment
KLDFLAGS  += -Wl,-static -pie

# application ld flags
ifeq ($(CONFIG_VKLIBC), y)
APPLDFLAGS  += $(MCU) -ffreestanding -nostdlib
else
APPLDFLAGS  += $(MCU) -specs=nano.specs -lc -lm -lnosys
endif
APPLDFLAGS  += -Wl,-Map=$(@:.exec=.map),--cref
APPLDFLAGS  += -Wl,--gc-sections
APPLDFLAGS  += -Wl,--no-warn-rwx-segment
APPLDFLAGS  += -Wl,--unresolved-symbols=ignore-all
#APPLDFLAGS  += -Wl,-static -pie -e main
APPLDFLAGS  += -pie -e main
