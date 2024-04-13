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
inc-y                   += village-kernel/stdlib/libc/inc

src-y                   += village-kernel/stdlib/libc/src
src-y                   += village-kernel/stdlib/libc/stdio
src-y                   += village-kernel/stdlib/libc/string


######################################
# objects
######################################
objs-c-y                += $(patsubst %.c, %.o, $(notdir $(wildcard village-kernel/stdlib/libc/src/*.c)))
objs-c-y                += $(patsubst %.c, %.o, $(notdir $(wildcard village-kernel/stdlib/libc/stdio/*.c)))
objs-c-y                += $(patsubst %.c, %.o, $(notdir $(wildcard village-kernel/stdlib/libc/string/*.c)))
