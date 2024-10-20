//###########################################################################
// Timer.h
// Declarations of the functions that manage timer
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TIMER_H__
#define __TIMER_H__

#include "Kernel.h"
#include "Timer.h"
#include "List.h"
#include "Cast.h"


/// @brief ConcreteTimer
class ConcreteTimer : public Timer, public Class
{
private:
	/// @brief Members
	System*     system;
	List<Job*>  jobs;
	
	/// @brief Methods
	void Execute();
public:
	/// @brief Methods
	ConcreteTimer();
	~ConcreteTimer();
	void Setup();
	void Exit();

	/// @brief Create Methods
	Job* Create(uint32_t ticks, Function func, void* user = NULL, void* args = NULL);
	Job* Create(uint32_t ticks, Method method, Class* user, void* args = NULL);

	/// @brief Feature Methods
	void Modify(Job* job, uint32_t ticks);
	bool Delete(Job* job);
};

#endif // !__TIMER_H__
