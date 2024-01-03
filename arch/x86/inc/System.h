//###########################################################################
// System.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "Hardware.h"

///System
class System
{
private:
	static uint32_t sysTicks;
public:
	static void Initialize();
	static void ConfigureMPU();
	static void ConfigurePower();
	static void ConfigureClock();

	///Reset x86 core
	static inline void Reboot()
	{
		uint64_t null_idtr = 0;
		__asm volatile ("lidt %0; int3" :: "m" (null_idtr));

		//Loop with interrupt off if it doesn't work
		__asm volatile ("cli");
		while (1) { __asm volatile ("hlt"); }
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
	static inline void EnableIRQ() { __asm volatile("sti"); }

	///Disables IRQ interrupts
	static inline void DisableIRQ() { __asm volatile("cli"); }
};

#endif //!__SYSTEM_H__
