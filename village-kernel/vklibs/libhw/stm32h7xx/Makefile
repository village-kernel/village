###########################################################################
# Makefile
# The Makefile of stm32h7xx
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# flags
######################################
# flash cmd
FLASH_CMD := openocd -f interface/stlink-v2.cfg -f target/stm32h7x.cfg -c "program $(BUILD_DIR)/$(TARGET)-kernel.hex verify reset exit"

# MCU
MCU       := -mcpu=cortex-m7 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard

# defines
DEFS      := -DARCH_ARM -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -D'HSE_VALUE=((uint32_t)25000000)'
ifeq ($(CONFIG_STM32H743II), y)
DEFS      += -DSTM32H743xx
else ifeq ($(CONFIG_STM32H750VB), y)
DEFS      += -DSTM32H750xx
endif

# link script
LDSCRIPT-KERNEL-$(CONFIG_STM32H743II)            := -T village-kernel/vklibs/libhw/stm32h7xx/lds/STM32H743II_flash.ld
LDSCRIPT-KERNEL-$(CONFIG_STM32H750VB)            := -T village-kernel/vklibs/libhw/stm32h7xx/lds/STM32H750VB_flash.ld


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
inc-$(CONFIG_STM32H7xx)                          += village-kernel/vklibs/libhw/stm32h7xx/cmsis
inc-$(CONFIG_STM32H7xx)                          += village-kernel/vklibs/libhw/stm32h7xx/core/inc

src-$(CONFIG_STM32H7xx)                          += village-kernel/vklibs/libhw/stm32h7xx/core/src
src-$(CONFIG_STM32H7xx)                          += village-kernel/vklibs/libhw/stm32h7xx/crt0


######################################
# objects
######################################
objs-$(CONFIG_STM32H7xx)                         += system_stm32h7xx.o
objs-$(CONFIG_STM32H7a3xx)                       += crt0_kernel_stm32h7a3xx.o
objs-$(CONFIG_STM32H7a3xxq)                      += crt0_kernel_stm32h7a3xxq.o
objs-$(CONFIG_STM32H7b0xx)                       += crt0_kernel_stm32h7b0xx.o
objs-$(CONFIG_STM32H7b0xxq)                      += crt0_kernel_stm32h7b0xxq.o
objs-$(CONFIG_STM32H7b3xx)                       += crt0_kernel_stm32h7b3xx.o
objs-$(CONFIG_STM32H7b3xxq)                      += crt0_kernel_stm32h7b3xxq.o
objs-$(CONFIG_STM32H723xx)                       += crt0_kernel_stm32h723xx.o
objs-$(CONFIG_STM32H725xx)                       += crt0_kernel_stm32h725xx.o
objs-$(CONFIG_STM32H730xx)                       += crt0_kernel_stm32h730xx.o
objs-$(CONFIG_STM32H730xxq)                      += crt0_kernel_stm32h730xxq.o
objs-$(CONFIG_STM32H733xx)                       += crt0_kernel_stm32h733xx.o
objs-$(CONFIG_STM32H735xx)                       += crt0_kernel_stm32h735xx.o
objs-$(CONFIG_STM32H742xx)                       += crt0_kernel_stm32h742xx.o
objs-$(CONFIG_STM32H743xx)                       += crt0_kernel_stm32h743xx.o
objs-$(CONFIG_STM32H745xg)                       += crt0_kernel_stm32h745xg.o
objs-$(CONFIG_STM32H745xx)                       += crt0_kernel_stm32h745xx.o
objs-$(CONFIG_STM32H747xg)                       += crt0_kernel_stm32h747xg.o
objs-$(CONFIG_STM32H747xx)                       += crt0_kernel_stm32h747xx.o
objs-$(CONFIG_STM32H750xx)                       += crt0_kernel_stm32h750xx.o
objs-$(CONFIG_STM32H753xx)                       += crt0_kernel_stm32h753xx.o
objs-$(CONFIG_STM32H755xx)                       += crt0_kernel_stm32h755xx.o
objs-$(CONFIG_STM32H757xx)                       += crt0_kernel_stm32h757xx.o


######################################
# libhw
######################################
libs-y                                           += hw


