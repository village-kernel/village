//###########################################################################
// CmdMkdir.cpp
// Definitions of the functions that manage command mkdir
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "CmdMkdir.h"
#include "Console.h"


///Cmd mkdir initialize
void CmdMkdir::Initialize()
{

}


///Cmd mkdir execute
void CmdMkdir::Execute(int argc, char* argv[])
{

}


///Register cmd
REGISTER_CMD(new CmdMkdir(), mkdir);
