###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-$(CONFIG_GUI) += vk.gui/config
inc-$(CONFIG_GUI) += vk.gui/core/inc
inc-$(CONFIG_GUI) += vk.gui/font/inc
src-$(CONFIG_GUI) += vk.gui/core/src


######################################
# objects
######################################
objs-$(CONFIG_GUI) += GUI.o
objs-$(CONFIG_GUI) += Display.o