######################################
# paths
######################################
inc-$(CONFIG_STM32H7xx)                          += village-kernel/vklibs/libhw/stm32h7xx/hal/inc
inc-$(CONFIG_STM32H7xx)                          += village-kernel/vklibs/libhw/stm32h7xx/hal/inc/Legacy
src-$(CONFIG_STM32H7xx)                          += village-kernel/vklibs/libhw/stm32h7xx/hal/src


######################################
# objects
######################################
objs-hw-$(CONFIG_STM32H7XX_HAL)                  += stm32h7xx_hal.o
objs-hw-$(CONFIG_STM32H7XX_HAL_ADC)              += stm32h7xx_hal_adc.o
objs-hw-$(CONFIG_STM32H7XX_HAL_ADC_EX)           += stm32h7xx_hal_adc_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_CEC)              += stm32h7xx_hal_cec.o
objs-hw-$(CONFIG_STM32H7XX_HAL_COMP)             += stm32h7xx_hal_comp.o
objs-hw-$(CONFIG_STM32H7XX_HAL_CORDIC)           += stm32h7xx_hal_cordic.o
objs-hw-$(CONFIG_STM32H7XX_HAL_CORTEX)           += stm32h7xx_hal_cortex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_CRC)              += stm32h7xx_hal_crc.o
objs-hw-$(CONFIG_STM32H7XX_HAL_CRC_EX)           += stm32h7xx_hal_crc_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_CRYP)             += stm32h7xx_hal_cryp.o
objs-hw-$(CONFIG_STM32H7XX_HAL_CRYP_EX)          += stm32h7xx_hal_cryp_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_DAC)              += stm32h7xx_hal_dac.o
objs-hw-$(CONFIG_STM32H7XX_HAL_DAC_EX)           += stm32h7xx_hal_dac_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_DCMI)             += stm32h7xx_hal_dcmi.o
objs-hw-$(CONFIG_STM32H7XX_HAL_DFSDM)            += stm32h7xx_hal_dfsdm.o
objs-hw-$(CONFIG_STM32H7XX_HAL_DFSDM_EX)         += stm32h7xx_hal_dfsdm_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_DMA)              += stm32h7xx_hal_dma.o
objs-hw-$(CONFIG_STM32H7XX_HAL_DMA2D)            += stm32h7xx_hal_dma2d.o
objs-hw-$(CONFIG_STM32H7XX_HAL_DMA_EX)           += stm32h7xx_hal_dma_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_DSI)              += stm32h7xx_hal_dsi.o
objs-hw-$(CONFIG_STM32H7XX_HAL_DTS)              += stm32h7xx_hal_dts.o
objs-hw-$(CONFIG_STM32H7XX_HAL_ETH)              += stm32h7xx_hal_eth.o
objs-hw-$(CONFIG_STM32H7XX_HAL_ETH_EX)           += stm32h7xx_hal_eth_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_EXTI)             += stm32h7xx_hal_exti.o
objs-hw-$(CONFIG_STM32H7XX_HAL_FDCAN)            += stm32h7xx_hal_fdcan.o
objs-hw-$(CONFIG_STM32H7XX_HAL_FLASH)            += stm32h7xx_hal_flash.o
objs-hw-$(CONFIG_STM32H7XX_HAL_FLASH_EX)         += stm32h7xx_hal_flash_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_FMAC)             += stm32h7xx_hal_fmac.o
objs-hw-$(CONFIG_STM32H7XX_HAL_GFXMMU)           += stm32h7xx_hal_gfxmmu.o
objs-hw-$(CONFIG_STM32H7XX_HAL_GPIO)             += stm32h7xx_hal_gpio.o
objs-hw-$(CONFIG_STM32H7XX_HAL_HASH)             += stm32h7xx_hal_hash.o
objs-hw-$(CONFIG_STM32H7XX_HAL_HASH_EX)          += stm32h7xx_hal_hash_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_HCD)              += stm32h7xx_hal_hcd.o
objs-hw-$(CONFIG_STM32H7XX_HAL_HRTIM)            += stm32h7xx_hal_hrtim.o
objs-hw-$(CONFIG_STM32H7XX_HAL_HSEM)             += stm32h7xx_hal_hsem.o
objs-hw-$(CONFIG_STM32H7XX_HAL_I2C)              += stm32h7xx_hal_i2c.o
objs-hw-$(CONFIG_STM32H7XX_HAL_I2C_EX)           += stm32h7xx_hal_i2c_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_I2S)              += stm32h7xx_hal_i2s.o
objs-hw-$(CONFIG_STM32H7XX_HAL_I2S_EX)           += stm32h7xx_hal_i2s_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_IRDA)             += stm32h7xx_hal_irda.o
objs-hw-$(CONFIG_STM32H7XX_HAL_IWDG)             += stm32h7xx_hal_iwdg.o
objs-hw-$(CONFIG_STM32H7XX_HAL_JPEG)             += stm32h7xx_hal_jpeg.o
objs-hw-$(CONFIG_STM32H7XX_HAL_LPTIM)            += stm32h7xx_hal_lptim.o
objs-hw-$(CONFIG_STM32H7XX_HAL_LTDC)             += stm32h7xx_hal_ltdc.o
objs-hw-$(CONFIG_STM32H7XX_HAL_LTDC_EX)          += stm32h7xx_hal_ltdc_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_MDIOS)            += stm32h7xx_hal_mdios.o
objs-hw-$(CONFIG_STM32H7XX_HAL_MDMA)             += stm32h7xx_hal_mdma.o
objs-hw-$(CONFIG_STM32H7XX_HAL_MMC)              += stm32h7xx_hal_mmc.o
objs-hw-$(CONFIG_STM32H7XX_HAL_MMC_EX)           += stm32h7xx_hal_mmc_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_NAND)             += stm32h7xx_hal_nand.o
objs-hw-$(CONFIG_STM32H7XX_HAL_NOR)              += stm32h7xx_hal_nor.o
objs-hw-$(CONFIG_STM32H7XX_HAL_OPAMP)            += stm32h7xx_hal_opamp.o
objs-hw-$(CONFIG_STM32H7XX_HAL_OPAMP_EX)         += stm32h7xx_hal_opamp_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_OSPI)             += stm32h7xx_hal_ospi.o
objs-hw-$(CONFIG_STM32H7XX_HAL_OTFDEC)           += stm32h7xx_hal_otfdec.o
objs-hw-$(CONFIG_STM32H7XX_HAL_PCD)              += stm32h7xx_hal_pcd.o
objs-hw-$(CONFIG_STM32H7XX_HAL_PCD_EX)           += stm32h7xx_hal_pcd_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_PSSI)             += stm32h7xx_hal_pssi.o
objs-hw-$(CONFIG_STM32H7XX_HAL_PWR)              += stm32h7xx_hal_pwr.o
objs-hw-$(CONFIG_STM32H7XX_HAL_PWR_EX)           += stm32h7xx_hal_pwr_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_QSPI)             += stm32h7xx_hal_qspi.o
objs-hw-$(CONFIG_STM32H7XX_HAL_RAMECC)           += stm32h7xx_hal_ramecc.o
objs-hw-$(CONFIG_STM32H7XX_HAL_RCC)              += stm32h7xx_hal_rcc.o
objs-hw-$(CONFIG_STM32H7XX_HAL_RCC_EX)           += stm32h7xx_hal_rcc_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_RNG)              += stm32h7xx_hal_rng.o
objs-hw-$(CONFIG_STM32H7XX_HAL_RNG_EX)           += stm32h7xx_hal_rng_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_RTC)              += stm32h7xx_hal_rtc.o
objs-hw-$(CONFIG_STM32H7XX_HAL_RTC_EX)           += stm32h7xx_hal_rtc_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SAI)              += stm32h7xx_hal_sai.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SAI_EX)           += stm32h7xx_hal_sai_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SD)               += stm32h7xx_hal_sd.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SDRAM)            += stm32h7xx_hal_sdram.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SD_EX)            += stm32h7xx_hal_sd_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SMARTCARD)        += stm32h7xx_hal_smartcard.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SMARTCARD_EX)     += stm32h7xx_hal_smartcard_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SMBUS)            += stm32h7xx_hal_smbus.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SMBUS_EX)         += stm32h7xx_hal_smbus_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SPDIFRX)          += stm32h7xx_hal_spdifrx.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SPI)              += stm32h7xx_hal_spi.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SPI_EX)           += stm32h7xx_hal_spi_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SRAM)             += stm32h7xx_hal_sram.o
objs-hw-$(CONFIG_STM32H7XX_HAL_SWPMI)            += stm32h7xx_hal_swpmi.o
objs-hw-$(CONFIG_STM32H7XX_HAL_TIM)              += stm32h7xx_hal_tim.o
objs-hw-$(CONFIG_STM32H7XX_HAL_TIM_EX)           += stm32h7xx_hal_tim_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_UART)             += stm32h7xx_hal_uart.o
objs-hw-$(CONFIG_STM32H7XX_HAL_UART_EX)          += stm32h7xx_hal_uart_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_USART)            += stm32h7xx_hal_usart.o
objs-hw-$(CONFIG_STM32H7XX_HAL_USART_EX)         += stm32h7xx_hal_usart_ex.o
objs-hw-$(CONFIG_STM32H7XX_HAL_WWDG)             += stm32h7xx_hal_wwdg.o

