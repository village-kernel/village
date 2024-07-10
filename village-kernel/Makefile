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

inc-$(CONFIG_X86)                   += village-kernel/arch/x86/bios/inc
inc-$(CONFIG_CORTEX_M)              += village-kernel/arch/arm/cortex-m/inc
inc-$(CONFIG_STM32F4xx)             += village-kernel/arch/arm/cortex-m/inc/stm32f4xx
inc-$(CONFIG_STM32H7xx)             += village-kernel/arch/arm/cortex-m/inc/stm32h7xx
src-$(CONFIG_X86)                   += village-kernel/arch/x86/bios/src
src-$(CONFIG_CORTEX_M)              += village-kernel/arch/arm/cortex-m/src
src-$(CONFIG_STM32F4xx)             += village-kernel/arch/arm/cortex-m/src/stm32f4xx
src-$(CONFIG_STM32H7xx)             += village-kernel/arch/arm/cortex-m/src/stm32h7xx

inc-$(CONFIG_SUBSYS)                += village-kernel/subsys/inc
src-$(CONFIG_SUBSYS)                += village-kernel/subsys/src

inc-$(CONFIG_EXECUTOR)              += village-kernel/executor/inc
src-$(CONFIG_EXECUTOR)              += village-kernel/executor/src

inc-$(CONFIG_FATFS)                 += village-kernel/filesys/fat/inc
src-$(CONFIG_FATFS)                 += village-kernel/filesys/fat/src

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

objs-y                              += System.o
objs-y                              += Scheduler.o
objs-y                              += Exception.o
objs-y                              += ArchInterrupt.o

objs-y                              += FileSystem.o
objs-$(CONFIG_FATFS)                += FatDiskio.o
objs-$(CONFIG_FATFS)                += FatEntry.o
objs-$(CONFIG_FATFS)                += FatObject.o
objs-$(CONFIG_FATFS)                += FatSystem.o

objs-$(CONFIG_EXECUTOR)             += BaseExecutor.o
objs-$(CONFIG_BINEXECUTOR)          += BinExecutor.o
objs-$(CONFIG_ELFEXECUTOR)          += ElfExecutor.o
objs-$(CONFIG_HEXEXECUTOR)          += HexExecutor.o


######################################
# libutils
######################################
libs-y                              += utils

inc-$(CONFIG_FILEUTILS)             += village-kernel/vklibs/libutils/fileutils/inc
inc-$(CONFIG_BINUTILS)              += village-kernel/vklibs/libutils/binutils/inc
inc-$(CONFIG_PARSER)                += village-kernel/vklibs/libutils/parser/inc
inc-$(CONFIG_MODEL)                 += village-kernel/vklibs/libutils/model/inc
inc-$(CONFIG_SYNC)                  += village-kernel/vklibs/libutils/sync/inc

src-$(CONFIG_FILEUTILS)             += village-kernel/vklibs/libutils/fileutils/src
src-$(CONFIG_BINUTILS)              += village-kernel/vklibs/libutils/binutils/src
src-$(CONFIG_PARSER)                += village-kernel/vklibs/libutils/parser/src
src-$(CONFIG_MODEL)                 += village-kernel/vklibs/libutils/model/src
src-$(CONFIG_SYNC)                  += village-kernel/vklibs/libutils/sync/src

objs-utils-$(CONFIG_DIRSTREAM)      += DirStream.o
objs-utils-$(CONFIG_DRVSTREAM)      += DrvStream.o
objs-utils-$(CONFIG_FILESTREAM)     += FileStream.o
objs-utils-$(CONFIG_FILESYSOPT)     += FileSysOpt.o

objs-utils-$(CONFIG_SPINLOCK)       += SpinLock.o
objs-utils-$(CONFIG_MUTEX)          += Mutex.o
objs-utils-$(CONFIG_SEMAPHORE)      += Semaphore.o

objs-utils-$(CONFIG_BINLOADER)      += BinLoader.o
objs-utils-$(CONFIG_ELFLOADER)      += ElfLoader.o
objs-utils-$(CONFIG_HEXLOADER)      += HexLoader.o
objs-utils-$(CONFIG_LIBTOOL)        += LibraryTool.o
objs-utils-$(CONFIG_MODTOOL)        += ModuleTool.o

objs-utils-$(CONFIG_INIPARSER)      += iniParser.o
objs-utils-$(CONFIG_PINPARSER)      += pinParser.o
objs-utils-$(CONFIG_RCPARSER)       += rcParser.o
objs-utils-$(CONFIG_REGEX)          += Regex.o

objs-utils-$(CONFIG_MODEL)          += ObserverModel.o


######################################
# libm
######################################
libs-y                              += m

inc-y                               += village-kernel/vklibs/libm/inc
src-y                               += village-kernel/vklibs/libm/src

objs-m-y                            += math.o


######################################
# libstdc++
######################################
libs-y                              += stdc++

inc-y                               += village-kernel/vklibs/libc++/inc
src-y                               += village-kernel/vklibs/libc++/src

objs-stdc++-y                       += icxxabi.o
objs-stdc++-y                       += operator.o


######################################
# libc
######################################
libs-y                              += c

inc-y                               += village-kernel/vklibs/libc/inc
src-y                               += village-kernel/vklibs/libc/src
src-y                               += village-kernel/vklibs/libc/stdio
src-y                               += village-kernel/vklibs/libc/string

objs-c-y                            += stdio.o
objs-c-y                            += stdlib.o
objs-c-y                            += string.o


#######################################
# compiler flags
#######################################
ifdef CONFIG_TASK_STACK
CFLAGS    += -DTASK_STACK=$(CONFIG_TASK_STACK)
endif


######################################
# includes
######################################
## ARM
ifeq ($(CONFIG_ARM)_$(CONFIG_CORTEX_M), y_y)
include village-kernel/vklibs/libhw/arm/cortex-m/Makefile
include village-kernel/drivers/arm/cortex-m/Makefile
endif

## X86
ifeq ($(CONFIG_X86)_$(CONFIG_BIOS), y_y)
include village-kernel/vklibs/libhw/x86/bios/Makefile
include village-kernel/drivers/x86/bios/Makefile
endif
