###########################################################################
# Makefile
# The Makefile of vk.aplication
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-$(CONFIG_BOOTLOADER) += vk.bootloader/bootloader/inc
src-$(CONFIG_BOOTLOADER) += vk.bootloader/bootloader/src

######################################
# objects
######################################
objs-bl-$(CONFIG_BOOTLOADER) += Bootloader.o
