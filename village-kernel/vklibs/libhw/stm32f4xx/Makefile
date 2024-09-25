###########################################################################
# Makefile
# The Makefile of stm32f4xx
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# flags
######################################
# flash cmd
FLASH_CMD := openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg -c "program $(BUILD_DIR)/$(TARGET)-kernel.hex verify reset exit"

# MCU
MCU       := -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# defines
DEFS      := -DARCH_ARM -DUSE_HAL_DRIVER -DSTM32F407xx -D'HSE_VALUE=((uint32_t)8000000)'

# link script
LDSCRIPT-KERNEL-$(CONFIG_STM32F405RG)            := -T village-kernel/vklibs/libhw/stm32f4xx/lds/STM32F405RG_flash.ld
LDSCRIPT-KERNEL-$(CONFIG_STM32F407ZE)            := -T village-kernel/vklibs/libhw/stm32f4xx/lds/STM32F407ZE_flash.ld
LDSCRIPT-KERNEL-$(CONFIG_STM32F407ZG)            := -T village-kernel/vklibs/libhw/stm32f4xx/lds/STM32F407ZG_flash.ld


#######################################
# compiler flags
#######################################
# gcc flags
CFLAGS                                           += $(MCU) $(DEFS)
CFLAGS                                           += -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(dir $<)/$(@:.o=.list)
CFLAGS                                           += -MMD -MP -MF"$(BUILD_DIR)/$(dir $<)/$(@:%.o=%.d)"
CFLAGS                                           += -Wall -fdata-sections -ffunction-sections -fno-common
CFLAGS                                           += -mword-relocations -mlong-calls
CXXFLAGS                                         += $(CFLAGS) -fno-rtti -fno-exceptions -fno-use-cxa-atexit -fno-threadsafe-statics

# kernel ld flags
LDFLAGS-KERNEL                                   += $(MCU) $(LDSCRIPT-KERNEL-y)
LDFLAGS-KERNEL                                   += -ffreestanding -nostdlib
LDFLAGS-KERNEL                                   += -Wl,-Map=$(BUILD_DIR)/$(TARGET)-kernel.map,--cref
LDFLAGS-KERNEL                                   += -Wl,--gc-sections
LDFLAGS-KERNEL                                   += -Wl,--no-warn-rwx-segment
LDFLAGS-KERNEL                                   += -Wl,-static -pie


######################################
# paths
######################################
inc-$(CONFIG_STM32F4xx)                          += village-kernel/vklibs/libhw/stm32f4xx/cmsis
inc-$(CONFIG_STM32F4xx)                          += village-kernel/vklibs/libhw/stm32f4xx/core/inc

src-$(CONFIG_STM32F4xx)                          += village-kernel/vklibs/libhw/stm32f4xx/core/src
src-$(CONFIG_STM32F4xx)                          += village-kernel/vklibs/libhw/stm32f4xx/crt0


