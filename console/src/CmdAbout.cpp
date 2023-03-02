//###########################################################################
// CmdAbout.cpp
// Definitions of the functions that manage command about
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "CmdAbout.h"


///Cmd about initialize
void CmdAbout::Initialize(CmdMsgMgr* msgMgr)
{
	this->msgMgr = msgMgr;
}


///Cmd about set args
void CmdAbout::SetArgs(uint8_t* args)
{

}


///Cmd about execute
void CmdAbout::Execute()
{
	msgMgr->Write((uint8_t*)"vk.kernel 0.0.1(beta), Copyright (C) village.\r\n");
}
