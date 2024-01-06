//###########################################################################
// CmdAbout.cpp
// Definitions of the functions that manage command about
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Village.h"


/// @brief CmdAbout
class CmdAbout : public Cmd
{
public:
	/// @brief Cmd about execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		console.Output("build date      : %s", village.GetBuildDate());
		console.Output("build time      : %s", village.GetBuildTime());
		console.Output("build version   : %s", village.GetBuildVersion());
		console.Output("build gitcommit : %s", village.GetBuildGitCommit());
		console.Output("village kernel Copyright (C) village.");
	}
};


///Register cmd
REGISTER_CMD(new CmdAbout(), about);
