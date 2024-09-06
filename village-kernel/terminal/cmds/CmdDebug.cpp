//###########################################################################
// CmdDebug.cpp
// Definitions of the functions that manage command debug
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Kernel.h"


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
			console->Println("Usage: debug [level]");
			return;
		}
		kernel->debug.SetDebugLevel(argv[1][0] - '0');
	}


	/// @brief Cmd debug help
	void Help()
	{
		console->Println("cmd debug: settings debug output level");
	}
};


///Register cmd
REGISTER_CMD(new CmdDebug(), debug);
