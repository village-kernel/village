//###########################################################################
// vk_system.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_system.h"
#include "vk_kernel.h"
#include "vk_hardware.h"


/// @brief Constructor
ConcreteSystem::ConcreteSystem()
    :sysTicks(0),
    cyclesInMicro(0)
{}


/// @brief Destructor
ConcreteSystem::~ConcreteSystem()
{
}


/// @brief System Setup
void ConcreteSystem::Setup()
{
    //Set interrupt handler
    kernel->interrupt.SetISR(SysTick_IRQn, (Method)&ConcreteSystem::SysTickHandler, this);

    //Config clock
    ConfigCoreDebug();
    ConfigureMPU();
    ConfigurePower();
    ConfigSysTick();
    ConfigureFor25MhzXtal();
}


/// @brief System Exit
void ConcreteSystem::Exit()
{
    kernel->interrupt.RemoveISR(SysTick_IRQn, (Method)&ConcreteSystem::SysTickHandler, this);
}


/// @brief Configure core debug
void ConcreteSystem::ConfigCoreDebug()
{
    //Enable Data Watchpoint and Trace unit and turn on its main counter
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}


/// @brief Config system tick
void ConcreteSystem::ConfigSysTick()
{
    //Select Systick clock source: SYSCLK_MHZ/8 = 480/8 = 60M
    SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;

    //Enable systick interrupt
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

    //Set systick reload value
    SysTick->LOAD = 60000;

    //Clear systick current value
    SysTick->VAL = 0;

    //Enable systick
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    //Calculate the cyclesInMicro variable
    cyclesInMicro = SystemCoreClock / microsInSec;
}


/// @brief Configure memory protection unit
void ConcreteSystem::ConfigureMPU()
{
    //Make sure outstanding transfers are done
    __DMB();

    //Disable fault exceptions
    SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;

    //Disable the MPU and clear the control register
    MPU->CTRL = 0;

    //Config Address: SRAM = 0x24000000
    MPU->RBAR = 0x24000000;
    
    //region: Instruction fetches enabled, full access, shareable, 512K size.
    //        Outer and inner write-through, No write allocate.
    //        Corresponding sub-region is enabled.
    MPU->RASR = ((uint32_t)0x00 << MPU_RASR_XN_Pos)    |
                ((uint32_t)0x03 << MPU_RASR_AP_Pos)    |
                ((uint32_t)0x00 << MPU_RASR_TEX_Pos)   |
                ((uint32_t)0x01 << MPU_RASR_C_Pos)     |
                ((uint32_t)0x00 << MPU_RASR_B_Pos)     |
                ((uint32_t)0x01 << MPU_RASR_S_Pos)     |
                ((uint32_t)0x00 << MPU_RASR_SRD_Pos)   |
                ((uint32_t)0x12 << MPU_RASR_SIZE_Pos)  |
                ((uint32_t)0x01 << MPU_RASR_ENABLE_Pos);

    //Enable the MPU
    MPU->CTRL = MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_ENABLE_Msk;

    //Enable fault exceptions
    SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;

    //Ensure MPU setting take effects
    __DSB();
    __ISB();

    //Enable data cache
    SCB_EnableDCache();

    //Enable instruction cache
    //SCB_EnableICache();
}


/// @brief Configure the main internal regulator output voltage
void ConcreteSystem::ConfigurePower()
{
    //Supply configuration update enable
    PWR->CR3 = (PWR->CR3 & ~(PWR_CR3_SCUEN | PWR_CR3_LDOEN | PWR_CR3_BYPASS)) | PWR_CR3_LDOEN;

    //Wait till voltage level flag is set
    while (!(PWR->CSR1 & PWR_CSR1_ACTVOSRDY)) {}

    //Setting the voltage scaling
    PWR->D3CR = (PWR->D3CR & ~PWR_D3CR_VOS) | PWR_D3CR_VOS_1;

    //Delay after setting the voltage scaling
    __attribute__((unused)) uint32_t tmpreg1 = PWR->D3CR & PWR_D3CR_VOS;

    //Setting the syscfg boost setting
    SYSCFG->PWRCR = (SYSCFG->PWRCR & ~SYSCFG_PWRCR_ODEN) | SYSCFG_PWRCR_ODEN;

    //Delay after setting the syscfg boost setting
    __attribute__((unused)) uint32_t tmpreg2 = SYSCFG->PWRCR & SYSCFG_PWRCR_ODEN;

    //Voltage scaling output selection ready
    while (!(PWR->D3CR & PWR_D3CR_VOSRDY)) {}
}


