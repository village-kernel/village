###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
libs-$(CONFIG_UTILITIES)                    += utils


######################################
# paths
######################################
inc-y                                       += vk.kernel/kernel/if
inc-y                                       += vk.kernel/kernel/inc

inc-$(CONFIG_X86)                           += vk.kernel/arch/x86/inc
inc-$(CONFIG_CORTEX_M)                      += vk.kernel/arch/arm/cortex-m/inc
inc-$(CONFIG_STM32F4xx)                     += vk.kernel/arch/arm/cortex-m/inc/stm32f4xx
inc-$(CONFIG_STM32H7xx)                     += vk.kernel/arch/arm/cortex-m/inc/stm32h7xx

src-y                                       += vk.kernel
src-y                                       += vk.kernel/kernel/src

src-$(CONFIG_X86)                           += vk.kernel/arch/x86/src
src-$(CONFIG_CORTEX_M)                      += vk.kernel/arch/arm/cortex-m/src
src-$(CONFIG_STM32F4xx)                     += vk.kernel/arch/arm/cortex-m/src/stm32f4xx
src-$(CONFIG_STM32H7xx)                     += vk.kernel/arch/arm/cortex-m/src/stm32h7xx

inc-$(CONFIG_CONSOLE)                       += vk.kernel/console/inc
inc-$(CONFIG_UTILITIES)                     += vk.kernel/utilities/inc

src-$(CONFIG_CONSOLE)                       += vk.kernel/console/src
src-$(CONFIG_UTILITIES)                     += vk.kernel/utilities/src


######################################
# objects
######################################
objs-y                                      += Start.o
objs-y                                      += Kernel.o
objs-y                                      += Debug.o
objs-y                                      += Modular.o
objs-y                                      += Device.o
objs-y                                      += Memory.o
objs-y                                      += Thread.o

objs-y                                      += Interrupt.o
objs-y                                      += Scheduler.o
objs-y                                      += System.o

objs-$(CONFIG_LOADER)                       += Loader.o
objs-$(CONFIG_ENVIRONMENT)                  += Environment.o
objs-$(CONFIG_WORKQUEUE)                    += WorkQueue.o

objs-$(CONFIG_CMD_ABOUT)                    += CmdAbout.o
objs-$(CONFIG_CMD_HELP)                     += CmdHelp.o
objs-$(CONFIG_CMD_RUN)                      += CmdRun.o
objs-$(CONFIG_CMD_MOD)                      += CmdMod.o
objs-$(CONFIG_CONSOLE)                      += CmdMsgMgr.o
objs-$(CONFIG_CONSOLE)                      += Console.o

objs-utils-$(CONFIG_SYNCLOCK)               += SyncLock.o
objs-utils-$(CONFIG_FILESTREAM)             += FileStream.o
objs-utils-$(CONFIG_INIPARSER)              += iniParser.o
objs-utils-$(CONFIG_PINPARSER)              += pinParser.o
objs-utils-$(CONFIG_RCPARSER)               += rcParser.o
objs-utils-$(CONFIG_ELFPARSER)              += ElfParser.o
objs-utils-$(CONFIG_EXECUTOR)               += Executor.o
objs-utils-$(CONFIG_LIBMANAGER)             += LibManager.o
objs-utils-$(CONFIG_MODMANAGER)             += ModManager.o
objs-utils-$(CONFIG_REGEX)                  += Regex.o


#######################################
# compiler flags
#######################################
ifdef CONFIG_TASK_STACK
CFLAGS    += -DTASK_STACK=$(CONFIG_TASK_STACK)
endif
