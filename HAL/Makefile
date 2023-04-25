###########################################################################
# Makefile
# The Makefile of vk.hardware/HAL
#
# $Copyright: Copyright (C) village
############################################################################

ifeq ($(CONFIG_STM32F4xx), y)
-include vk.hardware/HAL/ST/STM32F4xx/Makefile
else ifeq ($(CONFIG_STM32H7xx), y)
-include vk.hardware/HAL/ST/STM32H7xx/Makefile
else ifeq ($(CONFIG_X86), y)
-include vk.hardware/HAL/x86/Makefile
endif
