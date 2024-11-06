###########################################################################
# Makefile
# The Makefile of taichi service
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_TAICHI_SERVICE), y)

######################################
# services
######################################
svcs-y                                += taichi


######################################
# paths
######################################
inc-taichi-y                          += village-os/services/taichi/inc
src-taichi-y                          += village-os/services/taichi/src


######################################
# objects
######################################
objs-taichi-y                         += taichi_service.o


######################################
# libraries
######################################
libs-taichi-y                         += utils vkc++ vkc

endif
