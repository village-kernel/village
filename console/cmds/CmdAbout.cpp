//###########################################################################
// CmdAbout.cpp
// Definitions of the functions that manage command about
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"


/// @brief CmdAbout
class CmdAbout : public Cmd
{
public:
	/// @brief Cmd about initialize
	void Initialize()
	{

	}
	

	/// @brief Cmd about execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		console.Output("vk.kernel 0.0.1(beta), Copyright (C) village.");
	}
};


///Register cmd
REGISTER_CMD(new CmdAbout(), about);