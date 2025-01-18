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

inc-y                               += village-kernel/protocol/if
inc-y                               += village-kernel/protocol/inc
src-y                               += village-kernel/protocol/src

inc-$(CONFIG_USBD)                  += village-kernel/protocol/stack/usb/device/inc
src-$(CONFIG_USBD)                  += village-kernel/protocol/stack/usb/device/src
inc-$(CONFIG_USBH)                  += village-kernel/protocol/stack/usb/host/inc
src-$(CONFIG_USBH)                  += village-kernel/protocol/stack/usb/host/src

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

objs-y                              += vk_village.o
objs-y                              += vk_debug.o
objs-y                              += vk_symbol.o
objs-y                              += vk_feature.o
objs-y                              += vk_device.o
objs-y                              += vk_memory.o
objs-y                              += vk_thread.o
objs-y                              += vk_interrupt.o
objs-y                              += vk_event.o
objs-y                              += vk_workqueue.o
objs-y                              += vk_loader.o
objs-y                              += vk_process.o
objs-y                              += vk_timer.o
objs-y                              += vk_signal.o

objs-y                              += vk_system.o
objs-y                              += vk_scheduler.o
objs-y                              += vk_exception.o

objs-y                              += vk_filesystem.o
objs-$(CONFIG_FATFS)                += vk_fat_diskio.o
objs-$(CONFIG_FATFS)                += vk_fat_folder.o
objs-$(CONFIG_FATFS)                += vk_fat_object.o
objs-$(CONFIG_FATFS)                += vk_fat_system.o

objs-$(CONFIG_EXECUTOR)             += vk_base_executor.o
objs-$(CONFIG_BINEXECUTOR)          += vk_bin_executor.o
objs-$(CONFIG_ELFEXECUTOR)          += vk_elf_executor.o
objs-$(CONFIG_HEXEXECUTOR)          += vk_hex_executor.o
objs-$(CONFIG_BINLOADER)            += vk_bin_loader.o
objs-$(CONFIG_ELFLOADER)            += vk_elf_loader.o
objs-$(CONFIG_HEXLOADER)            += vk_hex_loader.o
objs-$(CONFIG_LIBTOOL)              += vk_library_tool.o
objs-$(CONFIG_MODTOOL)              += vk_module_tool.o

objs-y                              += vk_protocol.o
objs-$(CONFIG_USBD)                 += vk_usb_device.o
objs-$(CONFIG_USBH)                 += vk_usb_host.o

objs-y                              += vk_cmdmsg.o
objs-y                              += vk_console.o
objs-y                              += vk_terminal.o
objs-$(CONFIG_CMD_ABOUT)            += vk_cmd_about.o
objs-$(CONFIG_CMD_CAT)              += vk_cmd_cat.o
objs-$(CONFIG_CMD_DEBUG)            += vk_cmd_debug.o
objs-$(CONFIG_CMD_DEVICE)           += vk_cmd_device.o
objs-$(CONFIG_CMD_ECHO)             += vk_cmd_echo.o
objs-$(CONFIG_CMD_FILESYS)          += vk_cmd_filesys.o
objs-$(CONFIG_CMD_HELP)             += vk_cmd_help.o
objs-$(CONFIG_CMD_KILL)             += vk_cmd_kill.o
objs-$(CONFIG_CMD_MEM)              += vk_cmd_memory.o
objs-$(CONFIG_CMD_MOD)              += vk_cmd_mod.o
objs-$(CONFIG_CMD_NULL)             += vk_cmd_null.o
objs-$(CONFIG_CMD_POWER)            += vk_cmd_power.o
objs-$(CONFIG_CMD_PROCESS)          += vk_cmd_process.o
objs-$(CONFIG_CMD_RUN)              += vk_cmd_run.o
objs-$(CONFIG_CMD_TASKER)           += vk_cmd_tasker.o


######################################
# libutils
######################################
libs-y                              += utils

inc-y                               += village-kernel/vklibs/libutils/template
inc-$(CONFIG_FILEUTILS)             += village-kernel/vklibs/libutils/fileutils/inc
inc-$(CONFIG_PARSER)                += village-kernel/vklibs/libutils/parser/inc
inc-$(CONFIG_MODEL)                 += village-kernel/vklibs/libutils/model/inc
inc-$(CONFIG_SYNC)                  += village-kernel/vklibs/libutils/sync/inc

src-$(CONFIG_FILEUTILS)             += village-kernel/vklibs/libutils/fileutils/src
src-$(CONFIG_PARSER)                += village-kernel/vklibs/libutils/parser/src
src-$(CONFIG_MODEL)                 += village-kernel/vklibs/libutils/model/src
src-$(CONFIG_SYNC)                  += village-kernel/vklibs/libutils/sync/src

objs-utils-$(CONFIG_DEVSTREAM)      += vk_dev_stream.o
objs-utils-$(CONFIG_DIRSTREAM)      += vk_dir_stream.o
objs-utils-$(CONFIG_FILESTREAM)     += vk_file_stream.o
objs-utils-$(CONFIG_FILESYSOPT)     += vk_filesys_opt.o

objs-utils-$(CONFIG_SPINLOCK)       += vk_spinlock.o
objs-utils-$(CONFIG_MUTEX)          += vk_mutex.o
objs-utils-$(CONFIG_SEMAPHORE)      += vk_semaphore.o

objs-utils-$(CONFIG_INIPARSER)      += vk_ini_parser.o
objs-utils-$(CONFIG_RCPARSER)       += vk_rc_parser.o
objs-utils-$(CONFIG_REGEX)          += vk_regex.o

objs-utils-$(CONFIG_MODEL)          += vk_observer.o


######################################
# libm
######################################
ifeq ($(CONFIG_VKLIBM), y)
libs-y                              += vkm

inc-y                               += village-kernel/vklibs/libm/inc
src-y                               += village-kernel/vklibs/libm/src

objs-vkm-y                          += math.o
endif


######################################
# libstdc++
######################################
ifeq ($(CONFIG_VKLIBCPP), y)
libs-y                              += vkc++

inc-y                               += village-kernel/vklibs/libc++/inc
src-y                               += village-kernel/vklibs/libc++/src

objs-vkc++-y                        += icxxabi.o
objs-vkc++-y                        += operator.o
endif


######################################
# libc
######################################
ifeq ($(CONFIG_VKLIBC), y)
libs-y                              += vkc

inc-y                               += village-kernel/vklibs/libc/inc
src-y                               += village-kernel/vklibs/libc/src
src-y                               += village-kernel/vklibs/libc/stdio
src-y                               += village-kernel/vklibs/libc/string

objs-vkc-y                          += stdio.o
objs-vkc-y                          += stdlib.o
objs-vkc-y                          += string.o
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
