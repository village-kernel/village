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
inc-taichi-y                          += village-demo/services/taichi/inc
src-taichi-y                          += village-demo/services/taichi/src


######################################
# objects
######################################
objs-taichi-y                         += taichi_service.o


######################################
# libraries
######################################
libs-taichi-y                         += misc vkc++ vkc

endif
