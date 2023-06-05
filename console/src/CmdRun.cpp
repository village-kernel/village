//###########################################################################
// CmdRun.cpp
// Definitions of the functions that manage command Run
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "CmdRun.h"
#include "Console.h"
#include "string.h"


/// @brief Initialize
/// @param msgMgr 
void CmdRun::Initialize()
{
	
}


///Cmd Run execute
void CmdRun::Execute(int argc, char* argv[])
{
	if (argc < 2)
	{
		console.output("Usage: run [program] <arg1> <arg2> <...>");
		return;
	}
	executor.Run(argv[1], argc, argv);
}


///Register cmd
REGISTER_CMD(new CmdRun(), run);
