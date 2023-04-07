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
	:pidCounter(0),
	list(NULL),
	curNode(NULL)
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

	//Set current node
	curNode = list;
}


///Thread execute
void Thread::Execute()
{
	FuncHandler((Function)&Thread::IdleTask);
}


///Thread append a task to the list
int Thread::AppendTask(Task task)
{
	//Find an empty node
	TaskNode** nextNode = &list;
	while (NULL != *nextNode) nextNode = &(*nextNode)->next;

	//Add new task node in task list
	*nextNode = new TaskNode(task);

	//Set the pid for task 
	if (NULL != *nextNode)
	{
		(*nextNode)->task.pid = pidCounter++;
		return (*nextNode)->task.pid;
	}

	//Return -1 when create task failed
	return -1;
}


///Create new task
int Thread::CreateTask(Function function, char* argv)
{
	//Create a new task and allocate stack space
	Task task(memory.StackAlloc(task_stack_size));
	
	//Check whether stack allocation is successful
	if (0 == task.stack) return -1;

	//Fill the stack content
	task.psp = task.stack - psp_frame_size;
	*(StackFrame*)task.psp = StackFrame
	(
		(uint32_t)&FuncHandler,
		(uint32_t)function,
		(uint32_t)argv
	);

	return AppendTask(task);
}
EXPORT_SYMBOL(Thread::CreateTask, _ZN6Thread10CreateTaskEPFvPcES0_);


///Create new task for cpp
int Thread::CreateTaskCpp(Class *user, Method method, char* argv)
{
	//Create a new task and allocate stack space
	Task task(memory.StackAlloc(task_stack_size));
	
	//Check whether stack allocation is successful
	if (0 == task.stack) return -1;

	//Fill the stack content
	task.psp = task.stack - psp_frame_size;
	*(StackFrame*)task.psp = StackFrame
	(
		(uint32_t)&MethodHandler,
		(uint32_t)user,
		*(uint32_t*)&method,
		(uint32_t)argv
	);

	return AppendTask(task);
}
EXPORT_SYMBOL(Thread::CreateTaskCpp, _ZN6Thread13CreateTaskCppEP5ClassMS0_FvPcES2_);


///Thread delete task
int Thread::DeleteTask(int pid)
{
	if (pid <= 0) return _ERR;

	TaskNode** prevNode = &list;
	TaskNode** currNode = &list;

	while (NULL != *currNode)
	{
		if (pid == (*currNode)->task.pid)
		{
			delete *currNode;

			if (*prevNode == *currNode)
				*prevNode = (*currNode)->next;
			else
				(*prevNode)->next = (*currNode)->next;

			memory.Free((*currNode)->task.stack);

			return _OK;
		}
		else
		{
			prevNode = currNode;
			currNode = &(*currNode)->next;
		}
	}

	return _ERR;
}
EXPORT_SYMBOL(Thread::DeleteTask, _ZN6Thread10DeleteTaskEi);


///Thread wait for task
int Thread::WaitForTask(int pid)
{
	//Check if the task exists
	for (volatile TaskNode* node = list; NULL != node; node = node->next)
	{
		if (pid == node->task.pid)
		{
			//Blocking wait
			while(node->task.state != TaskState::Exited) {}
			return _OK;
		}
	}
	return _ERR;
}
EXPORT_SYMBOL(Thread::WaitForTask, _ZN6Thread11WaitForTaskEi);


///Thread sleep
void Thread::Sleep(uint32_t ticks)
{
	if(curNode->task.pid > 0)
	{
		curNode->task.state = TaskState::Suspend;
		curNode->task.ticks = System::GetSysClkCounts() + ticks;
		scheduler.Rescheduler(Scheduler::Unprivileged);
	}
}
EXPORT_SYMBOL(Thread::Sleep, _ZN6Thread5SleepEm);


///Thread Exit
void Thread::Exit()
{
	if(curNode->task.pid > 0)
	{
		curNode->task.state = TaskState::Exited;
		DeleteTask(curNode->task.pid);
		scheduler.Rescheduler(Scheduler::Unprivileged);
	}
}
EXPORT_SYMBOL(Thread::Exit, _ZN6Thread4ExitEv);


///Idle task
void Thread::IdleTask()
{
	while(1) 
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
	curNode->task.psp = psp;
}


///Get current task psp
uint32_t Thread::GetTaskPSP()
{
	return curNode->task.psp;
}


///Select next task, round-Robin scheduler
void Thread::SelectNextTask()
{
	while (1)
	{
		//Set next task as current task
		curNode = (NULL != curNode->next) ? curNode->next : list;

		//Check current task state
		if (TaskState::Suspend == curNode->task.state)
		{
			if(System::GetSysClkCounts() >= curNode->task.ticks)
			{
				curNode->task.state = TaskState::Running;
			}
		}

		//Break when task state is running
		if (TaskState::Running == curNode->task.state) break;
	}
}
