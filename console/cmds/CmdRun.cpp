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
public:
	/// @brief Initialize
	/// @param msgMgr 
	void Initialize()
	{
		
	}


	///Cmd Run execute
	void Execute(int argc, char* argv[])
	{
		if (argc < 2)
		{
			console.Output("Usage: run [program] <arg1> <arg2> <...>");
			return;
		}
		executor.Run(argv[1], argc, argv);
	}
};


///Register cmd
REGISTER_CMD(new CmdRun(), run);
