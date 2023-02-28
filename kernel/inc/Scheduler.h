//###########################################################################
// Scheduler.h
// Declarations of the functions that manage thread scheduler
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "stdint.h"
#include "stddef.h"

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
	static bool isStartSchedule;
public:
	//Methods
	Scheduler();
	static void StartScheduler();
	static void Rescheduler(Access access);

	//Needed called by SVC_Handler
	static void TaskOperator(uint32_t* SP);
};

#endif // !__SCHEDULER_H__
