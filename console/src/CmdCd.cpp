//###########################################################################
// CmdCd.cpp
// Definitions of the functions that manage command change directory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "CmdCd.h"
#include "Console.h"


///Cmd cd initialize
void CmdCd::Initialize()
{

}


///Cmd cd execute
void CmdCd::Execute(int argc, char* argv[])
{
	
}


///Register cmd
REGISTER_CMD(new CmdCd(), cd);
