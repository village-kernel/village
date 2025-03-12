//###########################################################################
// crt0_kernel_stm32h745xg.c
// Low level file that manages kernel entry
//
// $Copyright: Copyright (C) village
//###########################################################################
#include <stddef.h>
#include <stdint.h>

/// @brief _estack
extern void *_estack;


/// @brief KernelSymbol
void KernelSymbol();


/// @brief SystemInit
void SystemInit();


/// @brief program entry main
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char* argv[]);


/// @brief Reset_Handler
/// @param argc 
/// @param argv 
void Reset_Handler(int argc, char* argv[]);


/// @brief Default_Handler
void __attribute__ ((weak, naked)) Default_Handler()
{
	while (1) {}
}


/// @brief Default Handlers
void NMI_Handler()                       __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()                 __attribute__ ((weak, alias ("Default_Handler")));
void MemManage_Handler()                 __attribute__ ((weak, alias ("Default_Handler")));
void BusFault_Handler()                  __attribute__ ((weak, alias ("Default_Handler")));
void UsageFault_Handler()                __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()                       __attribute__ ((weak, alias ("Default_Handler")));
void DebugMon_Handler()                  __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()                    __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()                   __attribute__ ((weak, alias ("Default_Handler")));
void WWDG_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void PVD_AVD_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void TAMP_STAMP_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void RTC_WKUP_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void FLASH_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void RCC_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void EXTI0_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void EXTI1_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void EXTI2_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void EXTI3_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void EXTI4_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Stream0_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Stream1_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Stream2_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Stream3_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Stream4_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Stream5_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Stream6_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void ADC_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void FDCAN1_IT0_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void FDCAN2_IT0_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void FDCAN1_IT1_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void FDCAN2_IT1_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void EXTI9_5_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_BRK_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_UP_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_TRG_COM_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_CC_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void TIM2_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void TIM3_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void TIM4_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void I2C1_EV_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void I2C1_ER_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void I2C2_EV_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void I2C2_ER_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void SPI1_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void SPI2_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void USART1_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void USART2_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void USART3_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void EXTI15_10_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void RTC_Alarm_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void TIM8_BRK_TIM12_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void TIM8_UP_TIM13_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void TIM8_TRG_COM_TIM14_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void TIM8_CC_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Stream7_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void FMC_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void SDMMC1_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void TIM5_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void SPI3_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void UART4_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void UART5_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void TIM6_DAC_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void TIM7_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream0_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream1_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream2_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream3_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream4_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void ETH_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void ETH_WKUP_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void FDCAN_CAL_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void CM7_SEV_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void CM4_SEV_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream5_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream6_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream7_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void USART6_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void I2C3_EV_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void I2C3_ER_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void OTG_HS_EP1_OUT_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void OTG_HS_EP1_IN_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void OTG_HS_WKUP_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void OTG_HS_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void DCMI_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void RNG_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void FPU_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void UART7_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void UART8_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void SPI4_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void SPI5_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void SPI6_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void SAI1_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void LTDC_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void LTDC_ER_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void DMA2D_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void SAI2_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void QUADSPI_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void LPTIM1_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void CEC_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void I2C4_EV_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void I2C4_ER_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void SPDIF_RX_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void OTG_FS_EP1_OUT_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void OTG_FS_EP1_IN_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void OTG_FS_WKUP_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void OTG_FS_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void DMAMUX1_OVR_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void HRTIM1_Master_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void HRTIM1_TIMA_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void HRTIM1_TIMB_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void HRTIM1_TIMC_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void HRTIM1_TIMD_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void HRTIM1_TIME_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void HRTIM1_FLT_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void DFSDM1_FLT0_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void DFSDM1_FLT1_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void DFSDM1_FLT2_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void DFSDM1_FLT3_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void SAI3_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void SWPMI1_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void TIM15_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void TIM16_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void TIM17_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void MDIOS_WKUP_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void MDIOS_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void JPEG_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void MDMA_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void SDMMC2_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void HSEM1_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void HSEM2_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void ADC3_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void DMAMUX2_OVR_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void BDMA_Channel0_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void BDMA_Channel1_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void BDMA_Channel2_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void BDMA_Channel3_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void BDMA_Channel4_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void BDMA_Channel5_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void BDMA_Channel6_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void BDMA_Channel7_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void COMP1_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void LPTIM2_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void LPTIM3_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void LPTIM4_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void LPTIM5_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void LPUART1_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void WWDG_RST_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void CRS_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void ECC_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void SAI4_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void HOLD_CORE_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void WAKEUP_PIN_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));


