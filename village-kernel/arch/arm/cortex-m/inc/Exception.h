//###########################################################################
// Exception.h
// Declarations of the functions that manage exception
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include "Kernel.h"
#include "Class.h"


/// @brief Exception
class Exception : public Class
{
private:
	//Members
	Debug*     debug;
	Interrupt* interrupt;

	//Methods
	void NMIHandler();
	void HardFaultHandler();
	void MemManageHandler();
	void BusFaultHandler();
	void UsageFaultHandler();
	void DebugMonHandler();
public:
	//Methods
	Exception();
	~Exception();
	void Setup();
	void Exit();
};

#endif //!__EXCEPTION_H__
