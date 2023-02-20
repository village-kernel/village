//###########################################################################
// Thread.h
// Declarations of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __THREAD_H__
#define __THREAD_H__

#include "System.h"

///Thread end point
class ThreadEndpoint {};
typedef void (ThreadEndpoint::*ThreadHandlerCpp)();
typedef void (*ThreadHandlerC)();

///Thread
class Thread
{
public:
	//Enumerations
	enum TaskState 
	{
		Running = 0,
		Blocked = 1,
	};
private:
	struct Task 
	{
		ThreadHandlerC handler;
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
	static Task tasks[task_number_size];
public:
	///Methods
	Thread();
	static void CreateTask(ThreadHandlerC handler);
	static void SaveTaskPSP(uint32_t psp);
	static uint32_t GetTaskPSP();
	static uint32_t GetTaskHandler();
	static void SelectNextTask();
	static void Sleep(uint32_t ticks);
};

#endif // !__THREAD_H__