######################################
# objects
######################################
objs-$(CONFIG_STM32F4xx)                         += system_stm32f4xx.o
objs-$(CONFIG_STM32F401xc)                       += crt0_kernel_stm32f401xc.o
objs-$(CONFIG_STM32F401xe)                       += crt0_kernel_stm32f401xe.o
objs-$(CONFIG_STM32F405xx)                       += crt0_kernel_stm32f405xx.o
objs-$(CONFIG_STM32F407xx)                       += crt0_kernel_stm32f407xx.o
objs-$(CONFIG_STM32F410cx)                       += crt0_kernel_stm32f410cx.o
objs-$(CONFIG_STM32F410rx)                       += crt0_kernel_stm32f410rx.o
objs-$(CONFIG_STM32F410tx)                       += crt0_kernel_stm32f410tx.o
objs-$(CONFIG_STM32F411xe)                       += crt0_kernel_stm32f411xe.o
objs-$(CONFIG_STM32F412cx)                       += crt0_kernel_stm32f412cx.o
objs-$(CONFIG_STM32F412rx)                       += crt0_kernel_stm32f412rx.o
objs-$(CONFIG_STM32F412vx)                       += crt0_kernel_stm32f412vx.o
objs-$(CONFIG_STM32F412zx)                       += crt0_kernel_stm32f412zx.o
objs-$(CONFIG_STM32F413xx)                       += crt0_kernel_stm32f413xx.o
objs-$(CONFIG_STM32F415xx)                       += crt0_kernel_stm32f415xx.o
objs-$(CONFIG_STM32F417xx)                       += crt0_kernel_stm32f417xx.o
objs-$(CONFIG_STM32F423xx)                       += crt0_kernel_stm32f423xx.o
objs-$(CONFIG_STM32F427xx)                       += crt0_kernel_stm32f427xx.o
objs-$(CONFIG_STM32F429xx)                       += crt0_kernel_stm32f429xx.o
objs-$(CONFIG_STM32F437xx)                       += crt0_kernel_stm32f437xx.o
objs-$(CONFIG_STM32F439xx)                       += crt0_kernel_stm32f439xx.o
objs-$(CONFIG_STM32F446tx)                       += crt0_kernel_stm32f446tx.o
objs-$(CONFIG_STM32F469xx)                       += crt0_kernel_stm32f469xx.o
objs-$(CONFIG_STM32F479xx)                       += crt0_kernel_stm32f479xx.o


######################################
# libhw
######################################
libs-y                                           += hw


######################################
# paths
######################################
inc-$(CONFIG_STM32F4xx)                          += village-kernel/vklibs/libhw/stm32f4xx/hal/inc
inc-$(CONFIG_STM32F4xx)                          += village-kernel/vklibs/libhw/stm32f4xx/hal/inc/Legacy
src-$(CONFIG_STM32F4xx)                          += village-kernel/vklibs/libhw/stm32f4xx/hal/src


