//###########################################################################
// CmdHelp.cpp
// Definitions of the functions that manage command help
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"


/// @brief CmdHelp
class CmdHelp : public Cmd
{
public:
	/// @brief Cmd help initialize
	void Initialize()
	{

	}


	/// @brief Cmd help execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		console.Output("help: about");
	}
};


///Register cmd
REGISTER_CMD(new CmdHelp(), help);
