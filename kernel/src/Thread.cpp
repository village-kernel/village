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


///Initialize static members
Thread::TaskNode* Thread::list = NULL;
Thread::TaskNode* Thread::curNode = NULL;


///Constructor
Thread::Thread()
{
}


///Thread Initialize
void Thread::Initialize()
{
	//Frist task should be idle task
	CreateTask(Thread::IdleTask);

	//Set current node
	curNode = list;
}


///Create new task
void Thread::CreateTask(ThreadHandlerC handler)
{
	//Create a new task
	Task task(handler);

	//Allocate memory space
	task.memory = Memory::Malloc(task_stack_size);
	
	//Check whether memory allocation is successful
	if (0 == task.memory) return;

	//Fill dummy stack frame
	task.psp = task.memory - psp_frame_size;
	*(StackFrame*)task.psp = StackFrame((uint32_t)handler);

	//Find an empty node
	TaskNode** nextNode = &list;
	while (NULL != *nextNode) nextNode = &(*nextNode)->next;

	//Add new task node in task list
	*nextNode = new TaskNode(task);
}


///Thread delete task
void Thread::DeleteTask(ThreadHandlerC handler)
{
	TaskNode** prevNode = &list;
	TaskNode** currNode = &list;

	while (NULL != *currNode)
	{
		if (handler == (*currNode)->task.handler)
		{
			delete *currNode;

			if (*prevNode == *currNode)
				*prevNode = (*currNode)->next;
			else
				(*prevNode)->next = (*currNode)->next;

			Memory::Free((*currNode)->task.memory, task_stack_size);

			break;
		}
		else
		{
			prevNode = currNode;
			currNode = &(*currNode)->next;
		}
	}
}


///Idle task
void Thread::IdleTask()
{
	while(1) 
	{
		__ASM("NOP");
	}
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


///Thread sleep
void Thread::Sleep(uint32_t ticks)
{
	if(Thread::IdleTask != curNode->task.handler)
	{
		curNode->task.state = TaskState::Blocked;
		curNode->task.waitToTick = System::GetSysClkCounts() + ticks;
		Scheduler::Rescheduler(Scheduler::Unprivileged);
	}
}


///Thread Exit
void Thread::Exit()
{
	if(Thread::IdleTask != curNode->task.handler)
	{
		curNode->task.state = TaskState::Exited;
		DeleteTask(curNode->task.handler);
		Scheduler::Rescheduler(Scheduler::Unprivileged);
	}
}


///Select next task
void Thread::SelectNextTask()
{
	//Check all task state
	for (volatile TaskNode* node = list; NULL != node; node = node->next)
	{
		if (TaskState::Blocked == node->task.state)
		{
			if(System::GetSysClkCounts() >= node->task.waitToTick)
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
