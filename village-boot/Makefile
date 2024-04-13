###########################################################################
# Makefile
# The Makefile of village-boot
#
# $Copyright: Copyright (C) village
############################################################################

ifeq ($(CONFIG_X86BIOS), y)
-include village-boot/x86bios/Makefile
endif

ifeq ($(CONFIG_X64UEFI), y)
-include village-boot/x64uefi/Makefile
endif
