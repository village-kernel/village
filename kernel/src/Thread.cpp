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


/// @brief Constructor
Thread::Thread()
{
}


/// @brief Fini constructor
Thread::~Thread()
{
}


/// @brief Singleton Instance
/// @return Thread instance
Thread& Thread::Instance()
{
	static Thread instance;
	return instance;
}
EXPORT_SYMBOL(Thread::Instance, _ZN6Thread8InstanceEv);


/// @brief Definitions thread and export
Thread& thread = Thread::Instance();
static Thread* pthread = &thread;
EXPORT_SYMBOL(pthread, thread);


/// @brief Thread Initialize
void Thread::Initialize()
{
	//Frist task should be idle task and the pid is 0
	CreateTask((Function)&Thread::IdleTask);

	//Set first node
	tasks.Begin();
}


/// @brief Thread execute
void Thread::Execute()
{
	FuncHandler((Function)&Thread::IdleTask);
}


/// @brief Create new task
/// @param function task execute function
/// @param argv task execute argv
/// @return result
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


/// @brief Create new task for cpp
/// @param user task execute class
/// @param method task execute class method
/// @param argv task execute argv
/// @return result
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


/// @brief Thread delete task
/// @param pid process id
/// @return result
int Thread::DeleteTask(int pid)
{
	Task* task = tasks.GetItem(pid);
	memory.Free(task->stack);
	return tasks.Remove(task, pid);
}
EXPORT_SYMBOL(Thread::DeleteTask, _ZN6Thread10DeleteTaskEi);


/// @brief Thread wait for task
/// @param pid process id
/// @return result
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


/// @brief Thread sleep
/// @param ticks sleep ticks
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


/// @brief Thread Exit
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


/// @brief Idle task
void Thread::IdleTask()
{
	while (1) 
	{
		__asm volatile("NOP");
	}
}


/// @brief Thread task function handler 
/// @param function execute function
/// @param argv execute argv
void Thread::FuncHandler(Function function, char* argv)
{
	if (NULL != function)
	{
		(function)(argv);
	}
	thread.Exit();
}


/// @brief Thread task method handler 
/// @param user execute class
/// @param method execute class method
/// @param argv execute argv
void Thread::MethodHandler(Class *user, Method method, char* argv)
{
	if (NULL != user && NULL != method)
	{
		(user->*method)(argv);
	}
	thread.Exit();
}


/// @brief Save task PSP
/// @param psp process stack pointer
void Thread::SaveTaskPSP(uint32_t psp)
{
	tasks.Item()->psp = psp;
}


/// @brief Get current task psp
/// @return process stack pointer
uint32_t Thread::GetTaskPSP()
{
	return tasks.Item()->psp;
}


/// @brief Select next task, round-Robin scheduler
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
