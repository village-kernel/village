###########################################################################
# Makefile
# The Makefile of settings
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_SETTINGS_APP), y)

######################################
# programs
######################################
apps-y                                += settings


######################################
# paths
######################################
inc-settings-y                        += village-os/programs/settings/inc
src-settings-y                        += village-os/programs/settings/src


######################################
# objects
######################################
objs-settings-y                       += settings_app.o
objs-settings-y                       += settings_model.o
objs-settings-y                       += settings_view.o


######################################
# libraries
######################################
libs-settings-y                       += vkgui utils vkc++ vkc

endif


######################################
# settings
######################################
ifeq ($(CONFIG_SETTINGS_POWER_UP), y)
settings-settings                     += power_up
endif
