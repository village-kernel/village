//###########################################################################
// WorkQueue.cpp
// Definitions of the functions that manage work queue
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "WorkQueue.h"
#include "Kernel.h"


/// @brief Constructor
WorkQueue::WorkQueue()
{
}


/// @brief Destructor
WorkQueue::~WorkQueue()
{
}


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
				if (work->ticks) Kernel::thread.Sleep(work->ticks);
				(work->func)(work->user, work->args);
				work->state = _Finish;
			}
		}
	}
}


/// @brief WorkQueue create
/// @param func work function
/// @param user work user
/// @param args work args
/// @param ticks delay ticks
/// @return work
WorkQueue::Work* WorkQueue::Create(Function func, void* user, void* args, uint32_t ticks)
{
	Work* work = new Work(func, user, args, ticks);
	if (NULL != work) works.Add(work);
	return work;
}
EXPORT_SYMBOL(_ZN9WorkQueue6CreateEPFvPvS0_ES0_S0_m);


/// @brief WorkQueue create
/// @param method work method
/// @param user work user
/// @param args work args
/// @param ticks delay ticks
/// @return work
WorkQueue::Work* WorkQueue::Create(Method method, Class* user, void* args, uint32_t ticks)
{
	return Create(union_cast<Function>(method), (void*)user, args, ticks);
}
EXPORT_SYMBOL(_ZN9WorkQueue6CreateEM5ClassFvPvEPS0_S1_m);


/// @brief WorkQueue delete
/// @param work workqueue work
/// @return result
int WorkQueue::Delete(Work* work)
{
	if (NULL != work && _Finish == work->state)
	{
		return works.Remove(work);
	}
	return _ERR;
}
EXPORT_SYMBOL(_ZN9WorkQueue6DeleteEPNS_4WorkE);


/// @brief WorkQueue schedule
/// @param work workqueue work
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
EXPORT_SYMBOL(_ZN9WorkQueue8ScheduleEPNS_4WorkE);


///Register module
REGISTER_MODULE(new WorkQueue(), ModuleID::_workQueue, workQueue);
