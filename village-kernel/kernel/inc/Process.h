
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
	//Members
	Regex regex;
	List<Data*> datum;
	List<Executor*> executors;

	//Methods
	void Taichi();
	void Listen();
	BaseExecutor* CreateExecutor(const char* path);
public:
	//Methods
	ConcreteProcess();
	~ConcreteProcess();
	void Setup();
	void Exit();
	void RegisterExecutor(Executor* executor);
	void DeregisterExecutor(Executor* executor);
	int Run(Behavior behavior, const char* args);
	int Run(Behavior behavior, const char* path, int argc, char* argv[]);
	bool Kill(const char* path);
	bool Kill(int pid);
	List<Data*> GetData();
};

#endif //!__EXECUTOR_H__
