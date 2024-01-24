//###########################################################################
// CmdRun.cpp
// Definitions of the functions that manage command Run
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Executor.h"
#include "string.h"


///CmdRun
class CmdRun : public Cmd
{
private:
	//Members
	Executor executor;
	Executor::Behavior behavior;
public:
	/// @brief Constructor
	CmdRun() :behavior(Executor::_Foreground) {}

	/// @brief Cmd Run execute
	void Execute(int argc, char* argv[])
	{
		int i = 0;

		if (argc < 2)
		{
			console.Output("Usage: run [-b] <program> [arg1] [arg2] [...]");
			return;
		}

		behavior = Executor::_Foreground;

		for (i = 1; i < argc; i++)
		{
			if (0 == strcmp(argv[i], "-b"))
			{
				behavior = Executor::_Background;
				break;
			}
		}

		executor.Run(behavior, argv[i + 1], argc, argv);
	}
};


///Register cmd
REGISTER_CMD(new CmdRun(), run);
