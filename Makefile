###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-y                     += vk.kernel/kernel/if
inc-y                     += vk.kernel/kernel/inc

src-y                     += vk.kernel
src-y                     += vk.kernel/kernel/src

inc-$(CONFIG_FATFS)       += vk.kernel/libraries/fatfs/inc
inc-$(CONFIG_CONSOLE)     += vk.kernel/console/inc
inc-$(CONFIG_UTILITIES)   += vk.kernel/utilities/inc

src-$(CONFIG_FATFS)       += vk.kernel/libraries/fatfs/src
src-$(CONFIG_CONSOLE)     += vk.kernel/console/src
src-$(CONFIG_UTILITIES)   += vk.kernel/utilities/src


######################################
# objects
######################################
objs-y                    += Start.o
objs-y                    += Kernel.o
objs-y                    += Modular.o
objs-y                    += Device.o
objs-y                    += Memory.o
objs-y                    += Thread.o
objs-y                    += Scheduler.o
objs-y                    += Interrupt.o

objs-$(CONFIG_LOADER)     += Loader.o
objs-$(CONFIG_EXECUTOR)   += Executor.o
objs-$(CONFIG_ENVIRONMENT)+= Environment.o

objs-$(CONFIG_FILESTREAM) += FileStream.o
objs-$(CONFIG_INIPARSER)  += iniParser.o
objs-$(CONFIG_PINPARSER)  += pinParser.o
objs-$(CONFIG_RCPARSER)   += rcParser.o
objs-$(CONFIG_ELFPARSER)  += ElfParser.o

objs-$(CONFIG_CMD_ABOUT)  += CmdAbout.o
objs-$(CONFIG_CMD_HELP)   += CmdHelp.o
objs-$(CONFIG_CONSOLE)    += CmdMsgMgr.o
objs-$(CONFIG_CONSOLE)    += Console.o

objs-$(CONFIG_FATFS)      += diskio.o
objs-$(CONFIG_FATFS)      += ff.o
objs-$(CONFIG_FATFS)      += ffsystem.o
objs-$(CONFIG_FATFS)      += ffunicode.o
