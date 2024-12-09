//###########################################################################
// vk_process.h
// Declarations of the functions that manage process
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_PROCESS_H__
#define __VK_PROCESS_H__

#include "vk_kernel.h"
#include "vk_list.h"
#include "vk_regex.h"
#include "vk_executor.h"


/// @brief ConcreteProcess
class ConcreteProcess : public Process, public Class
{
private:
	/// @brief Members
	Regex regex;
	VkList<Data*> datum;
	VkList<Executor*> executors;

	/// @brief Methods
	void Taichi();
	void Listen();
	BaseExecutor* CreateExecutor(const char* path);
public:
	/// @brief Methods
	ConcreteProcess();
	~ConcreteProcess();
	void Setup();
	void Exit();

	/// @brief Register Methods
	void RegisterExecutor(Executor* executor);
	void UnregisterExecutor(Executor* executor);

	/// @brief Run Methods
	int Run(Behavior behavior, const char* args);
	int Run(Behavior behavior, const char* path, int argc, char* argv[]);

	/// @brief Kill Methods
	bool Kill(const char* path);
	bool Kill(int pid);

	/// @brief Data Methods
	VkList<Data*> GetData();
};

#endif //!__VK_PROCESS_H__
