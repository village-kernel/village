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


///Initialize static members
int Thread::pidCounter = 0;
Thread::TaskNode* Thread::list = NULL;
Thread::TaskNode* Thread::curNode = NULL;


///Constructor
Thread::Thread()
{
}


///Thread Initialize
void Thread::Initialize()
{
	//Frist task should be idle task and the pid is 0
	CreateTask((ThreadHandler)&Thread::IdleTask);

	//Set current node
	curNode = list;
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
int Thread::CreateTask(ThreadHandler handler, int argc, char* argv[])
{
	//Create a new task
	Task task(handler);

	//Allocate stack space
	task.stack = Memory::StackAlloc(task_stack_size);
	
	//Check whether stack allocation is successful
	if (0 == task.stack) return -1;

	//Fill the stack content
	task.psp = task.stack - psp_frame_size;
	*(StackFrame*)task.psp = StackFrame
	(
		(uint32_t)&TaskHandlerC,
		(uint32_t)handler,
		(uint32_t)argc,
		(uint32_t)argv
	);

	return AppendTask(task);
}
EXPORT_SYMBOL(Thread::CreateTask, _ZN6Thread10CreateTaskEPFviPPcEiS1_);


///Create new task for cpp
int Thread::CreateTaskCpp(ThreadEndpoint *user, ThreadHandlerCpp handler, int argc, char* argv[])
{
	//Create a new task
	Task task(user, handler);

	//Allocate stack space
	task.stack = Memory::StackAlloc(task_stack_size);
	
	//Check whether stack allocation is successful
	if (0 == task.stack) return -1;

	//Fill the stack content
	task.psp = task.stack - psp_frame_size;
	*(StackFrame*)task.psp = StackFrame
	(
		(uint32_t)&TaskHandlerCpp, 
		(uint32_t)user, 
		*(uint32_t*)&handler,
		(uint32_t)argc,
		(uint32_t)argv	
	);

	return AppendTask(task);
}
EXPORT_SYMBOL(Thread::CreateTaskCpp, _ZN6Thread13CreateTaskCppEP14ThreadEndpointMS0_FviPPcEiS3_);


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

			Memory::Free((*currNode)->task.stack);

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
		curNode->task.state = TaskState::Blocked;
		curNode->task.ticks = System::GetSysClkCounts() + ticks;
		Scheduler::Rescheduler(Scheduler::Unprivileged);
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
		Scheduler::Rescheduler(Scheduler::Unprivileged);
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


///Thread task handler C
void Thread::TaskHandlerC(ThreadHandler handler, int argc, char* argv[])
{
	if (NULL != handler)
	{
		(handler)(argc, argv);
	}
	Exit();
}


///Thread task handler Cpp
void Thread::TaskHandlerCpp(ThreadEndpoint *user, ThreadHandlerCpp handler, int argc, char* argv[])
{
	if (NULL != user && NULL != handler)
	{
		(user->*handler)(argc, argv);
	}
	Exit();
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


///Get currenttask handler
uint32_t Thread::GetTaskHandler()
{
	return (uint32_t)curNode->task.handler;
}


///Select next task
void Thread::SelectNextTask()
{
	//Check all task state
	for (volatile TaskNode* node = list; NULL != node; node = node->next)
	{
		if (TaskState::Blocked == node->task.state)
		{
			if(System::GetSysClkCounts() >= node->task.ticks)
			{
				node->task.state = TaskState::Running;
			}
		}
	}

	//Round-Robin scheduler
	while (1)
	{
		if (NULL != curNode->next)
		{
			curNode = curNode->next;
		}
		else
		{
			curNode = list;
		}

		if(curNode->task.state == TaskState::Running) break;
	}
}
