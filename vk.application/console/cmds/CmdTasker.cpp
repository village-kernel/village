//###########################################################################
// CmdTasker.cpp
// Definitions of the functions that manage command tasker
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Village.h"


/// @brief CmdTasker
class CmdTasker : public Cmd
{
private:
	Village village;
public:
	/// @brief Cmd tasker execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		List<Thread::Task*> tasks = village.GetTasks();
		for (tasks.Begin(); !tasks.IsEnd(); tasks.Next())
		{
			console.Output("pid %d, stack 0x%08x, psp 0x%08x, state %d, ticks %d, name %s",
							tasks.GetNid(), 
							tasks.Item()->stack,
							tasks.Item()->psp,
							tasks.Item()->state,
							tasks.Item()->ticks,
							tasks.GetName());
		}
	}
};


///Register cmd
REGISTER_CMD(new CmdTasker(), tasker);