/// @brief Configures the system to use an hsi crystal as clock source.
/// @brief PLL1: 480Mhz, PLL2 = 84Mhz, System Clock = PLL1.
void ConcreteSystem::ConfigureForHsi()
{
    //Reset CFGR register
    RCC->CFGR = 0x00000000;

    //Configure HSI clock divider 1
    RCC->CR = (RCC->CR & ~(RCC_CR_HSIDIV | RCC_CR_HSION)) | (RCC_CR_HSIDIV_1 | RCC_CR_HSION);

    //Wait till HSI is ready
    while (!(RCC->CR & RCC_CR_HSIRDY)) {}

    //Enable the Internal Low Speed oscillator (HSI48)
    RCC->CR = (RCC->CR & ~RCC_CR_HSI48ON) | RCC_CR_HSI48ON;

    //Wait till HSI48 is ready
    while (!(RCC->CR & RCC_CR_HSI48RDY)) {}

    //Disable main PLL
    RCC->CR &= ~RCC_CR_PLL1ON;
    while (RCC->CR & RCC_CR_PLL1RDY) {}

    //Configure main PLL clock source
    RCC->PLLCKSELR &= ~RCC_PLLCKSELR_PLLSRC_Msk;
    RCC->PLLCKSELR |= RCC_PLLCKSELR_PLLSRC_HSI;

    //Configure main PLL multiplication factor
    RCC->PLLCKSELR &= ~RCC_PLLCKSELR_DIVM1_Msk;
    RCC->PLLCKSELR |= 4 << RCC_PLLCKSELR_DIVM1_Pos;

    //Configure main PLL division factor
    RCC->PLL1DIVR = ((60U - 1U) << RCC_PLL1DIVR_N1_Pos) |
                    (( 2U - 1U) << RCC_PLL1DIVR_P1_Pos) |
                    (( 2U - 1U) << RCC_PLL1DIVR_Q1_Pos) |
                    (( 2U - 1U) << RCC_PLL1DIVR_R1_Pos);

    //Configure PLL PLL1FRACN
    RCC->PLL1FRACR = (RCC->PLL1FRACR & ~RCC_PLL1FRACR_FRACN1_Msk);

    //Select PLL1 input reference frequency range: VCI
    RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLL1RGE_Msk) | RCC_PLLCFGR_PLL1RGE_3;

    //Select PLL1 output frequency range : VCO
    RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLL1VCOSEL_Msk);

    //Enable PLL System, PLL1Q, PLL1R and PLL1FRACN Clock output
    RCC->PLLCFGR |= RCC_PLLCFGR_DIVP1EN | RCC_PLLCFGR_DIVQ1EN | RCC_PLLCFGR_DIVR1EN | RCC_PLLCFGR_PLL1FRACEN;

    //Enable main PLL
    RCC->CR |= RCC_CR_PLL1ON;
    while (!(RCC->CR & RCC_CR_PLL1RDY)) {}

    //Disable PLL2
    RCC->CR &= ~RCC_CR_PLL2ON;
    while (RCC->CR & RCC_CR_PLL2RDY) {}

    //Configure PLL2 multiplication factor
    RCC->PLLCKSELR &= ~RCC_PLLCKSELR_DIVM2_Msk;
    RCC->PLLCKSELR |= 4 << RCC_PLLCKSELR_DIVM2_Pos;

    //Configure PLL2 division factor
    RCC->PLL2DIVR = ((21U - 1U) << RCC_PLL2DIVR_N2_Pos) |
                    (( 4U - 1U) << RCC_PLL2DIVR_P2_Pos) |
                    (( 2U - 1U) << RCC_PLL2DIVR_Q2_Pos) |
                    (( 2U - 1U) << RCC_PLL2DIVR_R2_Pos);

    //Configure PLL PLL2FRACN
    RCC->PLL2FRACR = (RCC->PLL2FRACR & ~RCC_PLL2FRACR_FRACN2_Msk);

    //Select PLL2 input reference frequency range: VCI
    RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLL2RGE_Msk) | RCC_PLLCFGR_PLL2RGE_3;

    //Select PLL2 output frequency range : VCO
    RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLL2VCOSEL_Msk);

    //Enable PLL System, PLL1Q, PLL1R and PLL1FRACN Clock output
    RCC->PLLCFGR |= RCC_PLLCFGR_DIVP2EN | RCC_PLLCFGR_DIVQ2EN | RCC_PLLCFGR_DIVR2EN | RCC_PLLCFGR_PLL2FRACEN;

    //Enable main PLL
    RCC->CR |= RCC_CR_PLL2ON;
    while (!(RCC->CR & RCC_CR_PLL2RDY)) {}

    //Increasing the CPU frequency 
    //Program the new number of wait states to the LATENCY bits in the FLASH_ACR register
    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_4WS;

    //Configures the AHB clock (AXI, HCLK3, AHB1, AHB2, AHB4)
    RCC->D1CFGR &= ~RCC_D1CFGR_HPRE_Msk;
    RCC->D1CFGR |= RCC_D1CFGR_HPRE_DIV2;

    //Configures the system core clock
    RCC->D1CFGR &= ~RCC_D1CFGR_D1CPRE_Msk;
    RCC->D1CFGR |= RCC_D1CFGR_D1CPRE_DIV1;

    //Switch SYSCLK source to the PLL
    RCC->CFGR = (RCC_CFGR_SW & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL1;
    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL1)) {}

    //Decreasing the number of wait states because of lower CPU frequency
    //Program the new number of wait states to the LATENCY bits in the FLASH_ACR register
    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_4WS;

    //Configures the High Speed APB clock (APB3)
    RCC->D1CFGR = (RCC->D1CFGR & ~RCC_D1CFGR_D1PPRE) | RCC_D1CFGR_D1PPRE_DIV2;

    //Configures the High Speed APB clock (APB1)
    RCC->D2CFGR = (RCC->D2CFGR & ~RCC_D2CFGR_D2PPRE1) | RCC_D2CFGR_D2PPRE1_DIV2;

    //Configures the High Speed APB clock (APB2)
    RCC->D2CFGR = (RCC->D2CFGR & ~RCC_D2CFGR_D2PPRE2) | RCC_D2CFGR_D2PPRE2_DIV2;

    //Configures the High Speed APB clock (APB4)
    RCC->D3CFGR = (RCC->D3CFGR & ~RCC_D3CFGR_D3PPRE) | RCC_D3CFGR_D3PPRE_DIV2;

    //Configures hsi_ck as the per_ck source
    RCC->D1CCIPR = (RCC->D1CCIPR & ~RCC_D1CCIPR_CKPERSEL);

    //Update the SystemCoreClock variable
    SystemCoreClockUpdate();

    //Update the cyclesInMicro variable
    cyclesInMicro = SystemCoreClock / microsInSec;
}


