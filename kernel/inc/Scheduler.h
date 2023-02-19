//###########################################################################
// Scheduler.h
// Declarations of the functions that manage thread scheduler
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "Thread.h"

///Scheduler
class Scheduler
{
public:
	//Enumerations
	enum Access
	{
		Unprivileged = 0,
		Privileged = 1,
	};
private:
	//Members
	static uint32_t sysTicks;
public:
	//Methods
	Scheduler();
	static void Initialize();
	static void StartScheduler();
	static void Rescheduler(Access access);
	static uint32_t GetSysTicks();

	//Needed called by SVC_Handler
	static void TaskOperator(uint32_t* SP);

	//Needed called by SysTick_Handler
	static void SystickCount();
};

#endif // !__SCHEDULER_H__
