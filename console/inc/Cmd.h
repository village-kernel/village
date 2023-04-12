//###########################################################################
// Cmd.h
// Specifies the interface for all classes that contain command
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_INTERFACE_H__
#define __CMD_INTERFACE_H__

#include "stdint.h"
#include "stddef.h"
#include "CmdMsgMgr.h"

///Cmd
class Cmd
{
protected:
	//Members
	CmdMsgMgr* msgMgr;
public:
	//Constructor
	Cmd() {}
	
	//Deconstructor
	virtual ~Cmd() {};

	//Methods
	virtual void Initialize(CmdMsgMgr* msgMgr) = 0;
	virtual void SetArgs(uint8_t* args)        = 0;
	virtual void Execute()                     = 0;
};

#endif //!__CMD_INTERFACE_H__
