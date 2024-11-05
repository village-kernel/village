//###########################################################################
// vk_timer.cpp
// Definitions of the functions that manage timer
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_timer.h"
#include "vk_hardware.h"


/// @brief Constructor
ConcreteTimer::ConcreteTimer()
{
}


/// @brief Destructor
ConcreteTimer::~ConcreteTimer()
{
}


/// @brief ConcreteTimer Setup
void ConcreteTimer::Setup()
{
	//Gets the system pointer
	system = (System*)&kernel->system;

	//Set interrupt handler
	kernel->interrupt.AppendISR(SysTick_IRQn, (Method)&ConcreteTimer::Execute, this);

	//Output debug info
	kernel->debug.Info("Timer setup done!");
}


/// @brief ConcreteTimer Execute
void ConcreteTimer::Execute()
{
	for (Job* job = jobs.Begin(); !jobs.IsEnd(); job = jobs.Next())
	{
		if (_Ready == job->state)
		{
			if (system->GetSysClkCounts() >= job->ticks)
			{
				job->state = _Done;
				(job->func)(job->user, job->args);
			}
		}
	}
}


/// @brief ConcreteTimer Exit
void ConcreteTimer::Exit()
{
	//Release jobs
	jobs.Release();
	
	//Remove interrupt handler
	kernel->interrupt.RemoveISR(SysTick_IRQn, (Method)&ConcreteTimer::Execute, this);
}


/// @brief ConcreteTimer Create
/// @param ticks 
/// @param func 
/// @param user 
/// @param args 
/// @return 
ConcreteTimer::Job* ConcreteTimer::Create(uint32_t ticks, Function func, void* user, void* args)
{
	Job* job = new Job(ticks, func, user, args);
	if (NULL != job) jobs.Add(job);
	return job;
}


/// @brief ConcreteTimer Create
/// @param ticks 
/// @param method 
/// @param user 
/// @param args 
/// @return 
ConcreteTimer::Job* ConcreteTimer::Create(uint32_t ticks, Method method, Class* user, void* args)
{
	return Create(ticks, union_cast<Function>(method), (void*)user, args);
}


/// @brief ConcreteTimer Modify
/// @param ticks 
/// @return 
void ConcreteTimer::Modify(Job* job, uint32_t ticks)
{
	job->ticks = ticks;
	job->state = _Ready;
}


/// @brief ConcreteTimer Delete
/// @param job 
/// @return 
bool ConcreteTimer::Delete(Job* job)
{
	return jobs.Remove(job);
}
