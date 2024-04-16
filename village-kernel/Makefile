###########################################################################
# Makefile
# The Makefile of village-kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# kernel code
######################################
inc-y                               += village-kernel/kernel/core/if
inc-y                               += village-kernel/kernel/core/inc
src-y                               += village-kernel/kernel/core/src

inc-$(CONFIG_X86)                   += village-kernel/kernel/arch/x86/bios/inc
inc-$(CONFIG_CORTEX_M)              += village-kernel/kernel/arch/arm/cortex-m/inc
inc-$(CONFIG_STM32F4xx)             += village-kernel/kernel/arch/arm/cortex-m/inc/stm32f4xx
inc-$(CONFIG_STM32H7xx)             += village-kernel/kernel/arch/arm/cortex-m/inc/stm32h7xx
src-$(CONFIG_X86)                   += village-kernel/kernel/arch/x86/bios/src
src-$(CONFIG_CORTEX_M)              += village-kernel/kernel/arch/arm/cortex-m/src
src-$(CONFIG_STM32F4xx)             += village-kernel/kernel/arch/arm/cortex-m/src/stm32f4xx
src-$(CONFIG_STM32H7xx)             += village-kernel/kernel/arch/arm/cortex-m/src/stm32h7xx

inc-$(CONFIG_SUBSYS)                += village-kernel/subsys/inc
src-$(CONFIG_SUBSYS)                += village-kernel/subsys/src

inc-$(CONFIG_FILESYSTEM)            += village-kernel/filesys/core/inc
inc-$(CONFIG_FATFS)                 += village-kernel/filesys/fat/inc

src-$(CONFIG_FILESYSTEM)            += village-kernel/filesys/core/src
src-$(CONFIG_FATFS)                 += village-kernel/filesys/fat/src

objs-y                              += Village.o
objs-y                              += Debug.o
objs-y                              += Symbol.o
objs-y                              += Feature.o
objs-y                              += Device.o
objs-y                              += Memory.o
objs-y                              += Thread.o
objs-y                              += Interrupt.o

objs-y                              += ArchInterrupt.o
objs-y                              += Exception.o
objs-y                              += Scheduler.o
objs-y                              += System.o

objs-$(CONFIG_INPUT)                += Input.o
objs-$(CONFIG_LOADER)               += Loader.o
objs-$(CONFIG_WORKQUEUE)            += WorkQueue.o

objs-$(CONFIG_FILESYSTEM)           += FileSys.o
objs-$(CONFIG_FATFS)                += FatDiskio.o
objs-$(CONFIG_FATFS)                += FatEntry.o
objs-$(CONFIG_FATFS)                += FatObject.o
objs-$(CONFIG_FATFS)                += FatSystem.o
objs-$(CONFIG_FATFS)                += FatVolume.o


######################################
# libkernel
######################################
libs-$(CONFIG_KERNEL)               += kernel

inc-$(CONFIG_FILEUTILS)             += village-kernel/utilities/fileutils/inc
inc-$(CONFIG_BINUTILS)              += village-kernel/utilities/binutils/inc
inc-$(CONFIG_PARSER)                += village-kernel/utilities/parser/inc
inc-$(CONFIG_SYNC)                  += village-kernel/utilities/sync/inc

src-$(CONFIG_FILEUTILS)             += village-kernel/utilities/fileutils/src
src-$(CONFIG_BINUTILS)              += village-kernel/utilities/binutils/src
src-$(CONFIG_PARSER)                += village-kernel/utilities/parser/src
src-$(CONFIG_SYNC)                  += village-kernel/utilities/sync/src

objs-kernel-$(CONFIG_DIRSTREAM)     += DirStream.o
objs-kernel-$(CONFIG_DRVSTREAM)     += DrvStream.o
objs-kernel-$(CONFIG_FILESTREAM)    += FileStream.o
objs-kernel-$(CONFIG_FILESYSOPT)    += FileSysOpt.o

objs-kernel-$(CONFIG_SPINLOCK)      += SpinLock.o
objs-kernel-$(CONFIG_MUTEX)         += Mutex.o
objs-kernel-$(CONFIG_SEMAPHORE)     += Semaphore.o

objs-kernel-$(CONFIG_BINUTILS)      += BaseExecutor.o
objs-kernel-$(CONFIG_BINLOADER)     += BinLoader.o
objs-kernel-$(CONFIG_BINEXECUTOR)   += BinExecutor.o
objs-kernel-$(CONFIG_ELFLOADER)     += ElfLoader.o
objs-kernel-$(CONFIG_ELFEXECUTOR)   += ElfExecutor.o
objs-kernel-$(CONFIG_LIBTOOL)       += LibraryTool.o
objs-kernel-$(CONFIG_MODTOOL)       += ModuleTool.o

objs-kernel-$(CONFIG_INIPARSER)     += iniParser.o
objs-kernel-$(CONFIG_PINPARSER)     += pinParser.o
objs-kernel-$(CONFIG_RCPARSER)      += rcParser.o
objs-kernel-$(CONFIG_REGEX)         += Regex.o


######################################
# libm
######################################
libs-y                              += m

inc-y                               += village-kernel/stdlib/libm/inc
src-y                               += village-kernel/stdlib/libm/src

objs-m-y                            += math.o


######################################
# libstdc++
######################################
libs-y                              += stdc++

inc-y                               += village-kernel/stdlib/libc++/inc
src-y                               += village-kernel/stdlib/libc++/src

objs-stdc++-y                       += icxxabi.o
objs-stdc++-y                       += operator.o


######################################
# libc
######################################
libs-y                              += c

inc-y                               += village-kernel/stdlib/libc/inc
src-y                               += village-kernel/stdlib/libc/src
src-y                               += village-kernel/stdlib/libc/stdio
src-y                               += village-kernel/stdlib/libc/string

objs-c-y                            += $(patsubst %.c, %.o, $(notdir $(wildcard village-kernel/stdlib/libc/src/*.c)))
objs-c-y                            += $(patsubst %.c, %.o, $(notdir $(wildcard village-kernel/stdlib/libc/stdio/*.c)))
objs-c-y                            += $(patsubst %.c, %.o, $(notdir $(wildcard village-kernel/stdlib/libc/string/*.c)))


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
-include village-kernel/arch/arm/cortex-m/Makefile
-include village-kernel/drivers/arm/cortex-m/Makefile
endif

## X86
ifeq ($(CONFIG_X86)_$(CONFIG_BIOS), y_y)
-include village-kernel/arch/x86/bios/Makefile
-include village-kernel/drivers/x86/bios/Makefile
endif
