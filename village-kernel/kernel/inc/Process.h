
//###########################################################################
// Process.h
// Declarations of the functions that manage process
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "Kernel.h"
#include "List.h"
#include "Regex.h"
#include "Executor.h"


/// @brief ConcreteProcess
class ConcreteProcess : public Process, public Class
{
private:
	/// @brief Members
	Regex regex;
	List<Data*> datum;
	List<Executor*> executors;

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
	void DeregisterExecutor(Executor* executor);

	/// @brief Run Methods
	int Run(Behavior behavior, const char* args);
	int Run(Behavior behavior, const char* path, int argc, char* argv[]);

	/// @brief Kill Methods
	bool Kill(const char* path);
	bool Kill(int pid);

	/// @brief Data Methods
	List<Data*> GetData();
};

#endif //!__EXECUTOR_H__
