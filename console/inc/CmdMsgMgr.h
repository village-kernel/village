//###########################################################################
// CmdMsgMgr.h
//
// Decodes incoming bytes into messages and Encodes outgoing messages
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __COMMAND_MSG_MGR_H__
#define __COMMAND_MSG_MGR_H__

#include "System.h"
#include "CmdDefines.h"

//CmdMsg struct
struct CmdMsg
{
	uint8_t  cmd;
	uint8_t* args;
};


///CmdMsg
class CmdMsgMgr
{
private:
	//Members
	CmdMsg rxMsg;
public:
	//Methods
	CmdMsgMgr();
	void Initialize();
	bool Execute();
	void Write(uint8_t* txMsg);

	///Gets the decoded message
	inline CmdMsg Read() { return rxMsg; }
};

#endif //!__COMMAND_MSG_MGR_H__
