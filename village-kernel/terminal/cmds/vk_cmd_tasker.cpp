//###########################################################################
// vk_cmd_tasker.cpp
// Definitions of the functions that manage command tasker
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_cmd.h"
#include "vk_console.h"
#include "vk_kernel.h"


/// @brief CmdTasker
class CmdTasker : public Cmd
{
public:
	/// @brief Cmd tasker execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		List<Thread::Task*> tasks = kernel->thread.GetTasks();
		for (tasks.Begin(); !tasks.IsEnd(); tasks.Next())
		{
			console->Println("tid %d, stack 0x%08x, psp 0x%08x, state %d, ticks %10d, name %s",
							tasks.Item()->tid, 
							tasks.Item()->stack,
							tasks.Item()->psp,
							tasks.Item()->state,
							tasks.Item()->ticks,
							tasks.Item()->name);
		}
	}


	/// @brief Cmd tasker help
	void Help()
	{
		console->Println("cmd ts: list thread task");
	}
};


///Register cmd
REGISTER_CMD(new CmdTasker(), ts);
