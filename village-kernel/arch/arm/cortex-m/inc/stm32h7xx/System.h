//###########################################################################
// System.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "Kernel.h"


/// @brief System
class ConcreteSystem : public System, public Class
{
private:
	///Static constants
	static const uint32_t microsInSec = 1000000;
	static const uint32_t microsInMilli = 1000;

	//Members
	uint32_t sysTicks;
	uint32_t cyclesInMicro;

	//Methods
	void SysTickHandler();
	void ConfigCoreDebug();
	void ConfigSysTick();
	void ConfigureMPU();
	void ConfigurePower();
	void ConfigureForHsi();
	void ConfigureFor25MhzXtal();
public:
	//Methods
	ConcreteSystem();
	~ConcreteSystem();
	void Setup();
	void Exit();

	//Ticks Metthods
	void SysTickCounter();
	uint32_t GetSysClkCounts();
	void DelayUs(uint32_t micros);
	void DelayMs(uint32_t millis);
	
	//IRQ Methods
	void EnableIRQ();
	void DisableIRQ();

	//Power Methods
	void Sleep();
	void Standby();
	void Shutdown();
	void Reboot();
};

#endif //!__SYSTEM_H__
