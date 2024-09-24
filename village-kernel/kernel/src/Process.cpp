//###########################################################################
// Process.cpp
// Definitions of the functions that manage process
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Process.h"
#include "BaseExecutor.h"


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
	//Create a running taichi application task
	kernel->thread.CreateTask("Process::Taichi", (Method)&ConcreteProcess::Taichi, this);

	//Create a listening thread alive task
	kernel->thread.CreateTask("Process::Listen", (Method)&ConcreteProcess::Listen, this);

	//Output debug info
	kernel->debug.Info("Process setup done!");
}


/// @brief Process Taichi
void ConcreteProcess::Taichi()
{
	const char* taichi = "/applications/taichi.exec";
	
	if (0 > Run(Process::_Background, taichi))
	{
		kernel->debug.Error("%s execute failed", taichi);
	}
}


/// @brief Process Listen
void ConcreteProcess::Listen()
{
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
		kernel->thread.Sleep(1);
	}
}


/// @brief Process Exit
void ConcreteProcess::Exit()
{
	datum.Release();
	executors.Release();
}


/// @brief Register executor object
/// @param executor executor pointer
void ConcreteProcess::RegisterExecutor(Executor* executor)
{
	executors.Add(executor);
}


/// @brief Unregister executor object
/// @param executor executor pointer
void ConcreteProcess::UnregisterExecutor(Executor* executor)
{
	executors.Remove(executor);
}


/// @brief Process CreateExecutor
/// @param suffix 
/// @return 
BaseExecutor* ConcreteProcess::CreateExecutor(const char* path)
{
	char* suffix = strrchr(path, '.');

	for (executors.Begin(); !executors.IsEnd(); executors.Next())
	{
		List<char*> suffixes = executors.Item()->GetSuffixes();

		for (suffixes.Begin(); !suffixes.IsEnd(); suffixes.Next())
		{
			if (0 == strcmp(suffix, suffixes.Item()))
			{
				return executors.Item()->Create();
			}
		}
	}
	
	kernel->debug.Error("No associated executor found");
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
	return datum.GetItem(path)->exec->Kill();
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
