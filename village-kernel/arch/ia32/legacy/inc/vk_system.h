//###########################################################################
// vk_system.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_SYSTEM_H__
#define __VK_SYSTEM_H__

#include "vk_kernel.h"


/// @brief ConcreteSystem
class ConcreteSystem : public System, public Class
{
private:
	/// @brief Members
	uint32_t sysTicks;
	
	/// @brief Methods
	void SysTickHandler();
	void ConfigureClock();
public:
	/// @brief Methods
	ConcreteSystem();
	~ConcreteSystem();
	void Setup();
	void Exit();

	/// @brief Ticks Methods
	void SysTickCounter();
	uint32_t GetSysClkCounts();
	void DelayMs(uint32_t millis);
	
	/// @brief IRQ Methods
	void EnableIRQ();
	void DisableIRQ();
	
	/// @brief Power Methods
	void Sleep();
	void Standby();
	void Shutdown();
	void Reboot();
};

#endif //!__VK_SYSTEM_H__
