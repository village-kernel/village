###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# includes
######################################
INCLUDES += -I./vk.gui/config \
	-I./vk.gui/core/inc \
	-I./vk.gui/font/inc


######################################
# sources
######################################
# ASM sources
ASM_SOURCES +=

# C sources
C_SOURCES += 

# Cpp sources
CPP_SOURCES += vk.gui/core/src/GUI.cpp \
	vk.gui/core/src/Display.cpp
