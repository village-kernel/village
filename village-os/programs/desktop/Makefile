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
objs-desktop-y                        += desktop_app.o
objs-desktop-y                        += desktop_view.o
objs-desktop-y                        += desktop_model.o


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
