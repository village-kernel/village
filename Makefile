###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
libs-$(CONFIG_KERNEL)                       += kernel


######################################
# paths
######################################
inc-y                                       += vk.kernel/core/if
inc-y                                       += vk.kernel/core/inc

src-y                                       += vk.kernel
src-y                                       += vk.kernel/core/src

inc-$(CONFIG_X86)                           += vk.kernel/arch/x86/inc
inc-$(CONFIG_CORTEX_M)                      += vk.kernel/arch/arm/cortex-m/inc
inc-$(CONFIG_STM32F4xx)                     += vk.kernel/arch/arm/cortex-m/inc/stm32f4xx
inc-$(CONFIG_STM32H7xx)                     += vk.kernel/arch/arm/cortex-m/inc/stm32h7xx

src-$(CONFIG_X86)                           += vk.kernel/arch/x86/src
src-$(CONFIG_CORTEX_M)                      += vk.kernel/arch/arm/cortex-m/src
src-$(CONFIG_STM32F4xx)                     += vk.kernel/arch/arm/cortex-m/src/stm32f4xx
src-$(CONFIG_STM32H7xx)                     += vk.kernel/arch/arm/cortex-m/src/stm32h7xx

inc-$(CONFIG_SYNC)                          += vk.kernel/sync/inc
inc-$(CONFIG_BRIDGE)                        += vk.kernel/bridge/inc
inc-$(CONFIG_BINUTILS)                      += vk.kernel/binutils/inc
inc-$(CONFIG_UTILITIES)                     += vk.kernel/utilities/inc

src-$(CONFIG_SYNC)                          += vk.kernel/sync/src
src-$(CONFIG_BRIDGE)                        += vk.kernel/bridge/src
src-$(CONFIG_BINUTILS)                      += vk.kernel/binutils/src
src-$(CONFIG_UTILITIES)                     += vk.kernel/utilities/src

inc-$(CONFIG_FILESYSTEM)                   += vk.kernel/filesys/class/inc
inc-$(CONFIG_FILESYSTEM)                   += vk.kernel/filesys/core/inc
inc-$(CONFIG_FATFS)                        += vk.kernel/filesys/fat/inc

src-$(CONFIG_FILESYSTEM)                   += vk.kernel/filesys/class/src
src-$(CONFIG_FILESYSTEM)                   += vk.kernel/filesys/core/src
src-$(CONFIG_FATFS)                        += vk.kernel/filesys/fat/src

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

objs-y                                      += ArchInterrupt.o
objs-y                                      += Exception.o
objs-y                                      += Scheduler.o
objs-y                                      += System.o

objs-$(CONFIG_INPUT)                        += Input.o
objs-$(CONFIG_LOADER)                       += Loader.o
objs-$(CONFIG_ENVIRONMENT)                  += Environment.o
objs-$(CONFIG_WORKQUEUE)                    += WorkQueue.o

objs-$(CONFIG_FATFS)                        += FatData.o
objs-$(CONFIG_FATFS)                        += FatDisk.o
objs-$(CONFIG_FATFS)                        += FatEntry.o
objs-$(CONFIG_FATFS)                        += FatName.o
objs-$(CONFIG_FATFS)                        += FatOpts.o
objs-$(CONFIG_FATFS)                        += FatSystem.o
objs-$(CONFIG_FILESYSTEM)                   += FileSystem.o

objs-kernel-$(CONFIG_FILESYSTEM)            += DirStream.o
objs-kernel-$(CONFIG_FILESYSTEM)            += FileStream.o
objs-kernel-$(CONFIG_FILESYSTEM)            += FileSysOpt.o

objs-kernel-$(CONFIG_SPINLOCK)              += SpinLock.o
objs-kernel-$(CONFIG_MUTEX)                 += Mutex.o
objs-kernel-$(CONFIG_SEMAPHORE)             += Semaphore.o

objs-kernel-$(CONFIG_VILLAGE)               += Village.o

objs-kernel-$(CONFIG_ELFLOADER)             += ElfLoader.o
objs-kernel-$(CONFIG_EXECUTOR)              += Executor.o
objs-kernel-$(CONFIG_LIBTOOL)               += LibraryTool.o
objs-kernel-$(CONFIG_MODTOOL)               += ModuleTool.o

objs-kernel-$(CONFIG_INIPARSER)             += iniParser.o
objs-kernel-$(CONFIG_PINPARSER)             += pinParser.o
objs-kernel-$(CONFIG_RCPARSER)              += rcParser.o
objs-kernel-$(CONFIG_REGEX)                 += Regex.o


#######################################
# compiler flags
#######################################
ifdef CONFIG_TASK_STACK
CFLAGS    += -DTASK_STACK=$(CONFIG_TASK_STACK)
endif
