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
objs-vkguisvc-y                       += VkGuiService.o


######################################
# libraries
######################################
libs-vkguisvc-y                       += vkgui utils vkc++ vkc

endif
