//###########################################################################
// Thread.h
// Declarations of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __THREAD_H__
#define __THREAD_H__

#include "Defines.h"
#include "Registers.h"
#include "Templates.h"

#ifndef TASK_STACK
#define TASK_STACK      1024
#endif

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
private:
	//Static constants
	static const uint32_t task_stack_size = TASK_STACK;
	static const uint32_t psp_frame_size = sizeof(TaskContext) >> 2;
	
	//Members
	List<Task*> tasks;

	//Methods
	void IdleTask();
	void TaskHandler(Function function, void* user = NULL, void* args = NULL);
public:
	///Methods
	Thread();
	~Thread();
	void Initialize();
	void Execute();
	int CreateTask(const char* name, Function function, void* user = NULL, void* args = NULL);
	int CreateTask(const char* name, Method method, Class *user, void* args = NULL);
	int DeleteTask(int pid);
	int WaitForTask(int pid);
	List<Task*> GetTasks();
	void Sleep(uint32_t ticks);
	void Exit();

	//Scheduler Methods
	void SaveTaskPSP(uint32_t psp);
	uint32_t GetTaskPSP();
	void SelectNextTask();
};

#endif // !__THREAD_H__
