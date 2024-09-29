###########################################################################
# Makefile
# The Makefile of input service
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_INPUT_SERVICE), y)

######################################
# services
######################################
svcs-y                                += input


######################################
# paths
######################################
inc-input-y                           += village-os/services/input/inc
src-input-y                           += village-os/services/input/src


######################################
# objects
######################################
objs-input-y                          += InputService.o


######################################
# libraries
######################################
libs-input-y                          += utils c

endif