/// @brief Configures the system to use an hse crystal as clock source.
/// @brief XTAL: 25Mhz, PLL1: 480Mhz, PLL2 = 480Mhz, PLL3 = 480Mhz, System Clock = PLL1.
void ConcreteSystem::ConfigureFor25MhzXtal()
{
    //Reset CFGR register
    RCC->CFGR = 0x00000000;

    //Enable the HSE
    RCC->CR = (RCC->CR & ~RCC_CR_HSEON) | RCC_CR_HSEON;

    //Wait till HSE is ready
    while (!(RCC->CR & RCC_CR_HSEON)) {}

    //Enable the Internal Low Speed oscillator (HSI48)
    RCC->CR = (RCC->CR & ~RCC_CR_HSI48ON) | RCC_CR_HSI48ON;

    //Wait till HSI48 is ready
    while (!(RCC->CR & RCC_CR_HSI48RDY)) {}

    //Configure PLL1
    {
        //Disable PLL1
        RCC->CR &= ~RCC_CR_PLL1ON;
        while (RCC->CR & RCC_CR_PLL1RDY) {}

        //Configure PLL1 clock source
        RCC->PLLCKSELR &= ~RCC_PLLCKSELR_PLLSRC_Msk;
        RCC->PLLCKSELR |= RCC_PLLCKSELR_PLLSRC_HSE;

        //Configure PLL1 multiplication factor
        RCC->PLLCKSELR &= ~RCC_PLLCKSELR_DIVM1_Msk;
        RCC->PLLCKSELR |= 5 << RCC_PLLCKSELR_DIVM1_Pos;

        //Configure PLL1 division factor
        RCC->PLL1DIVR = ((192U - 1U) << RCC_PLL1DIVR_N1_Pos) |
                        ((  2U - 1U) << RCC_PLL1DIVR_P1_Pos) |
                        ((  2U - 1U) << RCC_PLL1DIVR_Q1_Pos) |
                        ((  2U - 1U) << RCC_PLL1DIVR_R1_Pos);

        //Configure PLL PLL1FRACN
        RCC->PLL1FRACR = (RCC->PLL1FRACR & ~RCC_PLL1FRACR_FRACN1_Msk);

        //Select PLL1 input reference frequency range: VCI
        RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLL1RGE_Msk) | RCC_PLLCFGR_PLL1RGE_3;

        //Select PLL1 output frequency range : VCO
        RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLL1VCOSEL_Msk);

        //Enable PLL1 System, PLL1Q, PLL1R and PLL1FRACN Clock output
        RCC->PLLCFGR |= RCC_PLLCFGR_DIVP1EN | RCC_PLLCFGR_DIVQ1EN | RCC_PLLCFGR_DIVR1EN | RCC_PLLCFGR_PLL1FRACEN;

        //Enable PLL1
        RCC->CR |= RCC_CR_PLL1ON;
        while (!(RCC->CR & RCC_CR_PLL1RDY)) {}
    }

    //Configure PLL2
    {
        //Disable PLL2
        RCC->CR &= ~RCC_CR_PLL2ON;
        while (RCC->CR & RCC_CR_PLL2RDY) {}

        //Configure PLL2 multiplication factor
        RCC->PLLCKSELR &= ~RCC_PLLCKSELR_DIVM2_Msk;
        RCC->PLLCKSELR |= 5 << RCC_PLLCKSELR_DIVM2_Pos;

        //Configure PLL2 division factor
        RCC->PLL2DIVR = ((192U - 1U) << RCC_PLL2DIVR_N2_Pos) |
                        ((  2U - 1U) << RCC_PLL2DIVR_P2_Pos) |
                        ((  2U - 1U) << RCC_PLL2DIVR_Q2_Pos) |
                        ((  4U - 1U) << RCC_PLL2DIVR_R2_Pos);

        //Configure PLL PLL2FRACN
        RCC->PLL2FRACR = (RCC->PLL2FRACR & ~RCC_PLL2FRACR_FRACN2_Msk);

        //Select PLL2 input reference frequency range: VCI
        RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLL2RGE_Msk) | RCC_PLLCFGR_PLL2RGE_3;

        //Select PLL2 output frequency range : VCO
        RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLL2VCOSEL_Msk);

        //Enable PLL System, PLL2Q, PLL2R and PLL2FRACN Clock output
        RCC->PLLCFGR |= RCC_PLLCFGR_DIVP2EN | RCC_PLLCFGR_DIVQ2EN | RCC_PLLCFGR_DIVR2EN | RCC_PLLCFGR_PLL2FRACEN;

        //Enable PLL2
        RCC->CR |= RCC_CR_PLL2ON;
        while (!(RCC->CR & RCC_CR_PLL2RDY)) {}
    }

    //Configure PLL3
    {
        //Disable PLL3
        RCC->CR &= ~RCC_CR_PLL3ON;
        while (RCC->CR & RCC_CR_PLL3RDY) {}

        //Configure PLL3 multiplication factor
        RCC->PLLCKSELR &= ~RCC_PLLCKSELR_DIVM3_Msk;
        RCC->PLLCKSELR |= 5 << RCC_PLLCKSELR_DIVM3_Pos;

        //Configure PLL3 division factor
        RCC->PLL3DIVR = ((192U - 1U) << RCC_PLL3DIVR_N3_Pos) |
                        ((  2U - 1U) << RCC_PLL3DIVR_P3_Pos) |
                        (( 16U - 1U) << RCC_PLL3DIVR_Q3_Pos) |
                        ((  8U - 1U) << RCC_PLL3DIVR_R3_Pos);

        //Configure PLL PLL3FRACN
        RCC->PLL3FRACR = (RCC->PLL3FRACR & ~RCC_PLL3FRACR_FRACN3_Msk);

        //Select PLL3 input reference frequency range: VCI
        RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLL2RGE_Msk) | RCC_PLLCFGR_PLL2RGE_3;

        //Select PLL3 output frequency range : VCO
        RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLL2VCOSEL_Msk);

        //Enable PLL3 System, PLL3Q, PLL3R and PLL3FRACN Clock output
        RCC->PLLCFGR |= RCC_PLLCFGR_DIVP3EN | RCC_PLLCFGR_DIVQ3EN | RCC_PLLCFGR_DIVR3EN | RCC_PLLCFGR_PLL3FRACEN;

        //Enable PLL3
        RCC->CR |= RCC_CR_PLL3ON;
        while (!(RCC->CR & RCC_CR_PLL3RDY)) {}
    }

    //Increasing the CPU frequency 
    //Program the new number of wait states to the LATENCY bits in the FLASH_ACR register
    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_4WS;

    //Configures the AHB clock (AXI, HCLK3, AHB1, AHB2, AHB4)
    RCC->D1CFGR &= ~RCC_D1CFGR_HPRE_Msk;
    RCC->D1CFGR |= RCC_D1CFGR_HPRE_DIV2;

    //Configures the system core clock
    RCC->D1CFGR &= ~RCC_D1CFGR_D1CPRE_Msk;
    RCC->D1CFGR |= RCC_D1CFGR_D1CPRE_DIV1;

    //Switch SYSCLK source to the PLL
    RCC->CFGR = (RCC_CFGR_SW & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL1;
    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL1)) {}

    //Decreasing the number of wait states because of lower CPU frequency
    //Program the new number of wait states to the LATENCY bits in the FLASH_ACR register
    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_4WS;

    //Configures the High Speed APB clock (APB3)
    RCC->D1CFGR = (RCC->D1CFGR & ~RCC_D1CFGR_D1PPRE) | RCC_D1CFGR_D1PPRE_DIV2;

    //Configures the High Speed APB clock (APB1)
    RCC->D2CFGR = (RCC->D2CFGR & ~RCC_D2CFGR_D2PPRE1) | RCC_D2CFGR_D2PPRE1_DIV2;

    //Configures the High Speed APB clock (APB2)
    RCC->D2CFGR = (RCC->D2CFGR & ~RCC_D2CFGR_D2PPRE2) | RCC_D2CFGR_D2PPRE2_DIV2;

    //Configures the High Speed APB clock (APB4)
    RCC->D3CFGR = (RCC->D3CFGR & ~RCC_D3CFGR_D3PPRE) | RCC_D3CFGR_D3PPRE_DIV2;

    //Configures hse_ck as the per_ck source
    RCC->D1CCIPR = (RCC->D1CCIPR & ~RCC_D1CCIPR_CKPERSEL) | RCC_D1CCIPR_CKPERSEL_1;

    //Update the SystemCoreClock variable
    SystemCoreClockUpdate();

    //Update the cyclesInMicro variable
    cyclesInMicro = SystemCoreClock / microsInSec;
}


