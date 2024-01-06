###########################################################################
# Makefile
# The Makefile of vklibc
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
libs-y                  += c


######################################
# paths
######################################
inc-y                   += vk.library/vklibc/inc

src-y                   += vk.library/vklibc/src
src-y                   += vk.library/vklibc/stdio
src-y                   += vk.library/vklibc/string


######################################
# objects
######################################
objs-c-y                += $(patsubst %.c, %.o, $(notdir $(wildcard vk.library/vklibc/src/*.c)))
objs-c-y                += $(patsubst %.c, %.o, $(notdir $(wildcard vk.library/vklibc/stdio/*.c)))
objs-c-y                += $(patsubst %.c, %.o, $(notdir $(wildcard vk.library/vklibc/string/*.c)))
