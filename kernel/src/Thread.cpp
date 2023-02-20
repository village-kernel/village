//###########################################################################
// Thread.cpp
// Definitions of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Thread.h"
#include "Scheduler.h"


///Initialize static members
unsigned int Thread::storedIndex = 0;
unsigned int Thread::taskIndex = 0;
Thread::Task Thread::tasks[Thread::task_number_size];


///Constructor
Thread::Thread()
{
}


///Idle task
static void IdleTask(void) { while(1) { __ASM("NOP"); } }


///Create new task
void Thread::CreateTask(ThreadHandlerC handler)
{
	//Check
	if(storedIndex >= task_number_size) return;

	//Init idle if it is not found
	if (handler != &IdleTask)
	{
		if (tasks[0].handler != IdleTask)
		{
			CreateTask(IdleTask);
		}
	}

	//Calculate new task psp
	uint32_t *psp = (uint32_t*)(end_stack - (storedIndex + 1) * task_stack_szie);

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

	//Stored task info
	tasks[storedIndex].psp = (uint32_t)psp;
	tasks[storedIndex].handler = handler;
	tasks[storedIndex].state = TaskState::Running;
	storedIndex++;
}


///Save task PSP
void Thread::SaveTaskPSP(uint32_t psp)
{
	tasks[taskIndex].psp = psp;
}


///Get current task psp
uint32_t Thread::GetTaskPSP()
{
	return tasks[taskIndex].psp;
}


///Get currenttask handler
uint32_t Thread::GetTaskHandler()
{
	return (uint32_t)tasks[taskIndex].handler;
}


///Thread sleep
void Thread::Sleep(uint32_t ticks)
{
	if(taskIndex)
	{
		tasks[taskIndex].state = TaskState::Blocked;
		tasks[taskIndex].waitToTick = Scheduler::GetSysTicks() + ticks;
		Scheduler::Rescheduler(Scheduler::Unprivileged);
	}
}


///Select next task
void Thread::SelectNextTask()
{
	//Check all task state
	for(uint32_t i = 0; i < storedIndex; i++) 
	{
		if(tasks[i].state == TaskState::Blocked) 
		{
			if(Scheduler::GetSysTicks() >= tasks[i].waitToTick)
			{
				tasks[i].state = TaskState::Running;
			}
		}
	}

	//Round-Robin scheduler
	while (1)
	{
		if (++taskIndex >= storedIndex) taskIndex = 0;

		if(tasks[taskIndex].state == TaskState::Running) break;
	}
}
