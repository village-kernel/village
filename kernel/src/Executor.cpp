//###########################################################################
// Executor.cpp
// Definitions of the functions that manage executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Executor.h"


///Executor Initialize
int Executor::Run(const char* path, char* argv[])
{
	//Load, parser and execute elf file
	if (elf.Load(path) != Result::_OK) return _ERR;
	
	//Create a sandboxed thread to run the app
	int pid = thread.CreateTaskCpp(this, (Method)&Executor::Sandbox);

	//Wait for task done
	return thread.WaitForTask(pid);
}


///Executor execute app
void Executor::Sandbox()
{
	elf.InitArray();
	elf.Execute();
	elf.FiniArray();
	elf.Exit();
}


///Register module
REGISTER_MODULE(new Executor(), ModuleID::_executor, executor);
