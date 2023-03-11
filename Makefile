###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# includes
######################################
INCLUDES-$(CONFIG_GUI) += -I./vk.gui/config \
	-I./vk.gui/core/inc \
	-I./vk.gui/font/inc


######################################
# sources
######################################
# ASM sources
ASM_SOURCES-y +=

# C sources
C_SOURCES-y += 

# Cpp sources
CPP_SOURCES-$(CONFIG_GUI) += vk.gui/core/src/GUI.cpp
CPP_SOURCES-$(CONFIG_GUI) += vk.gui/core/src/Display.cpp
