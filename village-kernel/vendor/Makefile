###########################################################################
# Makefile
# The Makefile of village-kernel/vendor
#
# $Copyright: Copyright (C) village
############################################################################

## ARM
ifeq ($(CONFIG_ARM)_$(CONFIG_CORTEX_M), y_y)
-include village-kernel/vendor/arm/cortex-m/Makefile
endif

## X86
ifeq ($(CONFIG_X86)_$(CONFIG_BIOS), y_y)
-include village-kernel/vendor/x86/bios/Makefile
endif
