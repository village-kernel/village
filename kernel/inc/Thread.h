//###########################################################################
// Thread.h
// Declarations of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __THREAD_H__
#define __THREAD_H__

#include "stdint.h"
#include "stddef.h"

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
	//Structures
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

	struct TaskNode
	{
		Task task;
		TaskNode* next;

		TaskNode(Task task) :
			task(task),
			next(NULL)
		{}
	};

	//Static constants
	static const uint32_t start_stack = 0x20000000;
	static const uint32_t end_stack = 0x2001c000;
	static const uint32_t task_stack_szie = 1024;

	//Members
	static TaskNode* list;
	static TaskNode* curNode;

	//Methods
	static void IdleTask();
public:
	///Methods
	Thread();
	static void Initialize();
	static void CreateTask(ThreadHandlerC handler);
	static void SaveTaskPSP(uint32_t psp);
	static uint32_t GetTaskPSP();
	static uint32_t GetTaskHandler();
	static void SelectNextTask();
	static void Sleep(uint32_t ticks);
};

#endif // !__THREAD_H__
