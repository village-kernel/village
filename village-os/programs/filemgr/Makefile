###########################################################################
# Makefile
# The Makefile of filemgr
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_MONITOR_APP), y)

######################################
# programs
######################################
apps-y                                += filemgr


######################################
# paths
######################################
inc-filemgr-y                         += village-os/programs/filemgr/inc
src-filemgr-y                         += village-os/programs/filemgr/src


######################################
# objects
######################################
objs-filemgr-y                        += filemgr_app.o
objs-filemgr-y                        += filemgr_model.o
objs-filemgr-y                        += filemgr_view.o


######################################
# libraries
######################################
libs-filemgr-y                        += vkgui utils vkc++ vkc

endif


######################################
# settings
######################################
ifeq ($(CONFIG_FILEMGR_POWER_UP), y)
filemgr-settings                      += power_up
endif
