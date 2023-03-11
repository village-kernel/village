//###########################################################################
// System.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "HalHeaders.h"

///System
class System
{
private:
	static const uint32_t microsInSec = 1000000;
	static const uint32_t microsInMilli = 1000;
	static uint32_t cyclesInMicro;

public:
	static void Initialize();
	static void ConfigureMPU();
	static void ConfigurePower();
	static void ConfigureForHsi();
	static void ConfigureForXtal();

	///Reset STM32 core and peripherals
	static inline void Reboot()
	{
		__set_FAULTMASK(1);
		NVIC_SystemReset();
	}

	///Delays for a specified number of microseconds.
	///Delay range: 0-798915 us
	static inline void DelayUs(uint32_t micros)
	{
		CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
		uint32_t delayStart = DWT->CYCCNT;
		uint32_t delayCycles = (micros * cyclesInMicro);
		while ((DWT->CYCCNT - delayStart) < delayCycles);
	}

	///Delays for a specified number of milliseconds.
	///Delay range: 0-798 ms
	static inline void DelayMs(uint32_t millis) { DelayUs(1000 * millis); }
	static inline uint32_t GetSysClkCount() { return DWT->CYCCNT; }

	///Enables IRQ interrupts by clearing the I-bit in the CPSR.
	static inline void EnableIRQ() { __enable_irq(); }

	///Disables IRQ interrupts by setting the I - bit in the CPSR.
	static inline void DisableIRQ() { __disable_irq(); }
};


#endif /* __SYSTEM_H__ */