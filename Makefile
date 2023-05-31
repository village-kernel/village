###########################################################################
# Makefile
# The Makefile of vk.aplication
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# applications
######################################
apps-$(CONFIG_TAICHI)                += taichi
apps-$(CONFIG_LAUNCH)                += launch
apps-$(CONFIG_TERMINAL)              += terminal
apps-$(CONFIG_SETTINGS)              += settings


######################################
# paths
######################################
inc-y                                += vk.application/demo/inc
inc-$(CONFIG_TAICHI)                 += vk.application/taichi/inc
inc-$(CONFIG_LAUNCH)                 += vk.application/launch/inc
inc-$(CONFIG_TERMINAL)               += vk.application/terminal/inc
inc-$(CONFIG_SETTINGS)               += vk.application/settings/inc

src-y                                += vk.application/demo/src
src-$(CONFIG_TAICHI)                 += vk.application/taichi/src
src-$(CONFIG_LAUNCH)                 += vk.application/launch/src
src-$(CONFIG_TERMINAL)               += vk.application/terminal/src
src-$(CONFIG_SETTINGS)               += vk.application/settings/src


######################################
# objects
######################################
objs-$(CONFIG_APPLICATION1)          += Application1.o
objs-$(CONFIG_APPLICATION2)          += Application2.o
objs-$(CONFIG_APPLICATION3)          += Application3.o
objs-$(CONFIG_APPLICATION4)          += Application4.o
objs-$(CONFIG_APPLICATION5)          += Application5.o
objs-$(CONFIG_APPLICATION6)          += Application6.o


objs-taichi-$(CONFIG_TAICHI)         += Taichi.o
objs-launch-$(CONFIG_LAUNCH)         += Launch.o
objs-terinal-$(CONFIG_TERMINAL)      += Terminal.o
objs-settings-$(CONFIG_SETTINGS)     += Settings.o
