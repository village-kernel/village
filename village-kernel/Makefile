###########################################################################
# Makefile
# The Makefile of village-kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# kernel code
######################################
inc-y                               += village-kernel/kernel/if
inc-y                               += village-kernel/kernel/inc
src-y                               += village-kernel/kernel/src

inc-y                               += village-kernel/filesys/if
inc-y                               += village-kernel/filesys/inc
src-y                               += village-kernel/filesys/src

inc-y                               += village-kernel/terminal/if
inc-y                               += village-kernel/terminal/inc
src-y                               += village-kernel/terminal/src
src-y                               += village-kernel/terminal/cmds

inc-$(CONFIG_IA32LEGACY)            += village-kernel/arch/ia32/legacy/inc
src-$(CONFIG_IA32LEGACY)            += village-kernel/arch/ia32/legacy/src

inc-$(CONFIG_CORTEX_M)              += village-kernel/arch/arm/cortex-m/inc
inc-$(CONFIG_STM32F4xx)             += village-kernel/arch/arm/cortex-m/inc/stm32f4xx
inc-$(CONFIG_STM32H7xx)             += village-kernel/arch/arm/cortex-m/inc/stm32h7xx
src-$(CONFIG_CORTEX_M)              += village-kernel/arch/arm/cortex-m/src
src-$(CONFIG_STM32F4xx)             += village-kernel/arch/arm/cortex-m/src/stm32f4xx
src-$(CONFIG_STM32H7xx)             += village-kernel/arch/arm/cortex-m/src/stm32h7xx

inc-$(CONFIG_BINUTILS)              += village-kernel/binutils/if
inc-$(CONFIG_BINUTILS)              += village-kernel/binutils/inc
src-$(CONFIG_BINUTILS)              += village-kernel/binutils/src

inc-$(CONFIG_FATFS)                 += village-kernel/filesys/fs/fat/inc
src-$(CONFIG_FATFS)                 += village-kernel/filesys/fs/fat/src

objs-y                              += Village.o
objs-y                              += Debug.o
objs-y                              += Symbol.o
objs-y                              += Feature.o
objs-y                              += Device.o
objs-y                              += Memory.o
objs-y                              += Thread.o
objs-y                              += Interrupt.o
objs-y                              += InputEvent.o
objs-y                              += WorkQueue.o
objs-y                              += Loader.o
objs-y                              += Process.o
objs-y                              += Timer.o
objs-y                              += Signal.o

objs-y                              += System.o
objs-y                              += Scheduler.o
objs-y                              += Exception.o

objs-y                              += FileSystem.o
objs-$(CONFIG_FATFS)                += FatDiskio.o
objs-$(CONFIG_FATFS)                += FatFolder.o
objs-$(CONFIG_FATFS)                += FatObject.o
objs-$(CONFIG_FATFS)                += FatSystem.o

objs-$(CONFIG_EXECUTOR)             += BaseExecutor.o
objs-$(CONFIG_BINEXECUTOR)          += BinExecutor.o
objs-$(CONFIG_ELFEXECUTOR)          += ElfExecutor.o
objs-$(CONFIG_HEXEXECUTOR)          += HexExecutor.o
objs-$(CONFIG_BINLOADER)            += BinLoader.o
objs-$(CONFIG_ELFLOADER)            += ElfLoader.o
objs-$(CONFIG_HEXLOADER)            += HexLoader.o
objs-$(CONFIG_LIBTOOL)              += LibraryTool.o
objs-$(CONFIG_MODTOOL)              += ModuleTool.o

objs-y                              += CmdMsgMgr.o
objs-y                              += Console.o
objs-y                              += Terminal.o
objs-$(CONFIG_CMD_ABOUT)            += CmdAbout.o
objs-$(CONFIG_CMD_CAT)              += CmdCat.o
objs-$(CONFIG_CMD_DEBUG)            += CmdDebug.o
objs-$(CONFIG_CMD_ECHO)             += CmdEcho.o
objs-$(CONFIG_CMD_FILESYS)          += CmdFileSys.o
objs-$(CONFIG_CMD_HELP)             += CmdHelp.o
objs-$(CONFIG_CMD_KILL)             += CmdKill.o
objs-$(CONFIG_CMD_MEM)              += CmdMem.o
objs-$(CONFIG_CMD_MOD)              += CmdMod.o
objs-$(CONFIG_CMD_POWER)            += CmdPower.o
objs-$(CONFIG_CMD_PROCESS)          += CmdProcess.o
objs-$(CONFIG_CMD_RUN)              += CmdRun.o
objs-$(CONFIG_CMD_TASKER)           += CmdTasker.o


