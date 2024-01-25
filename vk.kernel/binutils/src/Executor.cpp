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
	:pid(0),
	argc(0),
	argv(NULL)
{
}


/// @brief Deconstructor
Executor::~Executor()
{
	regex.Clear();
}


/// @brief Executor Initialize
/// @param args run args
/// @return pid
int Executor::Run(Behavior behavior, const char* args)
{
	//Split args
	regex.Split(args);

	//Set argc and argv
	int    argc = regex.Size();
	char** argv = regex.ToArray();

	//Run with argc and argv
	return Run(behavior, argv[0], argc, argv);
}


/// @brief Executor Initialize
/// @param path elf file path
/// @param argv running argv
/// @return pid
int Executor::Run(Behavior behavior, const char* path, int argc, char* argv[])
{
	//Set argc and argv
	this->argc = argc;
	this->argv = argv;

	//Load, parser and execute elf file
	if (elf.Load(path) != Result::_OK) return _ERR;
	
	//Create a sandboxed thread to run the app
	pid = Kernel::thread.CreateTask(path, (Method)&Executor::Sandbox, this);

	//Wait for task done
	if (behavior == _Foreground) Kernel::thread.WaitForTask(pid);

	return pid;
}


/// @brief Executor wait
/// @return result
int Executor::Wait()
{
	return Kernel::thread.WaitForTask(pid);
}


/// @brief Executor execute app
void Executor::Sandbox()
{
	elf.Execute(NULL, argc, argv);
	elf.Exit();
}
