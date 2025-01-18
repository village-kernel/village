###########################################################################
# Makefile
# The Makefile of demo
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_DEMO_APP), y)

######################################
# programs
######################################
apps-y                                += demo


######################################
# paths
######################################
inc-demo-y                            += village-demo/programs/demo/inc
src-demo-y                            += village-demo/programs/demo/src


######################################
# objects
######################################
objs-demo-y                           += demo_app.o


######################################
# libraries
######################################
libs-demo-y                           += vkc++ vkc

endif


######################################
# settings
######################################
ifeq ($(CONFIG_DEMO_POWER_UP), y)
settings-demo                         += power_up
endif
