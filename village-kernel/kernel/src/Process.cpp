//###########################################################################
// Process.cpp
// Definitions of the functions that manage process
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Process.h"
#include "BaseExecutor.h"
#include "BinExecutor.h"
#include "ElfExecutor.h"


/// @brief Constructor
ConcreteProcess::ConcreteProcess()
{
}


/// @brief Destructor
ConcreteProcess::~ConcreteProcess()
{
}


/// @brief Process Setup
void ConcreteProcess::Setup()
{
	//Create task
	kernel->thread.CreateTask("Process", (Method)&ConcreteProcess::Execute, this);
}


/// @brief Process Execute
void ConcreteProcess::Execute()
{
	const char* taichi = "/applications/taichi.elf";
	
	if (0 > Run(Process::_Background, taichi))
	{
		kernel->debug.Error("%s execute failed", taichi);
	}

	while (1)
	{
		for (Data* data = datum.Begin(); !datum.IsEnd(); data = datum.Next())
		{
			if (false == kernel->thread.IsTaskAlive(data->tid))
			{
				kernel->thread.DeleteTask(data->tid);
				datum.Remove(data);
			}
		}
	}
}


/// @brief Process Exit
void ConcreteProcess::Exit()
{
	datum.Release();
}


/// @brief Process CreateExecutor
/// @param suffix 
/// @return 
BaseExecutor* ConcreteProcess::CreateExecutor(const char* path)
{
	char* suffix = strrchr(path, '.');

	if (0 == strcmp(suffix, ".bin"))
	{
		return new BinExecutor();
	}
	else if (0 == strcmp(suffix, ".elf"))
	{
		return new ElfExecutor();
	}
	return NULL;
}


/// @brief Process Run
/// @param behavior 
/// @param args 
/// @return 
int ConcreteProcess::Run(Behavior behavior, const char* args)
{
	//Split args
	regex.Split(args);

	//Set argc and argv
	int    argc = regex.Size();
	char** argv = regex.ToArray();

	//Run with argc and argv
	return Run(behavior, argv[0], argc, argv);
}


/// @brief Process Run
/// @param behavior 
/// @param path 
/// @param argc 
/// @param argv 
/// @return 
int ConcreteProcess::Run(Behavior behavior, const char* path, int argc, char* argv[])
{
	//New data object
	Data* data = new Data((char*)path); 
	
	//Create executor
	if ((data->exec = CreateExecutor(path)) == NULL) 
	{
		delete data;
		return -1;
	}

	//Run executor with args
	if ((data->tid = data->exec->Run(path, argc, argv)) < 0)
	{
		delete data;
		return -1;
	}
	
	//Add to datum list
	if ((data->pid = datum.Add(data, (char*)path)) < 0)
	{
		delete data;
		return -1;
	}
	
	//Wait for task done
	if (behavior == _Foreground)
	{
		data->exec->Wait();
	}
	
	return data->pid;
}


/// @brief Process Kill
/// @param path 
/// @return 
bool ConcreteProcess::Kill(const char* path)
{
	return datum.GetItemByName(path)->exec->Kill();
}


/// @brief Process Kill
/// @param pid 
/// @return 
bool ConcreteProcess::Kill(int pid)
{
	return datum.GetItem(pid)->exec->Kill();
}


/// @brief GetExecutors
/// @return 
List<ConcreteProcess::Data*> ConcreteProcess::GetData()
{
	return datum;
}