/// @brief isr_vector
void * g_pfnVectors[] __attribute__ ((section (".isr_vector"), used)) = 
{
	&_estack,
	&Reset_Handler,
	&NMI_Handler,
	&HardFault_Handler,
	&MemManage_Handler,
	&BusFault_Handler,
	&UsageFault_Handler,
	0,
	0,
	0,
	0,
	&SVC_Handler,
	&DebugMon_Handler,
	0,
	&PendSV_Handler,
	&SysTick_Handler,
	&WWDG_IRQHandler,                   /* Window WatchDog Interrupt ( wwdg1_it, wwdg2_it) */
	&PVD_AVD_IRQHandler,                /* PVD/AVD through EXTI Line detection */
	&TAMP_STAMP_IRQHandler,             /* Tamper and TimeStamps through the EXTI line */
	&RTC_WKUP_IRQHandler,               /* RTC Wakeup through the EXTI line */
	&FLASH_IRQHandler,                  /* FLASH                        */
	&RCC_IRQHandler,                    /* RCC                          */
	&EXTI0_IRQHandler,                  /* EXTI Line0                   */
	&EXTI1_IRQHandler,                  /* EXTI Line1                   */
	&EXTI2_IRQHandler,                  /* EXTI Line2                   */
	&EXTI3_IRQHandler,                  /* EXTI Line3                   */
	&EXTI4_IRQHandler,                  /* EXTI Line4                   */
	&DMA1_Stream0_IRQHandler,           /* DMA1 Stream 0                */
	&DMA1_Stream1_IRQHandler,           /* DMA1 Stream 1                */
	&DMA1_Stream2_IRQHandler,           /* DMA1 Stream 2                */
	&DMA1_Stream3_IRQHandler,           /* DMA1 Stream 3                */
	&DMA1_Stream4_IRQHandler,           /* DMA1 Stream 4                */
	&DMA1_Stream5_IRQHandler,           /* DMA1 Stream 5                */
	&DMA1_Stream6_IRQHandler,           /* DMA1 Stream 6                */
	&ADC_IRQHandler,                    /* ADC1, ADC2 and ADC3s         */
	&FDCAN1_IT0_IRQHandler,             /* FDCAN1 interrupt line 0      */
	&FDCAN2_IT0_IRQHandler,             /* FDCAN2 interrupt line 0      */
	&FDCAN1_IT1_IRQHandler,             /* FDCAN1 interrupt line 1      */
	&FDCAN2_IT1_IRQHandler,             /* FDCAN2 interrupt line 1      */
	&EXTI9_5_IRQHandler,                /* External Line[9:5]s          */
	&TIM1_BRK_IRQHandler,               /* TIM1 Break interrupt         */
	&TIM1_UP_IRQHandler,                /* TIM1 Update interrupt        */
	&TIM1_TRG_COM_IRQHandler,           /* TIM1 Trigger and Commutation interrupt */
	&TIM1_CC_IRQHandler,                /* TIM1 Capture Compare         */
	&TIM2_IRQHandler,                   /* TIM2                         */
	&TIM3_IRQHandler,                   /* TIM3                         */
	&TIM4_IRQHandler,                   /* TIM4                         */
	&I2C1_EV_IRQHandler,                /* I2C1 Event                   */
	&I2C1_ER_IRQHandler,                /* I2C1 Error                   */
	&I2C2_EV_IRQHandler,                /* I2C2 Event                   */
	&I2C2_ER_IRQHandler,                /* I2C2 Error                   */
	&SPI1_IRQHandler,                   /* SPI1                         */
	&SPI2_IRQHandler,                   /* SPI2                         */
	&USART1_IRQHandler,                 /* USART1                       */
	&USART2_IRQHandler,                 /* USART2                       */
	&USART3_IRQHandler,                 /* USART3                       */
	&EXTI15_10_IRQHandler,              /* External Line[15:10]s        */
	&RTC_Alarm_IRQHandler,              /* RTC Alarm (A and B) through EXTI Line */
	0,                                  /* Reserved                     */
	&TIM8_BRK_TIM12_IRQHandler,         /* TIM8 Break and TIM12         */
	&TIM8_UP_TIM13_IRQHandler,          /* TIM8 Update and TIM13        */
	&TIM8_TRG_COM_TIM14_IRQHandler,     /* TIM8 Trigger and Commutation and TIM14 */
	&TIM8_CC_IRQHandler,                /* TIM8 Capture Compare         */
	&DMA1_Stream7_IRQHandler,           /* DMA1 Stream7                 */
	&FMC_IRQHandler,                    /* FMC                          */
	&SDMMC1_IRQHandler,                 /* SDMMC1                       */
	&TIM5_IRQHandler,                   /* TIM5                         */
	&SPI3_IRQHandler,                   /* SPI3                         */
	&UART4_IRQHandler,                  /* UART4                        */
	&UART5_IRQHandler,                  /* UART5                        */
	&TIM6_DAC_IRQHandler,               /* TIM6 and DAC1&2 underrun errors */
	&TIM7_IRQHandler,                   /* TIM7                         */
	&DMA2_Stream0_IRQHandler,           /* DMA2 Stream 0                */
	&DMA2_Stream1_IRQHandler,           /* DMA2 Stream 1                */
	&DMA2_Stream2_IRQHandler,           /* DMA2 Stream 2                */
	&DMA2_Stream3_IRQHandler,           /* DMA2 Stream 3                */
	&DMA2_Stream4_IRQHandler,           /* DMA2 Stream 4                */
	&ETH_IRQHandler,                    /* Ethernet                     */
	&ETH_WKUP_IRQHandler,               /* Ethernet Wakeup through EXTI line */
	&FDCAN_CAL_IRQHandler,              /* FDCAN calibration unit interrupt  */
	&CM7_SEV_IRQHandler,                /* CM7 Send event interrupt for CM4  */
	&CM4_SEV_IRQHandler,                /* CM4 Send event interrupt for CM7  */
	0,                                  /* Reserved                     */
	0,                                  /* Reserved                     */
	&DMA2_Stream5_IRQHandler,           /* DMA2 Stream 5                */
	&DMA2_Stream6_IRQHandler,           /* DMA2 Stream 6                */
	&DMA2_Stream7_IRQHandler,           /* DMA2 Stream 7                */
	&USART6_IRQHandler,                 /* USART6                       */
	&I2C3_EV_IRQHandler,                /* I2C3 event                   */
	&I2C3_ER_IRQHandler,                /* I2C3 error                   */
	&OTG_HS_EP1_OUT_IRQHandler,         /* USB OTG HS End Point 1 Out   */
	&OTG_HS_EP1_IN_IRQHandler,          /* USB OTG HS End Point 1 In    */
	&OTG_HS_WKUP_IRQHandler,            /* USB OTG HS Wakeup through EXTI */
	&OTG_HS_IRQHandler,                 /* USB OTG HS                   */
	&DCMI_IRQHandler,                   /* DCMI                         */
	0,                                  /* Reserved                     */
	&RNG_IRQHandler,                    /* Rng                          */
	&FPU_IRQHandler,                    /* FPU                          */
	&UART7_IRQHandler,                  /* UART7                        */
	&UART8_IRQHandler,                  /* UART8                        */
	&SPI4_IRQHandler,                   /* SPI4                         */
	&SPI5_IRQHandler,                   /* SPI5                         */
	&SPI6_IRQHandler,                   /* SPI6                         */
	&SAI1_IRQHandler,                   /* SAI1                         */
	&LTDC_IRQHandler,                   /* LTDC                         */
	&LTDC_ER_IRQHandler,                /* LTDC error                   */
	&DMA2D_IRQHandler,                  /* DMA2D                        */
	&SAI2_IRQHandler,                   /* SAI2                         */
	&QUADSPI_IRQHandler,                /* QUADSPI                      */
	&LPTIM1_IRQHandler,                 /* LPTIM1                       */
	&CEC_IRQHandler,                    /* HDMI_CEC                     */
	&I2C4_EV_IRQHandler,                /* I2C4 Event                   */
	&I2C4_ER_IRQHandler,                /* I2C4 Error                   */
	&SPDIF_RX_IRQHandler,               /* SPDIF_RX                     */
	&OTG_FS_EP1_OUT_IRQHandler,         /* USB OTG FS End Point 1 Out   */
	&OTG_FS_EP1_IN_IRQHandler,          /* USB OTG FS End Point 1 In    */
	&OTG_FS_WKUP_IRQHandler,            /* USB OTG FS Wakeup through EXTI */
	&OTG_FS_IRQHandler,                 /* USB OTG FS                   */
	&DMAMUX1_OVR_IRQHandler,            /* DMAMUX1 Overrun interrupt    */
	&HRTIM1_Master_IRQHandler,          /* HRTIM Master Timer global Interrupt */
	&HRTIM1_TIMA_IRQHandler,            /* HRTIM Timer A global Interrupt */
	&HRTIM1_TIMB_IRQHandler,            /* HRTIM Timer B global Interrupt */
	&HRTIM1_TIMC_IRQHandler,            /* HRTIM Timer C global Interrupt */
	&HRTIM1_TIMD_IRQHandler,            /* HRTIM Timer D global Interrupt */
	&HRTIM1_TIME_IRQHandler,            /* HRTIM Timer E global Interrupt */
	&HRTIM1_FLT_IRQHandler,             /* HRTIM Fault global Interrupt   */
	&DFSDM1_FLT0_IRQHandler,            /* DFSDM Filter0 Interrupt        */
	&DFSDM1_FLT1_IRQHandler,            /* DFSDM Filter1 Interrupt        */
	&DFSDM1_FLT2_IRQHandler,            /* DFSDM Filter2 Interrupt        */
	&DFSDM1_FLT3_IRQHandler,            /* DFSDM Filter3 Interrupt        */
	&SAI3_IRQHandler,                   /* SAI3 global Interrupt          */
	&SWPMI1_IRQHandler,                 /* Serial Wire Interface 1 global interrupt */
	&TIM15_IRQHandler,                  /* TIM15 global Interrupt      */
	&TIM16_IRQHandler,                  /* TIM16 global Interrupt      */
	&TIM17_IRQHandler,                  /* TIM17 global Interrupt      */
	&MDIOS_WKUP_IRQHandler,             /* MDIOS Wakeup  Interrupt     */
	&MDIOS_IRQHandler,                  /* MDIOS global Interrupt      */
	&JPEG_IRQHandler,                   /* JPEG global Interrupt       */
	&MDMA_IRQHandler,                   /* MDMA global Interrupt       */
	0,                                  /* Reserved                   */
	&SDMMC2_IRQHandler,                 /* SDMMC2 global Interrupt     */
	&HSEM1_IRQHandler,                  /* HSEM1 global Interrupt      */
	&HSEM2_IRQHandler,                  /* HSEM1 global Interrupt      */
	&ADC3_IRQHandler,                   /* ADC3 global Interrupt       */
	&DMAMUX2_OVR_IRQHandler,            /* DMAMUX Overrun interrupt    */
	&BDMA_Channel0_IRQHandler,          /* BDMA Channel 0 global Interrupt */
	&BDMA_Channel1_IRQHandler,          /* BDMA Channel 1 global Interrupt */
	&BDMA_Channel2_IRQHandler,          /* BDMA Channel 2 global Interrupt */
	&BDMA_Channel3_IRQHandler,          /* BDMA Channel 3 global Interrupt */
	&BDMA_Channel4_IRQHandler,          /* BDMA Channel 4 global Interrupt */
	&BDMA_Channel5_IRQHandler,          /* BDMA Channel 5 global Interrupt */
	&BDMA_Channel6_IRQHandler,          /* BDMA Channel 6 global Interrupt */
	&BDMA_Channel7_IRQHandler,          /* BDMA Channel 7 global Interrupt */
	&COMP1_IRQHandler,                  /* COMP1 global Interrupt     */
	&LPTIM2_IRQHandler,                 /* LP TIM2 global interrupt   */
	&LPTIM3_IRQHandler,                 /* LP TIM3 global interrupt   */
	&LPTIM4_IRQHandler,                 /* LP TIM4 global interrupt   */
	&LPTIM5_IRQHandler,                 /* LP TIM5 global interrupt   */
	&LPUART1_IRQHandler,                /* LP UART1 interrupt         */
	&WWDG_RST_IRQHandler,               /* Window Watchdog reset interrupt (exti_d2_wwdg_it, exti_d1_wwdg_it) */
	&CRS_IRQHandler,                    /* Clock Recovery Global Interrupt */
	&ECC_IRQHandler,                    /* ECC diagnostic Global Interrupt */
	&SAI4_IRQHandler,                   /* SAI4 global interrupt      */
	0,                                  /* Reserved                   */
	&HOLD_CORE_IRQHandler,              /* Hold core interrupt        */
	&WAKEUP_PIN_IRQHandler,             /* Interrupt for all 6 wake-up pins */
};


