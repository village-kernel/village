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
private:
	//Members
	uint8_t* name;
protected:
	//Members
	CmdMsgMgr* msgMgr;
public:
	//Methods
	virtual void Initialize(CmdMsgMgr* msgMgr) = 0;
	virtual void SetArgs(uint8_t* args)        = 0;
	virtual void Execute()                     = 0;

	///Set the cmd name
	inline void SetName(uint8_t* name) { this->name = name; }
	
	///Get the cmd name
	inline uint8_t* GetName() { return name; } 
};

#endif //!__CMD_INTERFACE_H__
