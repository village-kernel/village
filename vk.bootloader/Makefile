###########################################################################
# Makefile
# The Makefile of vk.aplication
#
# $Copyright: Copyright (C) village
############################################################################

ifeq ($(CONFIG_X86BIOS), y)
-include vk.bootloader/x86bios/Makefile
endif

ifeq ($(CONFIG_X64UEFI), y)
-include vk.bootloader/x64uefi/Makefile
endif