/// @brief Initialize data and bss section
/// @param  
void __init_data_bss(void)
{
	extern void *_sidata, *_sdata, *_edata;
	extern void *_sbss,   *_ebss;
	void **pSource, **pDest;

	//Normally the CPU should will setup the based on the value from the first entry in the vector table.
	//If you encounter problems with accessing stack variables during initialization, ensure the line below is enabled.
	asm ("ldr sp, =_estack");

	//Copy data segment initializers from disk to SRAM
	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	//Zero fill the bss segment.
	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;
}


/// @brief execute preinit_arrary
/// @param  
void __preinit_arrary(void)
{
	extern void (*__preinit_array_start []) (void);
	extern void (*__preinit_array_end   []) (void);

	int count = __preinit_array_end - __preinit_array_start;
	for (int i = 0; i < count; i++)
		__preinit_array_start[i]();
}


/// @brief execute init_arrary
/// @param  
void __init_array(void)
{
	extern void (*__init_array_start []) (void);
	extern void (*__init_array_end   []) (void);

	int count = __init_array_end - __init_array_start;
	for (int i = 0; i < count; i++)
		__init_array_start[i]();
}


/// @brief execute fini_arrary
/// @param  
void __fini_array(void)
{
	extern void (*__fini_array_start []) (void);
	extern void (*__fini_array_end   []) (void);

	int count = __fini_array_end - __fini_array_start;

	for (int i = 0; i < count; i++)
	{
		__fini_array_start[i]();
	}
}


/// @brief Reset_Handler
/// @param  
void Reset_Handler(int argc, char* argv[])
{
	__init_data_bss();

    KernelSymbol();

	SystemInit();

	__preinit_arrary();

	__init_array();

	main(argc, argv);

	__fini_array();

	for(;;) ;
}
