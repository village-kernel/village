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
inc-console-$(CONFIG_CONSOLE)                += vk.application/console/inc

src-console-$(CONFIG_CONSOLE)                += vk.application/console/src
src-console-$(CONFIG_CONSOLE)                += vk.application/console/cmds


######################################
# objects
######################################
objs-console-$(CONFIG_CMD_ABOUT)             += CmdAbout.o
objs-console-$(CONFIG_CMD_DEBUG)             += CmdDebug.o
objs-console-$(CONFIG_CMD_FILESYS)           += CmdFileSys.o
objs-console-$(CONFIG_CMD_HELP)              += CmdHelp.o
objs-console-$(CONFIG_CMD_MEM)               += CmdMem.o
objs-console-$(CONFIG_CMD_MOD)               += CmdMod.o
objs-console-$(CONFIG_CMD_POWER)             += CmdPower.o
objs-console-$(CONFIG_CMD_RUN)               += CmdRun.o
objs-console-$(CONFIG_CMD_TASKER)            += CmdTasker.o
objs-console-$(CONFIG_CONSOLE)               += CmdMsgMgr.o
objs-console-$(CONFIG_CONSOLE)               += Console.o


######################################
# libraries
######################################
libs-console-$(CONFIG_CONSOLE)               += c stdc++ kernel
