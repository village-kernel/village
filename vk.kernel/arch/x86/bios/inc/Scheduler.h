//###########################################################################
// Scheduler.h
// Declarations of the functions that manage thread scheduler
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "Module.h"


/// @brief Scheduler
class Scheduler : public Module
{
public:
	//Enumerations
	enum Access
	{
		Unprivileged = 0,
		Privileged = 1,
	};
public:
	//Methods
	virtual void StartScheduler() = 0;
	virtual void Rescheduler(Access access) = 0;
};

#endif // !__SCHEDULER_H__
