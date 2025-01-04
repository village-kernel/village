###########################################################################
# Makefile
# The Makefile of monitor
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_MONITOR_APP), y)

######################################
# programs
######################################
apps-y                                += monitor


######################################
# paths
######################################
inc-monitor-y                         += village-os/programs/monitor/inc
src-monitor-y                         += village-os/programs/monitor/src


######################################
# objects
######################################
objs-monitor-y                        += monitor_app.o
objs-monitor-y                        += monitor_model.o
objs-monitor-y                        += monitor_view.o


######################################
# libraries
######################################
libs-monitor-y                        += vkgui utils vkc++ vkc

endif


######################################
# settings
######################################
ifeq ($(CONFIG_MONITOR_POWER_UP), y)
monitor-settings                      += power_up
endif
