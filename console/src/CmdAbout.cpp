//###########################################################################
// CmdAbout.cpp
// Definitions of the functions that manage command about
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "CmdAbout.h"
#include "Console.h"


///Cmd about initialize
void CmdAbout::Initialize()
{

}


///Cmd about execute
void CmdAbout::Execute(int argc, char* argv[])
{
	console.Output("vk.kernel 0.0.1(beta), Copyright (C) village.");
}


///Register cmd
REGISTER_CMD(new CmdAbout(), about);