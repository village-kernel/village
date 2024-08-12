//###########################################################################
// Scheduler.h
// Declarations of the functions that manage thread scheduler
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "Kernel.h"


/// @brief ConcreteScheduler
class ConcreteScheduler : public Scheduler, public Class
{
private:
	/// @brief Members
	bool isStartSchedule;

	/// @brief Methods
	void SysTickHandler();
	void PendSVHandler();
public:
	/// @brief Methods
	ConcreteScheduler();
	~ConcreteScheduler();
	void Setup();
	void Exit();
	void Start();
	void Sched();
};

#endif // !__SCHEDULER_H__
