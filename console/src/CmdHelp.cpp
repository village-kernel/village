//###########################################################################
// CmdHelp.cpp
// Definitions of the functions that manage command help
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "CmdHelp.h"
#include "Console.h"


///Cmd help initialize
void CmdHelp::Initialize()
{

}


///Cmd help execute
void CmdHelp::Execute(int argc, char* argv[])
{
	console.output("help: about\r\n");
}


///Register cmd
REGISTER_CMD(new CmdHelp(), help);
