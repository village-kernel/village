###########################################################################
# Makefile
# The Makefile of vklibc
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-$(CONFIG_VKLIBC)                 += vk.kernel/libraries/vklibc/inc

src-$(CONFIG_VKLIBC)                 += vk.kernel/libraries/vklibc/src
src-$(CONFIG_VKLIBC)                 += vk.kernel/libraries/vklibc/stdio
src-$(CONFIG_VKLIBC)                 += vk.kernel/libraries/vklibc/string


######################################
# objects
######################################
objs-$(CONFIG_VKLIBC)                += init.o
objs-$(CONFIG_VKLIBC)                += stdlib.o
objs-$(CONFIG_VKLIBC)                += $(patsubst %.c, %.o, $(notdir $(wildcard vk.kernel/libraries/vklibc/stdio/*.c)))
objs-$(CONFIG_VKLIBC)                += $(patsubst %.c, %.o, $(notdir $(wildcard vk.kernel/libraries/vklibc/string/*.c)))
