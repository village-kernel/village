//###########################################################################
// CmdAbout.cpp
// Definitions of the functions that manage command about
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Kernel.h"


/// @brief CmdAbout
class CmdAbout : public Cmd
{
public:
	/// @brief Cmd about execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		console.Output("build date      : %s", kernel->GetBuildDate());
		console.Output("build time      : %s", kernel->GetBuildTime());
		console.Output("build version   : %s", kernel->GetBuildVersion());
		console.Output("build gitcommit : %s", kernel->GetBuildGitCommit());
		console.Output("village kernel Copyright (C) village.");
	}
};


///Register cmd
REGISTER_CMD(new CmdAbout(), about);
