###########################################################################
# Makefile
# The Makefile of desktop
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_DESKTOP_APP), y)

######################################
# programs
######################################
apps-y                                += desktop


######################################
# paths
######################################
inc-desktop-y                         += village-os/programs/desktop/inc
src-desktop-y                         += village-os/programs/desktop/src


######################################
# objects
######################################
objs-desktop-y                        += app_desktop.o
objs-desktop-y                        += desk_view.o
objs-desktop-y                        += desk_model.o
objs-desktop-y                        += dock_view.o
objs-desktop-y                        += dock_model.o


######################################
# libraries
######################################
libs-desktop-y                        += vkgui utils vkc++ vkc

endif


######################################
# settings
######################################
ifeq ($(CONFIG_DESKTOP_POWER_UP), y)
settings-desktop                      += power_up
endif
