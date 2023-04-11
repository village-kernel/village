//###########################################################################
// WorkQueue.cpp
// Definitions of the functions that manage work queue
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "WorkQueue.h"
#include "Environment.h"


/// @brief Constructor
WorkQueue::WorkQueue()
{
}


/// @brief Fini constructor
WorkQueue::~WorkQueue()
{
}


/// @brief WorkQueue instance
/// @return Singleton instance
WorkQueue& WorkQueue::Instance()
{
	static WorkQueue instance;
	return instance;
}
EXPORT_SYMBOL(WorkQueue::Instance, _ZN9WorkQueue8InstanceEv);


/// @brief Definitions workQueue
WorkQueue& workQueue = WorkQueue::Instance();
static WorkQueue* pWorkQueue = &workQueue;
EXPORT_SYMBOL(pWorkQueue, workQueue);


/// @brief WorkQueue initialize
void WorkQueue::Initialize()
{

}


/// @brief WorkQueue execute
void WorkQueue::Execute()
{
	while (1)
	{
		for (Work* work = works.Begin(); !works.IsEnd(); work = works.Next())
		{
			if (_Waked == work->state)
			{
				work->state = _Running;
				if (work->ticks) thread.Sleep(work->ticks);
				(work->func)(work->argv);
				work->state = _Finish;
			}
		}
	}
}


/// @brief WorkQueue create
/// @param func 
/// @param argv 
/// @param ticks 
/// @return work
WorkQueue::Work* WorkQueue::Create(Function func, char* argv, uint32_t ticks)
{
	Work* work = new Work(func, argv, ticks);
	if (NULL != work) works.Add(work);
	return work;
}


/// @brief WorkQueue delete
/// @param work 
/// @return result
int WorkQueue::Delete(Work* work)
{
	if (NULL != work && _Finish == work->state)
	{
		return works.Remove(work);
	}
	return _ERR;
}


/// @brief WorkQueue schedule
/// @param work 
/// @return result
int WorkQueue::Schedule(Work* work)
{
	if (NULL != work)
	{
		work->state = _Waked;
		return _OK;
	}
	return _ERR;
}


///Register module
REGISTER_MODULE(pWorkQueue, ModuleID::_workQueue, workQueue);
