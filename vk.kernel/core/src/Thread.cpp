//###########################################################################
// Thread.cpp
// Definitions of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Thread.h"
#include "System.h"
#include "Kernel.h"


/// @brief Constructor
Thread::Thread()
{
}


/// @brief Fini constructor
Thread::~Thread()
{
}


/// @brief Thread Initialize
void Thread::Initialize()
{
	//Frist task should be idle task and the pid is 0
	CreateTask("IdleTask", (Method)&Thread::IdleTask, this);

	//Set first node
	tasks.Begin();
}


/// @brief Thread execute
void Thread::Execute()
{
	TaskHandler(union_cast<Function>(&Thread::IdleTask), (void*)this);
}


/// @brief Create new task
/// @param function task execute function
/// @param user task execute uesr
/// @param args task execute args
/// @return pid
int Thread::CreateTask(const char* name, Function function, void* user, void* args)
{
	//Create a new task and allocate stack space
	Task* task = new Task(Kernel::memory.StackAlloc(task_stack_size));
	
	//Check whether stack allocation is successful
	if (NULL == task && 0 == task->stack) return -1;

	//Fill the stack content
	task->psp = task->stack - psp_frame_size;
	*(TaskContext*)task->psp = TaskContext
	(
		(uint32_t)union_cast<uint32_t>(&Thread::TaskHandler),
		(uint32_t)this,
		(uint32_t)function,
		(uint32_t)user,
		(uint32_t)args
	);

	return tasks.Add(task, (char*)name);
}
EXPORT_SYMBOL(_ZN6Thread10CreateTaskEPKcPFvPvS2_ES2_S2_);


/// @brief Create new task for cpp
/// @param method task execute class method
/// @param user task execute class
/// @param args task execute args
/// @return pid
int Thread::CreateTask(const char* name, Method method, Class *user, void* args)
{
	return CreateTask(name, union_cast<Function>(method), (void*)user, args);
}
EXPORT_SYMBOL(_ZN6Thread10CreateTaskEPKcM5ClassFvPvEPS2_S3_);


/// @brief Thread delete task
/// @param pid process id
/// @return result
int Thread::DeleteTask(int pid)
{
	Task* task = tasks.GetItem(pid);
	Kernel::memory.Free(task->stack);
	return tasks.Remove(task, pid);
}
EXPORT_SYMBOL(_ZN6Thread10DeleteTaskEi);


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
EXPORT_SYMBOL(_ZN6Thread11WaitForTaskEi);


/// @brief Get tasks
/// @return 
List<Thread::Task*> Thread::GetTasks()
{
	return tasks;
}
EXPORT_SYMBOL(_ZN6Thread8GetTasksEv);


/// @brief Thread sleep
/// @param ticks sleep ticks
void Thread::Sleep(uint32_t ticks)
{
	if(tasks.GetNid() > 0)
	{
		tasks.Item()->state = TaskState::Suspend;
		tasks.Item()->ticks = System::GetSysClkCounts() + ticks;
		Kernel::scheduler.Rescheduler(Scheduler::Unprivileged);
	}
}
EXPORT_SYMBOL(_ZN6Thread5SleepEm);


/// @brief Thread Exit
void Thread::Exit()
{
	if(tasks.GetNid() > 0)
	{
		tasks.Item()->state = TaskState::Exited;
		DeleteTask(tasks.GetNid());
		Kernel::scheduler.Rescheduler(Scheduler::Unprivileged);
	}
}
EXPORT_SYMBOL(_ZN6Thread4ExitEv);


/// @brief Idle task
#if defined(ARCH_X86)
void Thread::IdleTask() { while (1) { __asm volatile ("hlt" ::: "memory"); }}
#else
void Thread::IdleTask() { while (1) { __asm volatile("NOP"); } }
#endif


/// @brief Thread task function handler 
/// @param function execute function
/// @param user execute user
void Thread::TaskHandler(Function function, void* user, void* args)
{
	if (NULL != function)
	{
		(function)(user, args);
	}
	Kernel::thread.Exit();
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
