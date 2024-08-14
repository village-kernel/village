//###########################################################################
// Exception.h
// Declarations of the functions that manage exception
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include "Kernel.h"


/// @brief Exception
class Exception
{
public:
	/// @brief Static constants
	static const uint32_t isr_num = 256;
	static const uint32_t rsvd_isr_size = 16;
private:
	/// @brief Enumerations
	enum IRQnType
	{
		NonMaskableInt_IRQn         = -14,
		HardFault_IRQn              = -13,
		MemoryManagement_IRQn       = -12,
		BusFault_IRQn               = -11,
		UsageFault_IRQn             = -10,
		SVCall_IRQn                 = -5,
		DebugMonitor_IRQn           = -4,
		PendSV_IRQn                 = -2,
		SysTick_IRQn                = -1,
	};
private:
	/// @brief Methods
	void InstallHandlers();
	void ConfigVectorTable(uint32_t vector);

	/// @brief Static Methods
	static void StubHandler();
	static void NMIHandler();
	static void HardFaultHandler();
	static void MemManageHandler();
	static void BusFaultHandler();
	static void UsageFaultHandler();
	static void DebugMonHandler();
public:
	/// @brief Methods
	void Setup();
	void Exit();
	void Install(int irq, uint32_t handler);
};

#endif //!__EXCEPTION_H__
