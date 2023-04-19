###########################################################################
# Makefile
# The Makefile of vk.aplication
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-$(CONFIG_BOOTLOADER) += vk.bootloader/arm/inc
src-$(CONFIG_BOOTLOADER) += vk.bootloader/arm/src

######################################
# objects
######################################
objs-$(CONFIG_BOOTLOADER) += Bootloader.o
