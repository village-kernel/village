###########################################################################
# Makefile
# The Makefile of settings
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_SETTINGS_APP), y)

######################################
# applications
######################################
apps-y                                += settings


######################################
# paths
######################################
inc-settings-y                        += village-os/applications/settings/inc
src-settings-y                        += village-os/applications/settings/src


######################################
# objects
######################################
objs-settings-y                       += SettingsUI.o
objs-settings-y                       += SettingsApp.o


######################################
# libraries
######################################
libs-settings-y                       += vkc

endif


######################################
# settings
######################################
ifeq ($(CONFIG_SETTINGS_POWER_UP), y)
settings-settings                     += 
endif
