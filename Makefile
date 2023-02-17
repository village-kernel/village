###########################################################################
# Makefile
# The Makefile of VK.Kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# includes
######################################
INCLUDES += -I./VK.Kernel/kernel/inc \
	-I./VK.Kernel/libary/fatfs/inc \
	-I./VK.Kernel/utilities/inc


######################################
# sources
######################################
# ASM sources
ASM_SOURCES +=

# C sources
C_SOURCES += 

# Cpp sources
CPP_SOURCES += VK.Kernel/kernel/src/Console.cpp \
	VK.Kernel/kernel/src/Device.cpp \
	VK.Kernel/kernel/src/Kernel.cpp \
	VK.Kernel/kernel/src/Thread.cpp \
	VK.Kernel/libary/fatfs/src/diskio.cpp \
	VK.Kernel/libary/fatfs/src/ff.cpp \
	VK.Kernel/libary/fatfs/src/ffsystem.cpp \
	VK.Kernel/libary/fatfs/src/ffunicode.cpp \
	# VK.Kernel/utilities/src/FileStream.cpp \
	# VK.kernel/utilities/src/iniParser.cpp \
	# VK.kernel/utilities/src/pinParser.cpp
