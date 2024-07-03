###########################################################################
# Makefile
# The Makefile of console
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_CONSOLE), y)

######################################
# applications
######################################
apps-y                                += console


######################################
# paths
######################################
inc-console-y                         += village-os/applications/console/inc
src-console-y                         += village-os/applications/console/src
src-console-y                         += village-os/applications/console/cmds


######################################
# objects
######################################
objs-console-$(CONFIG_CMD_ABOUT)      += CmdAbout.o
objs-console-$(CONFIG_CMD_DEBUG)      += CmdDebug.o
objs-console-$(CONFIG_CMD_FILESYS)    += CmdFileSys.o
objs-console-$(CONFIG_CMD_HELP)       += CmdHelp.o
objs-console-$(CONFIG_CMD_KILL)       += CmdKill.o
objs-console-$(CONFIG_CMD_MEM)        += CmdMem.o
objs-console-$(CONFIG_CMD_MOD)        += CmdMod.o
objs-console-$(CONFIG_CMD_POWER)      += CmdPower.o
objs-console-$(CONFIG_CMD_PROCESS)    += CmdProcess.o
objs-console-$(CONFIG_CMD_RUN)        += CmdRun.o
objs-console-$(CONFIG_CMD_TASKER)     += CmdTasker.o
objs-console-$(CONFIG_CONSOLE)        += CmdMsgMgr.o
objs-console-$(CONFIG_CONSOLE)        += Console.o


######################################
# libraries
######################################
libs-console-y                        += utils stdc++ c 

endif
