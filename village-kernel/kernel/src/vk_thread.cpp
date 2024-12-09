//###########################################################################
// vk_thread.cpp
// Definitions of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_thread.h"


/// @brief Constructor
ConcreteThread::ConcreteThread()
	:memory(NULL),
	system(NULL),
	scheduler(NULL)
{
}


/// @brief Destructor
ConcreteThread::~ConcreteThread()
{
}


/// @brief Thread setup
void ConcreteThread::Setup()
{
	//Gets the memory pointer
	memory = (Memory*)&kernel->memory;

	//Gets the system pointer
	system = (System*)&kernel->system;

	//Gets the scheduler pointer
	scheduler = (Scheduler*)&kernel->scheduler;

	//Frist task should be idle task and the tid is 0
	CreateTask("Thread::IdleTask", (Method)&ConcreteThread::IdleTask, this);

	//Output debug info
	kernel->debug.Info("Thread setup done!");
}


/// @brief Thread start
void ConcreteThread::Start()
{
	for (tasks.Begin(); !tasks.IsEnd(); tasks.Next())
	{
		tasks.Item()->state = TaskState::_Running;
	}
	tasks.Begin();
}


/// @brief Exit
void ConcreteThread::Exit()
{
	tasks.Release();
}


/// @brief Thread task function handler 
/// @param function execute function
/// @param user execute user
void ConcreteThread::TaskHandler(Function function, void* user, void* args)
{
	if (NULL != function)
	{
		(function)(user, args);
	}
	TaskExit(); while(1) {}
}


/// @brief Create new task
/// @param function task execute function
/// @param user task execute uesr
/// @param args task execute args
/// @return tid
int ConcreteThread::CreateTask(const char* name, Function function, void* user, void* args)
{
	//Create a new task and allocate stack space
	Task* task = new Task(memory->StackAlloc(task_stack_size), (char*)name);
	
	//Check whether stack allocation is successful
	if (NULL == task && 0 == task->stack) return -1;

	//Fill the stack content
	task->psp = task->stack - psp_frame_size;
	*(TaskContext*)task->psp = TaskContext
	(
		(uint32_t)union_cast<uint32_t>(&ConcreteThread::TaskHandler),
		(uint32_t)this,
		(uint32_t)function,
		(uint32_t)user,
		(uint32_t)args
	);

	//Add task into tasks list
	task->tid = tasks.Add(task);

	//return task tid
	return task->tid;
}


/// @brief Create new task for cpp
/// @param method task execute class method
/// @param user task execute class
/// @param args task execute args
/// @return tid
int ConcreteThread::CreateTask(const char* name, Method method, Class *user, void* args)
{
	return CreateTask(name, union_cast<Function>(method), (void*)user, args);
}


/// @brief Start task
/// @param tid 
/// @return 
bool ConcreteThread::StartTask(int tid)
{
	//Gets the task
	Task* task = tasks.GetItem(tid);

	//Check task is valid
	if (NULL != task)
	{
		task->state = TaskState::_Running;
		return true;
	}
	return false;
}


/// @brief Stop task
/// @param tid 
/// @return 
bool ConcreteThread::StopTask(int tid)
{
	//Gets the task
	Task* task = tasks.GetItem(tid);

	//Check task is valid
	if (NULL != task)
	{
		task->state = TaskState::_Exited;
		return true;
	}
	return false;
}


/// @brief Thread wait for task
/// @param tid thread id
/// @return result
bool ConcreteThread::WaitForTask(int tid)
{
	//Gets the task
	Task* task = tasks.GetItem(tid);

	//Check task is valid
	if (NULL != task)
	{
		//Blocking wait
		while(task->state != TaskState::_Exited) {}
		return true;
	}
	return false;
}


/// @brief Thread delete task
/// @param tid thread id
/// @return result
bool ConcreteThread::DeleteTask(int tid)
{
	//Gets the task
	Task* task = tasks.GetItem(tid);

	//Check task is valid
	if (NULL != task)
	{
		memory->Free(task->stack);
		return tasks.Remove(task, tid);
	}
	return true;
}


/// @brief Thread check task is alive
/// @param tid 
/// @return result
bool ConcreteThread::IsTaskAlive(int tid)
{
	//Gets the task
	Task* task = tasks.GetItem(tid);

	//Returns true when the task is not null and the status is not exited
	return ((NULL != task) && (task->state != TaskState::_Exited));
}


/// @brief Get tasks
/// @return 
VkList<ConcreteThread::Task*> ConcreteThread::GetTasks()
{
	return tasks;
}


/// @brief Change State
/// @param state 
void ConcreteThread::ChangeState(TaskState state)
{
	if(tasks.GetNid() > 0)
	{
		tasks.Item()->state = state;
		scheduler->Sched();
	}
}


/// @brief Thread sleep
/// @param ticks sleep ticks
void ConcreteThread::Sleep(uint32_t ticks)
{
	if(tasks.GetNid() > 0)
	{
		tasks.Item()->state = TaskState::_Suspend;
		tasks.Item()->ticks = system->GetSysClkCounts() + ticks;
		scheduler->Sched();
		while (TaskState::_Suspend == tasks.Item()->state) {}
	}
}


/// @brief Thread Blocked
void ConcreteThread::Blocked()
{
	if(tasks.GetNid() > 0)
	{
		tasks.Item()->state = TaskState::_Blocked;
		scheduler->Sched();
		while (TaskState::_Blocked == tasks.Item()->state) {}
	}
}


/// @brief Thread Exit
void ConcreteThread::TaskExit()
{
	if(tasks.GetNid() > 0)
	{
		tasks.Item()->state = TaskState::_Exited;
		DeleteTask(tasks.GetNid());
		scheduler->Sched();
	}
}


/// @brief Save task PSP
/// @param psp process stack pointer
void ConcreteThread::SaveTaskPSP(uint32_t psp)
{
	tasks.Item()->psp = psp;
}


/// @brief Get current task psp
/// @return process stack pointer
uint32_t ConcreteThread::GetTaskPSP()
{
	return tasks.Item()->psp;
}


/// @brief Select next task, round-Robin scheduler
void ConcreteThread::SelectNextTask()
{
	while (1)
	{
		//Set next task as current task
		tasks.Next(); if (tasks.IsEnd()) tasks.Begin();

		//Check current task state
		if (TaskState::_Suspend == tasks.Item()->state)
		{
			if(system->GetSysClkCounts() >= tasks.Item()->ticks)
			{
				tasks.Item()->state = TaskState::_Running;
				tasks.Item()->ticks = 0;
			}
		}

		//Break when task state is running
		if (TaskState::_Running == tasks.Item()->state) break;
	}
}


/// @brief Idle task
void ConcreteThread::IdleTask()
{
	while (1)
	{
		__asm volatile("NOP");
	} 
}
