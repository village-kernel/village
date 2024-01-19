###########################################################################
# Makefile
# The Makefile of vk.hardware
#
# $Copyright: Copyright (C) village
############################################################################

## ARM
ifeq ($(CONFIG_ARM), y)

ifeq ($(CONFIG_CORTEX_M), y)
-include vk.hardware/arm/cortex-m/Makefile
endif

endif

## X86
ifeq ($(CONFIG_X86), y)

ifeq ($(CONFIG_BIOS), y)
-include vk.hardware/x86/bios/Makefile
endif

endif
