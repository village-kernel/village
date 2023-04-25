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
	static void ConfigVectorTable(uint32_t vector);

	///Reset x86 core
	static inline void Reboot()
	{

	}

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

	///Enables IRQ interrupts
	static inline void EnableIRQ() {  }

	///Disables IRQ interrupts
	static inline void DisableIRQ() {  }
};

#endif //!__SYSTEM_H__
