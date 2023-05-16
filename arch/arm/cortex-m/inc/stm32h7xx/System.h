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
	static uint32_t sysTicks;
public:
	static void Initialize();
	static void ConfigureMPU();
	static void ConfigurePower();
	static void ConfigureClock();
	static void ConfigureForHsi();
	static void ConfigureForXtal();

	///Reset STM32 core and peripherals
	static inline void Reboot()
	{
		__set_FAULTMASK(1);
		NVIC_SystemReset();
	}
#ifdef PRIVILEGED_LEVEL_DELAY
	///Delays for a specified number of microseconds.
	static inline void DelayUs(uint32_t micros)
	{
		uint32_t delayStart = DWT->CYCCNT;
		uint32_t delayCycles = (micros * cyclesInMicro);
		while ((DWT->CYCCNT - delayStart) < delayCycles);
	}

	///Delays for a specified number of milliseconds.
	static inline void DelayMs(uint32_t millis) { DelayUs(1000 * millis); }

	///Get system clock count
	static inline uint32_t GetSysClkCounts() { return DWT->CYCCNT; }
#else
	///Delays for a specified number of milliseconds.
	static inline void DelayMs(uint32_t millis)
	{
		uint32_t delayStart = sysTicks;
		uint32_t delayCycles = millis;
		while ((sysTicks - delayStart) < delayCycles);
	}

	///Get system clock count
	static inline uint32_t GetSysClkCounts() { return sysTicks; }

	///System clock counter
	static inline void SysTickCounter() { sysTicks++; }
#endif
	///Enables IRQ interrupts by clearing the I-bit in the CPSR.
	static inline void EnableIRQ() { __enable_irq(); }

	///Disables IRQ interrupts by setting the I - bit in the CPSR.
	static inline void DisableIRQ() { __disable_irq(); }
};

#endif /* __SYSTEM_H__ */