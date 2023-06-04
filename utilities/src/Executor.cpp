//###########################################################################
// Executor.cpp
// Definitions of the functions that manage executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Executor.h"


/// @brief Constructor
Executor::Executor()
{
}


/// @brief Deconstructor
Executor::~Executor()
{
}


/// @brief Executor Initialize
/// @param path elf file path
/// @param argv running argv
/// @return result
int Executor::Run(const char* path, char* argv[])
{
	//Load, parser and execute elf file
	if (elf.Load(path) != Result::_OK) return _ERR;
	
	//Create a sandboxed thread to run the app
	int pid = thread.CreateTaskCpp(this, (Method)&Executor::Sandbox);

	//Wait for task done
	return thread.WaitForTask(pid);
}


/// @brief Executor execute app
void Executor::Sandbox()
{
	elf.InitArray();
	elf.Execute();
	elf.FiniArray();
	elf.Exit();
}
