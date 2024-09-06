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
		console->Println("build date      : %s", kernel->GetBuildDate());
		console->Println("build time      : %s", kernel->GetBuildTime());
		console->Println("build version   : %s", kernel->GetBuildVersion());
		console->Println("build gitcommit : %s", kernel->GetBuildGitCommit());
		console->Println("village kernel Copyright (C) village.");
	}


	/// @brief Cmd about help
	void Help()
	{
		console->Println("cmd about: display build information");
	}
};


///Register cmd
REGISTER_CMD(new CmdAbout(), about);
