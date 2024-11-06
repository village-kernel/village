//###########################################################################
// vk_cmd_help.cpp
// Definitions of the functions that manage command help
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_cmd.h"
#include "vk_console.h"
#include "vk_kernel.h"


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
