###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
libs-y                                     += kernel


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
objs-kernel-y                               += Kernel.o
objs-kernel-y                               += Modular.o
objs-kernel-y                               += Device.o
objs-kernel-y                               += Memory.o
objs-kernel-y                               += Thread.o
objs-kernel-y                               += Synchronize.o

objs-kernel-y                               += Interrupt.o
objs-kernel-y                               += Scheduler.o
objs-kernel-y                               += System.o

objs-kernel-$(CONFIG_LOADER)                += Loader.o
objs-kernel-$(CONFIG_EXECUTOR)              += Executor.o
objs-kernel-$(CONFIG_ENVIRONMENT)           += Environment.o
objs-kernel-$(CONFIG_WORKQUEUE)             += WorkQueue.o

objs-kernel-$(CONFIG_FILESTREAM)            += FileStream.o
objs-kernel-$(CONFIG_INIPARSER)             += iniParser.o
objs-kernel-$(CONFIG_PINPARSER)             += pinParser.o
objs-kernel-$(CONFIG_RCPARSER)              += rcParser.o
objs-kernel-$(CONFIG_ELFPARSER)             += ElfParser.o

objs-kernel-$(CONFIG_CMD_ABOUT)             += CmdAbout.o
objs-kernel-$(CONFIG_CMD_HELP)              += CmdHelp.o
objs-kernel-$(CONFIG_CONSOLE)               += CmdMsgMgr.o
objs-kernel-$(CONFIG_CONSOLE)               += Console.o


#######################################
# compiler flags
#######################################
ifdef CONFIG_TASK_STACK
CFLAGS    += -DTASK_STACK=$(CONFIG_TASK_STACK)
endif
