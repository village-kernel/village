###########################################################################
# Makefile
# The Makefile of desktop
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_DESKTOP_APP), y)

######################################
# applications
######################################
apps-y                                += desktop


######################################
# paths
######################################
inc-desktop-y                         += village-os/applications/desktop/inc
src-desktop-y                         += village-os/applications/desktop/src


######################################
# objects
######################################
objs-desktop-y                        += DesktopUI.o
objs-desktop-y                        += DesktopApp.o


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
