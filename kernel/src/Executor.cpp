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
	int pid = Thread::Instance().CreateTaskCpp(this, (ThreadHandlerCpp)&Executor::Sandbox);

	//Wait for task done
	return Thread::Instance().WaitForTask(pid);
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
