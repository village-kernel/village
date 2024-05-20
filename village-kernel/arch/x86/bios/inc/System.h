//###########################################################################
// System.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "Kernel.h"


/// @brief ConcreteSystem
class ConcreteSystem : public System, public Class
{
private:
	//Members
	uint32_t sysTicks;
	
	//Methods
	void SysTickHandler();
	void ConfigureClock();
public:
	//Methods
	ConcreteSystem();
	~ConcreteSystem();
	void Setup();
	void Exit();
	void SysTickCounter();
	uint32_t GetSysClkCounts();
	void DelayMs(uint32_t millis);
	void EnableIRQ();
	void DisableIRQ();
	void Reboot();
};

#endif //!__SYSTEM_H__