objs-hw-$(CONFIG_STM32H7XX_LL_ADC)               += stm32h7xx_ll_adc.o
objs-hw-$(CONFIG_STM32H7XX_LL_BDMA)              += stm32h7xx_ll_bdma.o
objs-hw-$(CONFIG_STM32H7XX_LL_COMP)              += stm32h7xx_ll_comp.o
objs-hw-$(CONFIG_STM32H7XX_LL_CORDIC)            += stm32h7xx_ll_cordic.o
objs-hw-$(CONFIG_STM32H7XX_LL_CRC)               += stm32h7xx_ll_crc.o
objs-hw-$(CONFIG_STM32H7XX_LL_CRS)               += stm32h7xx_ll_crs.o
objs-hw-$(CONFIG_STM32H7XX_LL_DAC)               += stm32h7xx_ll_dac.o
objs-hw-$(CONFIG_STM32H7XX_LL_DELAYBLOCK)        += stm32h7xx_ll_delayblock.o
objs-hw-$(CONFIG_STM32H7XX_LL_DMA)               += stm32h7xx_ll_dma.o
objs-hw-$(CONFIG_STM32H7XX_LL_DMA2D)             += stm32h7xx_ll_dma2d.o
objs-hw-$(CONFIG_STM32H7XX_LL_EXTI)              += stm32h7xx_ll_exti.o
objs-hw-$(CONFIG_STM32H7XX_LL_FMAC)              += stm32h7xx_ll_fmac.o
objs-hw-$(CONFIG_STM32H7XX_LL_FMC)               += stm32h7xx_ll_fmc.o
objs-hw-$(CONFIG_STM32H7XX_LL_GPIO)              += stm32h7xx_ll_gpio.o
objs-hw-$(CONFIG_STM32H7XX_LL_HRTIM)             += stm32h7xx_ll_hrtim.o
objs-hw-$(CONFIG_STM32H7XX_LL_I2C)               += stm32h7xx_ll_i2c.o
objs-hw-$(CONFIG_STM32H7XX_LL_LPTIM)             += stm32h7xx_ll_lptim.o
objs-hw-$(CONFIG_STM32H7XX_LL_LPUART)            += stm32h7xx_ll_lpuart.o
objs-hw-$(CONFIG_STM32H7XX_LL_MDMA)              += stm32h7xx_ll_mdma.o
objs-hw-$(CONFIG_STM32H7XX_LL_OPAMP)             += stm32h7xx_ll_opamp.o
objs-hw-$(CONFIG_STM32H7XX_LL_PWR)               += stm32h7xx_ll_pwr.o
objs-hw-$(CONFIG_STM32H7XX_LL_RCC)               += stm32h7xx_ll_rcc.o
objs-hw-$(CONFIG_STM32H7XX_LL_RNG)               += stm32h7xx_ll_rng.o
objs-hw-$(CONFIG_STM32H7XX_LL_RTC)               += stm32h7xx_ll_rtc.o
objs-hw-$(CONFIG_STM32H7XX_LL_SDMMC)             += stm32h7xx_ll_sdmmc.o
objs-hw-$(CONFIG_STM32H7XX_LL_SPI)               += stm32h7xx_ll_spi.o
objs-hw-$(CONFIG_STM32H7XX_LL_SWPMI)             += stm32h7xx_ll_swpmi.o
objs-hw-$(CONFIG_STM32H7XX_LL_TIM)               += stm32h7xx_ll_tim.o
objs-hw-$(CONFIG_STM32H7XX_LL_USART)             += stm32h7xx_ll_usart.o
objs-hw-$(CONFIG_STM32H7XX_LL_USB)               += stm32h7xx_ll_usb.o
objs-hw-$(CONFIG_STM32H7XX_LL_UTILS)             += stm32h7xx_ll_utils.o
