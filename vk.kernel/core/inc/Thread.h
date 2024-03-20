//###########################################################################
// Thread.h
// Declarations of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __THREAD_H__
#define __THREAD_H__

#include "Component.h"
#include "Registers.h"
#include "List.h"


/// @brief Thread
class Thread : public Component
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
		char*            name;
		uint32_t         pid;
		uint32_t         psp;
		uint32_t         ticks;
		uint32_t         stack;
		TaskState        state;
		
		Task(uint32_t stack = 0, char* name = NULL)
			:name(name),
			pid(-1),
			psp(0),
			ticks(0),
			stack(stack),
			state(TaskState::Suspend)
		{}
	};
public:
	///Methods
	virtual int CreateTask(const char* name, Function function, void* user = NULL, void* args = NULL) = 0;
	virtual int CreateTask(const char* name, Method method, Class *user, void* args = NULL) = 0;
	virtual int DeleteTask(int pid) = 0;
	virtual bool WaitForTask(int pid) = 0;
	virtual List<Task*> GetTasks() = 0;
	virtual void Sleep(uint32_t ticks) = 0;
	virtual void TaskExit() = 0;

	//Scheduler Methods
	virtual void SaveTaskPSP(uint32_t psp) = 0;
	virtual uint32_t GetTaskPSP() = 0;
	virtual void SelectNextTask() = 0;
	virtual void IdleTask() = 0;
};

#endif // !__THREAD_H__
