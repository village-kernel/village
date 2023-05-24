###########################################################################
# Makefile
# The Makefile of vklibc
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-y                 += vk.library/vklibc/inc

src-y                 += vk.library/vklibc/src
src-y                 += vk.library/vklibc/stdio
src-y                 += vk.library/vklibc/string


######################################
# objects
######################################
objs-y                += init.o
objs-y                += stdlib.o
objs-y                += $(patsubst %.c, %.o, $(notdir $(wildcard vk.library/vklibc/stdio/*.c)))
objs-y                += $(patsubst %.c, %.o, $(notdir $(wildcard vk.library/vklibc/string/*.c)))
