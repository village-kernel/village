###########################################################################
# Makefile
# The Makefile of vk.hardware
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# includes
######################################
INCLUDES-y += -I./vk.hardware/BSP/ST/CMSIS/Include

INCLUDES-$(CONFIG_USBSTORAGE) += \
	-I./vk.hardware/BSP/ST/STM32_USB_Device_Library/Class/MSC/Inc \
	-I./vk.hardware/BSP/ST/STM32_USB_Device_Library/Core/Inc \
	-I./vk.hardware/BSP/ST/STM32_USB_Device_Library/Storage/Inc


######################################
# sources
######################################
# ASM sources
ASM_SOURCES-y += 


# C sources
C_SOURCES-y += \
	$(wildcard ./vk.hardware/BSP/ST/CMSIS/Source/*.c) \
	$(wildcard ./vk.hardware/BSP/ST/GCC/*.c) \

C_SOURCES-$(CONFIG_USBSTORAGE) += \
	$(wildcard ./vk.hardware/BSP/ST/STM32_USB_Device_Library/Class/MSC/Src/*.c) \
	$(wildcard ./vk.hardware/BSP/ST/STM32_USB_Device_Library/Core/Src/*.c) \
	$(wildcard ./vk.hardware/BSP/ST/STM32_USB_Device_Library/Storage/Src/*.c) \


# Cpp sources
CPP_SOURCES-y += 


######################################
# dependencies
######################################
ifeq ($(CONFIG_STM32F4xx), y)
-include vk.hardware/BSP/ST/MakefileF4
else ifeq ($(CONFIG_STM32H7xx), y)
-include vk.hardware/BSP/ST/MakefileH7
endif
