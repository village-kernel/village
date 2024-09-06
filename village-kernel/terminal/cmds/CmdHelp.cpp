//###########################################################################
// CmdHelp.cpp
// Definitions of the functions that manage command help
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Kernel.h"


/// @brief CmdHelp
class CmdHelp : public Cmd
{
public:
	/// @brief Cmd help execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		List<Cmd*> cmds = kernel->terminal.GetCmds();

		for (Cmd* cmd = cmds.Begin(); !cmds.IsEnd(); cmd = cmds.Next())
		{
			cmd->Setup(console);
			cmd->Help();
			cmd->Exit();
		}
	}


	/// @brief Cmd help help
	void Help()
	{
		console->Println("cmd help: display cmd help");
	}
};


///Register cmd
REGISTER_CMD(new CmdHelp(), help);
