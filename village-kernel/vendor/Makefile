###########################################################################
# Makefile
# The Makefile of village-kernel/vendor
#
# $Copyright: Copyright (C) village
############################################################################

## ARM
ifeq ($(CONFIG_ARM), y)

ifeq ($(CONFIG_CORTEX_M), y)
-include village-kernel/vendor/arm/cortex-m/Makefile
endif

endif

## X86
ifeq ($(CONFIG_X86), y)

ifeq ($(CONFIG_BIOS), y)
-include village-kernel/vendor/x86/bios/Makefile
endif

endif
