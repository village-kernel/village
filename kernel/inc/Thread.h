//###########################################################################
// Thread.h
// Declarations of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __THREAD_H__
#define __THREAD_H__

#include "Kernel.h"

extern "C" 
{
void IdleTask(void);
void Task0(void);
void Task1(void);

void StartScheduler(void);
}


///Thread
class Thread
{
private:
	enum TaskState 
	{
		Running = 0,
		Blocked = 1,
	};

    enum Access
    {
        Unprivileged = 0,
        Privileged = 1,
    };

	struct Task 
	{
		void (*handler)(void);
		TaskState state;
		uint32_t psp;
		uint32_t waitToTick;

		Task()
			:handler(0),
			state(TaskState::Running),
			psp(0),
			waitToTick(0)
		{}
	};

    //Static constants
    static const unsigned int end_stack = 0x2001c000;
	static const unsigned int task_number_size = 16;
	static const unsigned int task_stack_szie = 1024;

    //Members
    static unsigned int storedIndex;
   	static unsigned int taskIndex;
	static unsigned int sysTicks;
	static Task tasks[task_number_size];

    //Methods
    static void Rescheduler(Access access);
public:
    ///Methods
    Thread();
    static void CreateTask(void (*handler)());
    static void SaveTaskPSP(uint32_t psp);
    static uint32_t GetTaskPSP();
    static uint32_t GetTaskHandler();
    static void SelectNextTask();
    static void Sleep(uint32_t ticks);
    static void SystickCount();
    static void TaskOperator(uint32_t* SP);
};

#endif // !__THREAD_H__
