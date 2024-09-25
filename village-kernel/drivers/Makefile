###########################################################################
# Makefile
# The Makefile of village-kernel/drivers
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-y                                 += village-kernel/drivers/mach/inc
src-y                                 += village-kernel/drivers/mach/src

objs-$(CONFIG_IA32LEGACY)             += IA32legacyDevices.o
objs-$(CONFIG_STM32F4xx)              += Stm32f407Devices.o
objs-$(CONFIG_STM32H7xx)              += Stm32h743Devices.o


######################################
# platform
######################################
ifeq ($(CONFIG_IA32LEGACY), y)
inc-y                                 += village-kernel/drivers/platform/ia32legacy/inc
src-y                                 += village-kernel/drivers/platform/ia32legacy/src

objs-$(CONFIG_IA32LEGACY_DRV_PCI)     += PCIController.o
objs-$(CONFIG_IA32LEGACY_DRV_PS2)     += PS2Controller.o

else ifeq ($(CONFIG_STM32F4xx), y)
inc-y                                 += village-kernel/drivers/platform/stm32f4xx/inc
src-y                                 += village-kernel/drivers/platform/stm32f4xx/src

objs-$(CONFIG_STM32F4XX_DRV_HAL)      += Hal.o
objs-$(CONFIG_STM32F4XX_DRV_GPIO)     += Gpio.o
objs-$(CONFIG_STM32F4XX_DRV_NVIC)     += Nvic.o
objs-$(CONFIG_STM32F4XX_DRV_USART)    += Usart.o
objs-$(CONFIG_STM32F4XX_DRV_SPI)      += Spi.o
objs-$(CONFIG_STM32F4XX_DRV_I2C)      += I2c.o
objs-$(CONFIG_STM32F4XX_DRV_DMA)      += Dma.o
objs-$(CONFIG_STM32F4XX_DRV_FSMC)     += Fsmc.o
objs-$(CONFIG_STM32F4XX_DRV_EXTI)     += Exti.o

else ifeq ($(CONFIG_STM32H7xx), y)
inc-y                                 += village-kernel/drivers/platform/stm32h7xx/inc
src-y                                 += village-kernel/drivers/platform/stm32h7xx/src

objs-$(CONFIG_STM32H7XX_DRV_HAL)      += Hal.o
objs-$(CONFIG_STM32H7XX_DRV_GPIO)     += Gpio.o
objs-$(CONFIG_STM32H7XX_DRV_LTDC)     += Ltdc.o
objs-$(CONFIG_STM32H7XX_DRV_NVIC)     += Nvic.o
objs-$(CONFIG_STM32H7XX_DRV_USART)    += Usart.o
objs-$(CONFIG_STM32H7XX_DRV_SDIO)     += Sdio.o
objs-$(CONFIG_STM32H7XX_DRV_SPI)      += Spi.o
objs-$(CONFIG_STM32H7XX_DRV_I2C)      += I2c.o
objs-$(CONFIG_STM32H7XX_DRV_DMA)      += Dma.o
objs-$(CONFIG_STM32H7XX_DRV_FSMC)     += Fsmc.o
endif


######################################
# block
######################################
inc-y                                 += village-kernel/drivers/peripheral/block/inc
src-y                                 += village-kernel/drivers/peripheral/block/src

objs-$(CONFIG_ATALBADISK)             += AtaLbaDisk.o
objs-$(CONFIG_SDIOSDCARD)             += SdioSdCard.o
objs-$(CONFIG_SPISDCARD)              += SpiSdCard.o
objs-$(CONFIG_SPIW25QXX)              += SpiW25qxx.o


######################################
# display
######################################
inc-y                                 += village-kernel/drivers/peripheral/display/inc
src-y                                 += village-kernel/drivers/peripheral/display/src

objs-$(CONFIG_BOCHSVBE)               += BochsVBE.o
objs-$(CONFIG_ILI9488)                += ILI9488.o


######################################
# dma
######################################
inc-y                                 += village-kernel/drivers/peripheral/dma/inc
src-y                                 += village-kernel/drivers/peripheral/dma/src

objs-$(CONFIG_STM32DMA)               += Stm32Dma.o


######################################
# keyboard
######################################
inc-y                                 += village-kernel/drivers/peripheral/keyboard/inc
src-y                                 += village-kernel/drivers/peripheral/keyboard/src

objs-$(CONFIG_PS2KEYBOARD)            += PS2KeyBoard.o


######################################
# mouse
######################################
inc-y                                 += village-kernel/drivers/peripheral/mouse/inc
src-y                                 += village-kernel/drivers/peripheral/mouse/src

objs-$(CONFIG_PS2MOUSE)               += PS2Mouse.o


######################################
# serial
######################################
inc-y                                 += village-kernel/drivers/peripheral/serial/inc
src-y                                 += village-kernel/drivers/peripheral/serial/src

objs-$(CONFIG_PIC32UART)              += Pic32Uart.o
objs-$(CONFIG_STM32UART)              += Stm32Uart.o


######################################
# timer
######################################
inc-y                                 += village-kernel/drivers/peripheral/timer/inc
src-y                                 += village-kernel/drivers/peripheral/timer/src

objs-$(CONFIG_PIT32TIMER)             += Pit32Timer.o


######################################
# usb
######################################
inc-y                                 += village-kernel/drivers/peripheral/usb/inc
src-y                                 += village-kernel/drivers/peripheral/usb/src

objs-$(CONFIG_STM32USBDFS)            += Stm32UsbdFS.o
