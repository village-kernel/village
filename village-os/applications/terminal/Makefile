###########################################################################
# Makefile
# The Makefile of terminal
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_TERMINAL_APP), y)

######################################
# applications
######################################
apps-y                                += terminal


######################################
# paths
######################################
inc-terminal-y                        += village-os/applications/terminal/inc
src-terminal-y                        += village-os/applications/terminal/src


######################################
# objects
######################################
objs-terminal-y                       += TerminalUI.o
objs-terminal-y                       += TerminalDrv.o
objs-terminal-y                       += TerminalApp.o


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
