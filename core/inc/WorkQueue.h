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
		char*    argv;
		uint32_t ticks;
		State    state;

		Work(Function func, char* argv, uint32_t ticks)
			:func(func),
			argv(argv),
			ticks(ticks),
			state(_Suspend)
		{}
	};
private:
	//Members
	List<Work> works;

	//Methods
	WorkQueue();
	~WorkQueue();
public:
	//Methods
	void Initialize();
	void Execute();
	Work* Create(Function func, char* argv = NULL, uint32_t ticks = 0);
	int Delete(Work* work);
	int Schedule(Work* work);

	//Singleton Instance
	static WorkQueue& Instance();
};

///Declarations work queue reference
extern WorkQueue& workQueue;

#endif // !__WORK_QUEUE_H__
