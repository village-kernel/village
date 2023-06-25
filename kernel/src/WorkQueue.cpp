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


/// @brief Singleton Instance
/// @return WorkQueue instance
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
/// @param func work function
/// @param argv work argv
/// @param ticks delay ticks
/// @return work
WorkQueue::Work* WorkQueue::Create(Function func, char* argv, uint32_t ticks)
{
	Work* work = new Work(func, argv, ticks);
	if (NULL != work) works.Add(work);
	return work;
}
EXPORT_SYMBOL(WorkQueue::Create, _ZN9WorkQueue6CreateEPFvPcES0_m);


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
EXPORT_SYMBOL(WorkQueue::Delete, _ZN9WorkQueue6DeleteEPNS_4WorkE);


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
EXPORT_SYMBOL(WorkQueue::Schedule, _ZN9WorkQueue8ScheduleEPNS_4WorkE);


///Register module
REGISTER_MODULE(pWorkQueue, ModuleID::_workQueue, workQueue);
