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
	-I./vk.kernel/libraries/fatfs/inc \
	-I./vk.kernel/utilities/inc


######################################
# sources
######################################
# ASM sources
ASM_SOURCES +=

# C sources
C_SOURCES += 

# Cpp sources
CPP_SOURCES += $(wildcard vk.kernel/kernel/src/*.cpp) \
	$(wildcard vk.kernel/libraries/fatfs/src/*.cpp) \
	$(wildcard vk.kernel/utilities/src/*.cpp) \
	$(wildcard vk.kernel/console/src/*.cpp)
	