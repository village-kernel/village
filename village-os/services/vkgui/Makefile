###########################################################################
# Makefile
# The Makefile of vkgui service
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_VKGUI_SERVICE), y)

######################################
# services
######################################
svcs-y                                += vkguisvc


######################################
# paths
######################################
inc-vkguisvc-y                        += village-os/services/vkgui/inc
src-vkguisvc-y                        += village-os/services/vkgui/src


######################################
# objects
######################################
objs-vkguisvc-y                       += vk_gui_service.o


######################################
# libraries
######################################
libs-vkguisvc-y                       += vkgui utils vkc++ vkc

endif


######################################
# settings
######################################
ifeq ($(CONFIG_VKGUI_POWER_UP), y)
settings-vkguisvc                     += power_up
endif