######################################
# objects
######################################
objs-hw-$(CONFIG_STM32F4XX_HAL)                  += stm32f4xx_hal.o
objs-hw-$(CONFIG_STM32F4XX_HAL_ADC)              += stm32f4xx_hal_adc.o
objs-hw-$(CONFIG_STM32F4XX_HAL_ADC_EX)           += stm32f4xx_hal_adc_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_CAN)              += stm32f4xx_hal_can.o
objs-hw-$(CONFIG_STM32F4XX_HAL_CEC)              += stm32f4xx_hal_cec.o
objs-hw-$(CONFIG_STM32F4XX_HAL_CORTEX)           += stm32f4xx_hal_cortex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_CRC)              += stm32f4xx_hal_crc.o
objs-hw-$(CONFIG_STM32F4XX_HAL_CRYP)             += stm32f4xx_hal_cryp.o
objs-hw-$(CONFIG_STM32F4XX_HAL_CRYP_EX)          += stm32f4xx_hal_cryp_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_DAC)              += stm32f4xx_hal_dac.o
objs-hw-$(CONFIG_STM32F4XX_HAL_DAC_EX)           += stm32f4xx_hal_dac_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_DCMI)             += stm32f4xx_hal_dcmi.o
objs-hw-$(CONFIG_STM32F4XX_HAL_DCMI_EX)          += stm32f4xx_hal_dcmi_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_DFSDM)            += stm32f4xx_hal_dfsdm.o
objs-hw-$(CONFIG_STM32F4XX_HAL_DMA)              += stm32f4xx_hal_dma.o
objs-hw-$(CONFIG_STM32F4XX_HAL_DMA2D)            += stm32f4xx_hal_dma2d.o
objs-hw-$(CONFIG_STM32F4XX_HAL_DMA_EX)           += stm32f4xx_hal_dma_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_DSI)              += stm32f4xx_hal_dsi.o
objs-hw-$(CONFIG_STM32F4XX_HAL_ETH)              += stm32f4xx_hal_eth.o
objs-hw-$(CONFIG_STM32F4XX_HAL_EXTI)             += stm32f4xx_hal_exti.o
objs-hw-$(CONFIG_STM32F4XX_HAL_FLASH)            += stm32f4xx_hal_flash.o
objs-hw-$(CONFIG_STM32F4XX_HAL_FLASH_EX)         += stm32f4xx_hal_flash_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_FLASH_RAMFUNC)    += stm32f4xx_hal_flash_ramfunc.o
objs-hw-$(CONFIG_STM32F4XX_HAL_FMPI2C)           += stm32f4xx_hal_fmpi2c.o
objs-hw-$(CONFIG_STM32F4XX_HAL_FMPI2C_EX)        += stm32f4xx_hal_fmpi2c_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_FMPSMBUS)         += stm32f4xx_hal_fmpsmbus.o
objs-hw-$(CONFIG_STM32F4XX_HAL_FMPSMBUS_EX)      += stm32f4xx_hal_fmpsmbus_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_GPIO)             += stm32f4xx_hal_gpio.o
objs-hw-$(CONFIG_STM32F4XX_HAL_HASH)             += stm32f4xx_hal_hash.o
objs-hw-$(CONFIG_STM32F4XX_HAL_HASH_EX)          += stm32f4xx_hal_hash_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_HCD)              += stm32f4xx_hal_hcd.o
objs-hw-$(CONFIG_STM32F4XX_HAL_I2C)              += stm32f4xx_hal_i2c.o
objs-hw-$(CONFIG_STM32F4XX_HAL_I2C_EX)           += stm32f4xx_hal_i2c_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_I2S)              += stm32f4xx_hal_i2s.o
objs-hw-$(CONFIG_STM32F4XX_HAL_I2S_EX)           += stm32f4xx_hal_i2s_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_IRDA)             += stm32f4xx_hal_irda.o
objs-hw-$(CONFIG_STM32F4XX_HAL_IWDG)             += stm32f4xx_hal_iwdg.o
objs-hw-$(CONFIG_STM32F4XX_HAL_LPTIM)            += stm32f4xx_hal_lptim.o
objs-hw-$(CONFIG_STM32F4XX_HAL_LTDC)             += stm32f4xx_hal_ltdc.o
objs-hw-$(CONFIG_STM32F4XX_HAL_LTDC_EX)          += stm32f4xx_hal_ltdc_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_MMC)              += stm32f4xx_hal_mmc.o
objs-hw-$(CONFIG_STM32F4XX_HAL_NAND)             += stm32f4xx_hal_nand.o
objs-hw-$(CONFIG_STM32F4XX_HAL_NOR)              += stm32f4xx_hal_nor.o
objs-hw-$(CONFIG_STM32F4XX_HAL_PCCARD)           += stm32f4xx_hal_pccard.o
objs-hw-$(CONFIG_STM32F4XX_HAL_PCD)              += stm32f4xx_hal_pcd.o
objs-hw-$(CONFIG_STM32F4XX_HAL_PCD_EX)           += stm32f4xx_hal_pcd_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_PWR)              += stm32f4xx_hal_pwr.o
objs-hw-$(CONFIG_STM32F4XX_HAL_PWR_EX)           += stm32f4xx_hal_pwr_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_QSPI)             += stm32f4xx_hal_qspi.o
objs-hw-$(CONFIG_STM32F4XX_HAL_RCC)              += stm32f4xx_hal_rcc.o
objs-hw-$(CONFIG_STM32F4XX_HAL_RCC_EX)           += stm32f4xx_hal_rcc_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_RNG)              += stm32f4xx_hal_rng.o
objs-hw-$(CONFIG_STM32F4XX_HAL_RTC)              += stm32f4xx_hal_rtc.o
objs-hw-$(CONFIG_STM32F4XX_HAL_RTC_EX)           += stm32f4xx_hal_rtc_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_SAI)              += stm32f4xx_hal_sai.o
objs-hw-$(CONFIG_STM32F4XX_HAL_SAI_EX)           += stm32f4xx_hal_sai_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_SD)               += stm32f4xx_hal_sd.o
objs-hw-$(CONFIG_STM32F4XX_HAL_SDRAM)            += stm32f4xx_hal_sdram.o
objs-hw-$(CONFIG_STM32F4XX_HAL_SMARTCARD)        += stm32f4xx_hal_smartcard.o
objs-hw-$(CONFIG_STM32F4XX_HAL_SMBUS)            += stm32f4xx_hal_smbus.o
objs-hw-$(CONFIG_STM32F4XX_HAL_SPDIFRX)          += stm32f4xx_hal_spdifrx.o
objs-hw-$(CONFIG_STM32F4XX_HAL_SPI)              += stm32f4xx_hal_spi.o
objs-hw-$(CONFIG_STM32F4XX_HAL_SRAM)             += stm32f4xx_hal_sram.o
objs-hw-$(CONFIG_STM32F4XX_HAL_TIM)              += stm32f4xx_hal_tim.o
objs-hw-$(CONFIG_STM32F4XX_HAL_TIM_EX)           += stm32f4xx_hal_tim_ex.o
objs-hw-$(CONFIG_STM32F4XX_HAL_UART)             += stm32f4xx_hal_uart.o
objs-hw-$(CONFIG_STM32F4XX_HAL_USART)            += stm32f4xx_hal_usart.o
objs-hw-$(CONFIG_STM32F4XX_HAL_WWDG)             += stm32f4xx_hal_wwdg.o

