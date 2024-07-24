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
private:
	//Enumerations
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

	//Static Methods
	static void NMIHandler();
	static void HardFaultHandler();
	static void MemManageHandler();
	static void BusFaultHandler();
	static void UsageFaultHandler();
	static void DebugMonHandler();
	static void ExceptionInfo(const char* exception);
public:
	//Methods
	Exception();
	~Exception();
	void Setup();
	void Exit();
};

#endif //!__EXCEPTION_H__
