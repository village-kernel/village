//###########################################################################
// CmdTasker.cpp
// Definitions of the functions that manage command tasker
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Kernel.h"
#include "string.h"
#include "stdlib.h"


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
			console.Output("pid %d, stack 0x%08x, psp 0x%08x, state %d, ticks %d, name %s",
							tasks.Item()->pid, 
							tasks.Item()->stack,
							tasks.Item()->psp,
							tasks.Item()->state,
							tasks.Item()->ticks,
							tasks.Item()->name);
		}
	}
};


/// @brief CmdKill
class CmdKill : public Cmd
{
public:
	/// @brief Cmd kill execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc >= 2 && 0 == strcmp("-c", argv[1]))
		{
			kernel->thread.DeleteTask(atoi(argv[2]));
		}
		else
		{
			console.Output("Usage: kill -c <pid>");
		}
	}
};


///Register cmd
REGISTER_CMD(new CmdTasker(), tasker);
REGISTER_CMD(new CmdKill(),   kill  );