objs-hw-$(CONFIG_STM32F4XX_LL_ADC)               += stm32f4xx_ll_adc.o
objs-hw-$(CONFIG_STM32F4XX_LL_CRC)               += stm32f4xx_ll_crc.o
objs-hw-$(CONFIG_STM32F4XX_LL_DAC)               += stm32f4xx_ll_dac.o
objs-hw-$(CONFIG_STM32F4XX_LL_DMA)               += stm32f4xx_ll_dma.o
objs-hw-$(CONFIG_STM32F4XX_LL_DMA2D)             += stm32f4xx_ll_dma2d.o
objs-hw-$(CONFIG_STM32F4XX_LL_EXTI)              += stm32f4xx_ll_exti.o
objs-hw-$(CONFIG_STM32F4XX_LL_FMC)               += stm32f4xx_ll_fmc.o
objs-hw-$(CONFIG_STM32F4XX_LL_FMPI2C)            += stm32f4xx_ll_fmpi2c.o
objs-hw-$(CONFIG_STM32F4XX_LL_FSMC)              += stm32f4xx_ll_fsmc.o
objs-hw-$(CONFIG_STM32F4XX_LL_GPIO)              += stm32f4xx_ll_gpio.o
objs-hw-$(CONFIG_STM32F4XX_LL_I2C)               += stm32f4xx_ll_i2c.o
objs-hw-$(CONFIG_STM32F4XX_LL_LPTIM)             += stm32f4xx_ll_lptim.o
objs-hw-$(CONFIG_STM32F4XX_LL_PWR)               += stm32f4xx_ll_pwr.o
objs-hw-$(CONFIG_STM32F4XX_LL_RCC)               += stm32f4xx_ll_rcc.o
objs-hw-$(CONFIG_STM32F4XX_LL_RNG)               += stm32f4xx_ll_rng.o
objs-hw-$(CONFIG_STM32F4XX_LL_RTC)               += stm32f4xx_ll_rtc.o
objs-hw-$(CONFIG_STM32F4XX_LL_SDMMC)             += stm32f4xx_ll_sdmmc.o
objs-hw-$(CONFIG_STM32F4XX_LL_SPI)               += stm32f4xx_ll_spi.o
objs-hw-$(CONFIG_STM32F4XX_LL_TIM)               += stm32f4xx_ll_tim.o
objs-hw-$(CONFIG_STM32F4XX_LL_USART)             += stm32f4xx_ll_usart.o
objs-hw-$(CONFIG_STM32F4XX_LL_USB)               += stm32f4xx_ll_usb.o
objs-hw-$(CONFIG_STM32F4XX_LL_UTILS)             += stm32f4xx_ll_utils.o
