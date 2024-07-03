//###########################################################################
// CmdProcess.cpp
// Definitions of the functions that manage command process
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Kernel.h"


/// @brief CmdProcess
class CmdProcess : public Cmd
{
public:
	/// @brief Cmd ps execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		List<Process::Data*> data = kernel->process.GetData();

		for (data.Begin(); !data.IsEnd(); data.Next())
		{
			console.Output("pid %d, tid %d, name %s", 
							data.Item()->pid,
							data.Item()->tid,
							data.Item()->name);
		}
	}


	/// @brief Cmd ps help
	void Help()
	{
		console.Output("cmd ps: list process data");
	}
};


///Register cmd
REGISTER_CMD(new CmdProcess(), ps);
