//###########################################################################
// Thread.cpp
// Definitions of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Thread.h"
#include "System.h"
#include "Memory.h"
#include "Scheduler.h"
#include "Environment.h"


///Constructor
Thread::Thread()
{
}


///Singleton instance
Thread& Thread::Instance()
{
	static Thread instance;
	return instance;
}
EXPORT_SYMBOL(Thread::Instance, _ZN6Thread8InstanceEv);


//Definitions thread and export
Thread& thread = Thread::Instance();
static Thread* pthread = &thread;
EXPORT_SYMBOL(pthread, thread);


///Thread Initialize
void Thread::Initialize()
{
	//Frist task should be idle task and the pid is 0
	CreateTask((Function)&Thread::IdleTask);

	//Set first node
	tasks.Begin();
}


///Thread execute
void Thread::Execute()
{
	FuncHandler((Function)&Thread::IdleTask);
}


///Create new task
int Thread::CreateTask(Function function, char* argv)
{
	//Create a new task and allocate stack space
	Task* task = new Task(memory.StackAlloc(task_stack_size));
	
	//Check whether stack allocation is successful
	if (NULL == task && 0 == task->stack) return -1;

	//Fill the stack content
	task->psp = task->stack - psp_frame_size;
	*(StackFrame*)task->psp = StackFrame
	(
		(uint32_t)&FuncHandler,
		(uint32_t)function,
		(uint32_t)argv
	);

	return tasks.Add(task);
}
EXPORT_SYMBOL(Thread::CreateTask, _ZN6Thread10CreateTaskEPFvPcES0_);


///Create new task for cpp
int Thread::CreateTaskCpp(Class *user, Method method, char* argv)
{
	//Create a new task and allocate stack space
	Task* task = new Task(memory.StackAlloc(task_stack_size));
	
	//Check whether stack allocation is successful
	if (NULL == task && 0 == task->stack) return -1;

	//Fill the stack content
	task->psp = task->stack - psp_frame_size;
	*(StackFrame*)task->psp = StackFrame
	(
		(uint32_t)&MethodHandler,
		(uint32_t)user,
		*(uint32_t*)&method,
		(uint32_t)argv
	);

	return tasks.Add(task);
}
EXPORT_SYMBOL(Thread::CreateTaskCpp, _ZN6Thread13CreateTaskCppEP5ClassMS0_FvPcES2_);


///Thread delete task
int Thread::DeleteTask(int pid)
{
	Task* task = tasks.GetItem(pid);
	memory.Free(task->stack);
	return tasks.Remove(task, pid);
}
EXPORT_SYMBOL(Thread::DeleteTask, _ZN6Thread10DeleteTaskEi);


///Thread wait for task
int Thread::WaitForTask(int pid)
{
	//Gets the task
	Task* task = tasks.GetItem(pid);

	//Check task is valid
	if (NULL != task)
	{
		//Blocking wait
		while(task->state != TaskState::Exited) {}
		return _OK;
	}
	return _ERR;
}
EXPORT_SYMBOL(Thread::WaitForTask, _ZN6Thread11WaitForTaskEi);


///Thread sleep
void Thread::Sleep(uint32_t ticks)
{
	if(tasks.GetNid() > 0)
	{
		tasks.Item()->state = TaskState::Suspend;
		tasks.Item()->ticks = System::GetSysClkCounts() + ticks;
		scheduler.Rescheduler(Scheduler::Unprivileged);
	}
}
EXPORT_SYMBOL(Thread::Sleep, _ZN6Thread5SleepEm);


///Thread Exit
void Thread::Exit()
{
	if(tasks.GetNid() > 0)
	{
		tasks.Item()->state = TaskState::Exited;
		DeleteTask(tasks.GetNid());
		scheduler.Rescheduler(Scheduler::Unprivileged);
	}
}
EXPORT_SYMBOL(Thread::Exit, _ZN6Thread4ExitEv);


///Idle task
void Thread::IdleTask()
{
	while (1) 
	{
		__ASM("NOP");
	}
}


///Thread task function handler 
void Thread::FuncHandler(Function function, char* argv)
{
	if (NULL != function)
	{
		(function)(argv);
	}
	thread.Exit();
}


///Thread task method handler 
void Thread::MethodHandler(Class *user, Method method, char* argv)
{
	if (NULL != user && NULL != method)
	{
		(user->*method)(argv);
	}
	thread.Exit();
}


///Save task PSP
void Thread::SaveTaskPSP(uint32_t psp)
{
	tasks.Item()->psp = psp;
}


///Get current task psp
uint32_t Thread::GetTaskPSP()
{
	return tasks.Item()->psp;
}


///Select next task, round-Robin scheduler
void Thread::SelectNextTask()
{
	while (1)
	{
		//Set next task as current task
		tasks.Next(); if (tasks.IsEnd()) tasks.Begin();

		//Check current task state
		if (TaskState::Suspend == tasks.Item()->state)
		{
			if(System::GetSysClkCounts() >= tasks.Item()->ticks)
			{
				tasks.Item()->state = TaskState::Running;
			}
		}

		//Break when task state is running
		if (TaskState::Running == tasks.Item()->state) break;
	}
}
