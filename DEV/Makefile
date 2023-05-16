###########################################################################
# Makefile
# The Makefile of vk.hardware/HAL
#
# $Copyright: Copyright (C) village
############################################################################

ifeq ($(CONFIG_CORTEX_M), y)
-include vk.hardware/DEV/arm/cortex-m/Makefile
else ifeq ($(CONFIG_X86), y)
-include vk.hardware/DEV/x86/Makefile
endif
