###########################################################################
# Makefile
# The Makefile of manager
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_MONITOR_APP), y)

######################################
# programs
######################################
apps-y                                += manager


######################################
# paths
######################################
inc-manager-y                         += village-os/programs/manager/inc
src-manager-y                         += village-os/programs/manager/src


######################################
# objects
######################################
objs-manager-y                        += manager_app.o
objs-manager-y                        += manager_model.o
objs-manager-y                        += manager_view.o


######################################
# libraries
######################################
libs-manager-y                        += vkgui utils vkc++ vkc

endif


######################################
# settings
######################################
ifeq ($(CONFIG_MONITOR_POWER_UP), y)
manager-settings                      += power_up
endif
