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
		Exited  = 2,
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

	struct StackFrame
	{
		uint32_t r4;
		uint32_t r5;
		uint32_t r6;
		uint32_t r7;
		uint32_t r8;
		uint32_t r9;
		uint32_t r10;
		uint32_t r11;
		uint32_t r0;
		uint32_t r1;
		uint32_t r2;
		uint32_t r3;
		uint32_t r12;
		uint32_t lr;
		uint32_t pc;
		uint32_t xpsr;

		StackFrame(uint32_t pc = 0):
			r4(0),
			r5(0),
			r6(0),
			r7(0),
			r8(0),
			r9(0),
			r10(0),
			r11(0),
			r0(0),
			r1(0),
			r2(0),
			r3(0),
			r12(0),
			lr(0xFFFFFFFDu),
			pc(pc),
			xpsr(0x01000000u)
		{}
	};

	//Static constants
	static const uint32_t start_stack = 0x20000000;
	static const uint32_t end_stack = 0x2001c000;
	static const uint32_t task_stack_szie = 1024;
	static const uint32_t psp_frame_size = 16;

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
	static void DeleteTask(ThreadHandlerC handler);
	static void SaveTaskPSP(uint32_t psp);
	static uint32_t GetTaskPSP();
	static uint32_t GetTaskHandler();
	static void SelectNextTask();
	static void Sleep(uint32_t ticks);
	static void Exit();
};

#endif // !__THREAD_H__
