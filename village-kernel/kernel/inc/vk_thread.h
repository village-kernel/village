//###########################################################################
// vk_thread.h
// Declarations of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_THREAD_H__
#define __VK_THREAD_H__

#include "vk_kernel.h"
#include "vk_registers.h"
#include "vk_cast.h"
#include "vk_list.h"


#ifndef TASK_STACK
#define TASK_STACK      1024
#endif


/// @brief ConcreteThread
class ConcreteThread : public Thread, public Class
{
private:
	/// @brief Static constants
	static const uint32_t task_stack_size = TASK_STACK;
	static const uint32_t psp_frame_size = sizeof(TaskContext);
	
	/// @brief Members
	VkList<Task*> tasks;
	Memory*       memory;
	System*       system;
	Scheduler*    scheduler;

	/// @brief Members
	void TaskHandler(Function function, void* user, void* args);
public:
	/// @brief Methods
	ConcreteThread();
	~ConcreteThread();
	void Setup();
	void Start();
	void Exit();

	/// @brief Create Methods
	int CreateTask(const char* name, Function function, void* user = NULL, void* args = NULL);
	int CreateTask(const char* name, Method method, Class *user, void* args = NULL);

	/// @brief Task Methods
	bool StartTask(int tid);
	bool StopTask(int tid);
	bool WaitForTask(int tid);
	bool DeleteTask(int tid);
	bool IsTaskAlive(int tid);
	VkList<Task*> GetTasks();

	/// @brief State Methods
	void ChangeState(TaskState state);
	void Sleep(uint32_t ticks);
	void Blocked();
	void TaskExit();

	/// @brief Scheduler Methods
	void SaveTaskPSP(uint32_t psp);
	uint32_t GetTaskPSP();
	void SelectNextTask();
	void IdleTask();
};

#endif // !__VK_THREAD_H__
