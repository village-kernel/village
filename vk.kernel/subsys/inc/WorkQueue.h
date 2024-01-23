//###########################################################################
// WorkQueue.h
// Declarations of the functions that manage work queue
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __WORK_QUEUE_H__
#define __WORK_QUEUE_H__

#include "Module.h"
#include "Templates.h"

///WorkQueue
class WorkQueue : public Module
{
public:
	//Enumerations
	enum State
	{
		_Suspend = 0,
		_Waked,
		_Running,
		_Finish,
	};

	//Structures
	struct Work
	{
		Function func;
		void*    user;
		void*    args;
		uint32_t ticks;
		State    state;

		Work(Function func, void* user, void* args, uint32_t ticks)
			:func(func),
			user(user),
			args(args),
			ticks(ticks),
			state(_Suspend)
		{}
	};
private:
	//Members
	List<Work*> works;
public:
	//Methods
	WorkQueue();
	~WorkQueue();
	void Initialize();
	void Execute();
	Work* Create(Function func, void* user = NULL, void* args = NULL, uint32_t ticks = 0);
	Work* Create(Method method, Class* user, void* args = NULL, uint32_t ticks = 0);
	int Delete(Work* work);
	int Schedule(Work* work);
};

#endif // !__WORK_QUEUE_H__
