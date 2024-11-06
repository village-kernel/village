###########################################################################
# Makefile
# The Makefile of terminal
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_TERMINAL_APP), y)

######################################
# programs
######################################
apps-y                                += terminal


######################################
# paths
######################################
inc-terminal-y                        += village-os/programs/terminal/inc
src-terminal-y                        += village-os/programs/terminal/src


######################################
# objects
######################################
objs-terminal-y                       += terminal_app.o
objs-terminal-y                       += terminal_view.o


######################################
# libraries
######################################
libs-terminal-y                       += vkgui utils vkc++ vkc

endif


######################################
# settings
######################################
ifeq ($(CONFIG_TERMINAL_POWER_UP), y)
settings-terminal                     += power_up
endif
