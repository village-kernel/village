###########################################################################
# Makefile
# The Makefile of gui service
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_GUI_SERVICE), y)

######################################
# services
######################################
svcs-y                                += gui


######################################
# paths
######################################
inc-gui-y                             += village-os/services/gui/inc
src-gui-y                             += village-os/services/gui/src


######################################
# objects
######################################
objs-gui-y                            += GuiService.o


######################################
# libraries
######################################
libs-gui-y                            += vkgui utils stdc++ c

endif
