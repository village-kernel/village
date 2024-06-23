###########################################################################
# Makefile
# The Makefile of village-boot
#
# $Copyright: Copyright (C) village
############################################################################

ifeq ($(CONFIG_LEGACY), y)
include $(WORKSPACE)/village-boot/legacy/Makefile
endif

ifeq ($(CONFIG_UEFI), y)
include $(WORKSPACE)/village-boot/uefi/Makefile
endif
