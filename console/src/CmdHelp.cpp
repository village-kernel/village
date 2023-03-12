//###########################################################################
// CmdHelp.cpp
// Definitions of the functions that manage command help
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "CmdHelp.h"
#include "Console.h"


///Cmd help initialize
void CmdHelp::Initialize(CmdMsgMgr* msgMgr)
{
	this->msgMgr = msgMgr;
}


///Cmd help set args
void CmdHelp::SetArgs(uint8_t* args)
{

}


///Cmd help execute
void CmdHelp::Execute()
{
	msgMgr->Write((uint8_t*)"help: about\r\n");
}


///Register cmd
REGISTER_CMD(new CmdHelp(), help);
