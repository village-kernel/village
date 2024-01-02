//###########################################################################
// CmdDebug.cpp
// Definitions of the functions that manage command debug
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Village.h"


/// @brief CmdDebug
class CmdDebug : public Cmd
{
public:
	/// @brief Cmd debug execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 1)
		{
			console.Output("Usage: debug [level]");
			return;
		}
		village.SetDebugLevel(argv[1][0] - '0');
	}
};


///Register cmd
REGISTER_CMD(new CmdDebug(), debug);