/// @brief Delays for a specified number of microseconds.
void ConcreteSystem::DelayUs(uint32_t micros)
{
    uint32_t delayStart = DWT->CYCCNT;
    uint32_t delayCycles = (micros * cyclesInMicro);
    while ((DWT->CYCCNT - delayStart) < delayCycles);
}


/// @brief Delays for a specified number of milliseconds.
void ConcreteSystem::DelayMs(uint32_t millis)
{
    DelayUs(1000 * millis);
}


/// @brief Enables IRQ interrupts by clearing the I-bit in the CPSR.
void ConcreteSystem::EnableIRQ()
{
    __enable_irq();
}


/// @brief Disables IRQ interrupts by setting the I - bit in the CPSR.
void ConcreteSystem::DisableIRQ()
{
    __disable_irq();
}


/// @brief Enters Sleep mode
void ConcreteSystem::Sleep()
{
    //Clear SLEEPDEEP bit
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    //Request Wait For Interrupt
    __WFI();
}


/// @brief Enters Standby mode
void ConcreteSystem::Standby()
{
    //Enter DSTANDBY mode when Cortex-M7 enters DEEP-SLEEP
    PWR->CPUCR |= (PWR_CPUCR_PDDS_D1 | PWR_CPUCR_PDDS_D3);

    //Set SLEEPDEEP bit
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    //Ensure that all instructions are done before entering STOP mode
    __DSB ();
    __ISB ();

    //Request Wait For Interrupt
    __WFI();
}


/// @brief Enters Stop mode
void ConcreteSystem::Shutdown()
{
    //Select LPDS bits
    PWR->CR1 = (PWR->CR1 & ~PWR_CR1_LPDS) | PWR_CR1_LPDS;

    //Keep DSTOP mode when Cortex-M7 enter in DEEP-SLEEP
    PWR->CPUCR &= ~(PWR_CPUCR_PDDS_D1 | PWR_CPUCR_PDDS_D3);

    //Set SLEEPDEEP bit
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    //Ensure that all instructions are done before entering STOP mode
    __DSB ();
    __ISB ();

    //Wait Wake-up
    __WFI();

    //Clear SLEEPDEEP bit
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
}


/// @brief Reset STM32 core and peripherals
void ConcreteSystem::Reboot()
{
    __set_FAULTMASK(1);
    NVIC_SystemReset();
}


/// @brief Get system clock count
/// @return 
uint32_t ConcreteSystem::GetSysClkCounts() { return sysTicks; }


/// @brief System clock counter
void ConcreteSystem::SysTickCounter() { sysTicks++; }


/// @brief System clock handler
void ConcreteSystem::SysTickHandler() { sysTicks++; }
