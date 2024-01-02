###########################################################################
# Makefile
# The Makefile of console
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# applications
######################################
apps-$(CONFIG_CONSOLE)                       += console


######################################
# paths
######################################
inc-$(CONFIG_CONSOLE)                        += vk.application/console/inc

src-$(CONFIG_CONSOLE)                        += vk.application/console/src
src-$(CONFIG_CONSOLE)                        += vk.application/console/cmds


######################################
# objects
######################################
objs-console-$(CONFIG_CMD_ABOUT)             += CmdAbout.o
objs-console-$(CONFIG_CMD_FILESYS)           += CmdFileSys.o
objs-console-$(CONFIG_CMD_HELP)              += CmdHelp.o
objs-console-$(CONFIG_CMD_MEM)               += CmdMem.o
objs-console-$(CONFIG_CMD_MOD)               += CmdMod.o
objs-console-$(CONFIG_CMD_RUN)               += CmdRun.o
objs-console-$(CONFIG_CONSOLE)               += CmdMsgMgr.o
objs-console-$(CONFIG_CONSOLE)               += Console.o


######################################
# libraries
######################################
libs-console-$(CONFIG_CONSOLE)               += c stdc++ kernel
