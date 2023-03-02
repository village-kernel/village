//###########################################################################
// CmdHelp.h
// Declarations of the functions that manage command help
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_HELP_H__
#define __CMD_HELP_H__

#include "CmdMsgMgr.h"

///CmdHelp
class CmdHelp
{
private:
	//Members
	CmdMsgMgr* msgMgr;
public:
	//Methods
	void Initialize(CmdMsgMgr* msgMgr);
	void SetArgs(uint8_t* args);
	void Execute();
};

#endif // !__CMD_HELP_H__
