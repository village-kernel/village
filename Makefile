###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# includes
######################################
INCLUDES += -I./vk.kernel/console/inc \
	-I./vk.kernel/kernel/if \
	-I./vk.kernel/kernel/inc \
	-I./vk.kernel/libary/fatfs/inc \
	-I./vk.kernel/utilities/inc


######################################
# sources
######################################
# ASM sources
ASM_SOURCES +=

# C sources
C_SOURCES += 

# Cpp sources
CPP_SOURCES += vk.kernel/kernel/src/Device.cpp \
	vk.kernel/kernel/src/Kernel.cpp \
	vk.kernel/kernel/src/Thread.cpp \
	vk.kernel/kernel/src/Scheduler.cpp \
	vk.kernel/kernel/src/Modular.cpp \
	vk.kernel/libary/fatfs/src/diskio.cpp \
	vk.kernel/libary/fatfs/src/ff.cpp \
	vk.kernel/libary/fatfs/src/ffsystem.cpp \
	vk.kernel/libary/fatfs/src/ffunicode.cpp \
	vk.kernel/utilities/src/FileStream.cpp \
	vk.kernel/utilities/src/iniParser.cpp \
	vk.kernel/utilities/src/pinParser.cpp \
	vk.kernel/console/src/Console.cpp \
	vk.kernel/console/src/CmdMsgMgr.cpp
