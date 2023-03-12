###########################################################################
# Makefile
# The Makefile of vk.aplication
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# includes
######################################
INCLUDES-$(CONFIG_BOOTLOADER) += -I./vk.bootloader/bootloader/inc


######################################
# sources
######################################
# ASM sources
ASM_SOURCES-y +=

# C sources
C_SOURCES-y += 

# Cpp sources
CPP_SOURCES-$(CONFIG_APPLICATION1) += vk.bootloader/bootloader/src/Bootloader.cpp