######################################
# libutils
######################################
libs-y                              += utils

inc-$(CONFIG_FILEUTILS)             += village-kernel/vklibs/libutils/fileutils/inc
inc-$(CONFIG_PARSER)                += village-kernel/vklibs/libutils/parser/inc
inc-$(CONFIG_MODEL)                 += village-kernel/vklibs/libutils/model/inc
inc-$(CONFIG_SYNC)                  += village-kernel/vklibs/libutils/sync/inc

src-$(CONFIG_FILEUTILS)             += village-kernel/vklibs/libutils/fileutils/src
src-$(CONFIG_PARSER)                += village-kernel/vklibs/libutils/parser/src
src-$(CONFIG_MODEL)                 += village-kernel/vklibs/libutils/model/src
src-$(CONFIG_SYNC)                  += village-kernel/vklibs/libutils/sync/src

objs-utils-$(CONFIG_DEVSTREAM)      += DevStream.o
objs-utils-$(CONFIG_DIRSTREAM)      += DirStream.o
objs-utils-$(CONFIG_FILESTREAM)     += FileStream.o
objs-utils-$(CONFIG_FILESYSOPT)     += FileSysOpt.o

objs-utils-$(CONFIG_SPINLOCK)       += SpinLock.o
objs-utils-$(CONFIG_MUTEX)          += Mutex.o
objs-utils-$(CONFIG_SEMAPHORE)      += Semaphore.o

objs-utils-$(CONFIG_INIPARSER)      += iniParser.o
objs-utils-$(CONFIG_PINPARSER)      += pinParser.o
objs-utils-$(CONFIG_RCPARSER)       += rcParser.o
objs-utils-$(CONFIG_REGEX)          += Regex.o

objs-utils-$(CONFIG_MODEL)          += ObserverModel.o


######################################
# libm
######################################
ifeq ($(CONFIG_VKLIBM), y)
libs-y                              += m

inc-y                               += village-kernel/vklibs/libm/inc
src-y                               += village-kernel/vklibs/libm/src

objs-m-y                            += math.o
endif


######################################
# libstdc++
######################################
ifeq ($(CONFIG_VKLIBCPP), y)
libs-y                              += stdc++

inc-y                               += village-kernel/vklibs/libc++/inc
src-y                               += village-kernel/vklibs/libc++/src

objs-stdc++-y                       += icxxabi.o
objs-stdc++-y                       += operator.o
endif


######################################
# libc
######################################
ifeq ($(CONFIG_VKLIBC), y)
libs-y                              += c

inc-y                               += village-kernel/vklibs/libc/inc
src-y                               += village-kernel/vklibs/libc/src
src-y                               += village-kernel/vklibs/libc/stdio
src-y                               += village-kernel/vklibs/libc/string

objs-c-y                            += stdio.o
objs-c-y                            += stdlib.o
objs-c-y                            += string.o
endif


#######################################
# compiler flags
#######################################
ifdef CONFIG_KERNEL_RSVD_HEAP
CFLAGS    += -DKERNEL_RSVD_HEAP=$(CONFIG_KERNEL_RSVD_HEAP)
endif

ifdef CONFIG_KERNEL_RSVD_STACK
CFLAGS    += -DKERNEL_RSVD_STACK=$(CONFIG_KERNEL_RSVD_STACK)
endif

ifdef CONFIG_TASK_STACK
CFLAGS    += -DTASK_STACK=$(CONFIG_TASK_STACK)
endif


######################################
# includes
######################################
# drivers
include village-kernel/drivers/Makefile

## stm32f4xx
ifeq ($(CONFIG_STM32F4xx), y)
include village-kernel/vklibs/libhw/stm32f4xx/Makefile
endif

## stm32h7xx
ifeq ($(CONFIG_STM32H7xx), y)
include village-kernel/vklibs/libhw/stm32h7xx/Makefile
endif

## ia32legacy
ifeq ($(CONFIG_IA32LEGACY), y)
include village-kernel/vklibs/libhw/ia32legacy/Makefile
endif
