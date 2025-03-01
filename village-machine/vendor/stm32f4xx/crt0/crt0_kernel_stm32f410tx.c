//###########################################################################
// crt0_kernel_stm32f410tx.c
// Low level file that manages kernel entry
//
// $Copyright: Copyright (C) village
//###########################################################################
#include <stddef.h>
#include <stdint.h>

/// @brief _estack
extern void *_estack;


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
void PVD_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
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
void EXTI9_5_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_UP_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_CC_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void I2C1_EV_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void I2C1_ER_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void I2C2_EV_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void I2C2_ER_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void SPI1_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void USART1_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void USART2_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void EXTI15_10_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void RTC_Alarm_IRQHandler()              __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Stream7_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void TIM5_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void TIM6_DAC_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream0_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream1_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream2_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream3_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream4_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream5_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream6_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Stream7_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void RNG_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void FPU_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void FMPI2C1_EV_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void FMPI2C1_ER_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void LPTIM1_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));


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
	&WWDG_IRQHandler,                   /* Window WatchDog                             */
	&PVD_IRQHandler,                    /* PVD through EXTI Line detection             */
	&TAMP_STAMP_IRQHandler,             /* Tamper and TimeStamps through the EXTI line */
	&RTC_WKUP_IRQHandler,               /* RTC Wakeup through the EXTI line            */
	&FLASH_IRQHandler,                  /* FLASH                                       */
	&RCC_IRQHandler,                    /* RCC                                         */
	&EXTI0_IRQHandler,                  /* EXTI Line0                                  */
	&EXTI1_IRQHandler,                  /* EXTI Line1                                  */
	&EXTI2_IRQHandler,                  /* EXTI Line2                                  */
	&EXTI3_IRQHandler,                  /* EXTI Line3                                  */
	&EXTI4_IRQHandler,                  /* EXTI Line4                                  */
	&DMA1_Stream0_IRQHandler,           /* DMA1 Stream 0                               */
	&DMA1_Stream1_IRQHandler,           /* DMA1 Stream 1                               */
	&DMA1_Stream2_IRQHandler,           /* DMA1 Stream 2                               */
	&DMA1_Stream3_IRQHandler,           /* DMA1 Stream 3                               */
	&DMA1_Stream4_IRQHandler,           /* DMA1 Stream 4                               */
	&DMA1_Stream5_IRQHandler,           /* DMA1 Stream 5                               */
	&DMA1_Stream6_IRQHandler,           /* DMA1 Stream 6                               */
	&ADC_IRQHandler,                    /* ADC1, ADC2 and ADC3s                        */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	&EXTI9_5_IRQHandler,                /* External Line[9:5]s                         */
	&TIM1_BRK_TIM9_IRQHandler,          /* TIM1 Break and TIM9                         */
	&TIM1_UP_IRQHandler,                /* TIM1 Update                                 */
	&TIM1_TRG_COM_TIM11_IRQHandler,     /* TIM1 Trigger and Commutation and TIM11      */
	&TIM1_CC_IRQHandler,                /* TIM1 Capture Compare                        */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	&I2C1_EV_IRQHandler,                /* I2C1 Event                                  */
	&I2C1_ER_IRQHandler,                /* I2C1 Error                                  */
	&I2C2_EV_IRQHandler,                /* I2C2 Event                                  */
	&I2C2_ER_IRQHandler,                /* I2C2 Error                                  */
	&SPI1_IRQHandler,                   /* SPI1                                        */
	0,                                  /* Reserved                                    */
	&USART1_IRQHandler,                 /* USART1                                      */
	&USART2_IRQHandler,                 /* USART2                                      */
	0,                                  /* Reserved                                    */
	&EXTI15_10_IRQHandler,              /* External Line[15:10]s                       */
	&RTC_Alarm_IRQHandler,              /* RTC Alarm (A and B) through EXTI Line       */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	&DMA1_Stream7_IRQHandler,           /* DMA1 Stream7                                */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	&TIM5_IRQHandler,                   /* TIM5                                        */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	&TIM6_DAC_IRQHandler,               /* TIM6 and DAC                                */
	0,                                  /* Reserved                                    */
	&DMA2_Stream0_IRQHandler,           /* DMA2 Stream 0                               */
	&DMA2_Stream1_IRQHandler,           /* DMA2 Stream 1                               */
	&DMA2_Stream2_IRQHandler,           /* DMA2 Stream 2                               */
	&DMA2_Stream3_IRQHandler,           /* DMA2 Stream 3                               */
	&DMA2_Stream4_IRQHandler,           /* DMA2 Stream 4                               */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	&DMA2_Stream5_IRQHandler,           /* DMA2 Stream 5                               */
	&DMA2_Stream6_IRQHandler,           /* DMA2 Stream 6                               */
	&DMA2_Stream7_IRQHandler,           /* DMA2 Stream 7                               */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	&RNG_IRQHandler,                    /* RNG                                         */
	&FPU_IRQHandler,                    /* FPU                                         */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	0,                                  /* Reserved                                    */
	&FMPI2C1_EV_IRQHandler,             /* FMPI2C1 Event                               */
	&FMPI2C1_ER_IRQHandler,             /* FMPI2C1 Error                               */
	&LPTIM1_IRQHandler,                 /* LP TIM1                                     */
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

	SystemInit();

	__preinit_arrary();

	__init_array();

	main(argc, argv);

	__fini_array();

	for(;;) ;
}
