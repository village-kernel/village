//###########################################################################
// CmdKill.cpp
// Definitions of the functions that manage command kill
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Kernel.h"
#include "string.h"
#include "stdlib.h"


/// @brief CmdKill
class CmdKill : public Cmd
{
public:
	/// @brief Cmd kill execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc >= 2)
		{
			if (0 == strcmp("-p", argv[1]))
			{
				kernel->process.Kill(atoi(argv[2]));
			}
			else if (0 == strcmp("-t", argv[1]))
			{
				kernel->thread.DeleteTask(atoi(argv[2]));
			}
		}
		else
		{
			console->Output("Usage: ");
			console->Output("kill -p <pid>");
			console->Output("kill -t <tid>");
		}
	}


	/// @brief Cmd kill help
	void Help()
	{
		console->Output("cmd kill: kill process");
	}
};


///Register cmd
REGISTER_CMD(new CmdKill(), kill);
