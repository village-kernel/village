//###########################################################################
// Thread.h
// Declarations of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __THREAD_H__
#define __THREAD_H__

#include "Defines.h"
#include "Templates.h"

///Thread
class Thread : public Class
{
public:
	//Enumerations
	enum TaskState 
	{
		Running = 0,
		Suspend,
		Blocked,
		Exited,
	};
private:
	//Structures
	struct Task 
	{
		TaskState        state;
		uint32_t         stack;
		uint32_t         ticks;
		uint32_t         psp;

		Task(uint32_t stack = 0)
			:state(TaskState::Suspend),
			stack(stack),
			ticks(0),
			psp(0)
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

		StackFrame
		(
			uint32_t pc = 0, 
			uint32_t r0 = 0,
			uint32_t r1 = 0,
			uint32_t r2 = 0,
			uint32_t r3 = 0,
			uint32_t r4 = 0,
			uint32_t r5 = 0,
			uint32_t r6 = 0,
			uint32_t r7 = 0,
			uint32_t r8 = 0,
			uint32_t r9 = 0,
			uint32_t r10 = 0,
			uint32_t r11 = 0,
			uint32_t r12 = 0
		):
			r4(r4),
			r5(r5),
			r6(r6),
			r7(r7),
			r8(r8),
			r9(r9),
			r10(r10),
			r11(r11),
			r0(r0),
			r1(r1),
			r2(r2),
			r3(r3),
			r12(r12),
			lr(0xFFFFFFFDu),
			pc(pc),
			xpsr(0x01000000u)
		{}
	};

	//Static constants
	static const uint32_t task_stack_size = 1024;
	static const uint32_t psp_frame_size = 16;
	
	//Members
	List<Task> tasks;

	//Methods
	Thread();
	static void IdleTask();
	static void FuncHandler(Function function, char* argv = NULL);
	static void MethodHandler(Class *user, Method method, char* argv = NULL);
public:
	///Methods
	void Initialize();
	void Execute();
	int CreateTask(Function function, char* argv = NULL);
	int CreateTaskCpp(Class *user, Method method, char* argv = NULL);
	int DeleteTask(int pid);
	int WaitForTask(int pid);
	void Sleep(uint32_t ticks);
	void Exit();

	//Scheduler Methods
	void SaveTaskPSP(uint32_t psp);
	uint32_t GetTaskPSP();
	void SelectNextTask();

	//Singleton Instance
	static Thread& Instance();
};

///Declarations thread reference
extern Thread& thread;

#endif // !__THREAD_H__
