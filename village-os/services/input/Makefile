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
svcs-y                                += inputsvc


######################################
# paths
######################################
inc-inputsvc-y                        += village-os/services/input/inc
src-inputsvc-y                        += village-os/services/input/src


######################################
# objects
######################################
objs-inputsvc-y                       += input_service.o


######################################
# libraries
######################################
libs-inputsvc-y                       += utils vkc

endif


######################################
# settings
######################################
ifeq ($(CONFIG_INPUT_POWER_UP), y)
settings-inputsvc                     += power_up
endif
