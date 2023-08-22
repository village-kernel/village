//###########################################################################
// CmdRemove.cpp
// Definitions of the functions that manage command remove
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "CmdRemove.h"
#include "Console.h"


///Cmd remove initialize
void CmdRemove::Initialize()
{

}


///Cmd remove execute
void CmdRemove::Execute(int argc, char* argv[])
{
	
}


///Register cmd
REGISTER_CMD(new CmdRemove(), rm);
