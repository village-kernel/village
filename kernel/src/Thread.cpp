//###########################################################################
// Thread.cpp
// Definitions of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Thread.h"
#include "System.h"
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
	TaskNode** nextNode = &list;
	uint32_t index = 0;

	//Find an empty node
	while (NULL != *nextNode)
	{
		nextNode = &(*nextNode)->next;
		index++;
	}

	//Calculate new task psp
	uint32_t *psp = (uint32_t*)(end_stack - (index + 1) * task_stack_szie);

	//Check whether the stack has enough space
	if ((uint32_t)psp <= (start_stack + task_stack_szie)) return;

	//Fill dummy stack frame
	*(--psp) = 0x01000000u; // Dummy xPSR, just enable Thumb State bit;
	*(--psp) = (uint32_t)handler; // PC
	*(--psp) = 0xFFFFFFFDu; // LR with EXC_RETURN to return to Thread using PSP
	*(--psp) = 0x0; // Dummy R12
	*(--psp) = 0x0; // Dummy R3
	*(--psp) = 0x0; // Dummy R2
	*(--psp) = 0x0; // Dummy R1
	*(--psp) = 0x0; // Dummy R0
	*(--psp) = 0x0; // Dummy R11
	*(--psp) = 0x0; // Dummy R10
	*(--psp) = 0x0; // Dummy R9
	*(--psp) = 0x0; // Dummy R8
	*(--psp) = 0x0; // Dummy R7
	*(--psp) = 0x0; // Dummy R6
	*(--psp) = 0x0; // Dummy R5
	*(--psp) = 0x0; // Dummy R4

	//Add new task node in task list
	Task task;
	task.handler = handler;
	task.state = TaskState::Running;
	task.psp = (uint32_t)psp;
	*nextNode = new TaskNode(task);
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
