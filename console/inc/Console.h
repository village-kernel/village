//###########################################################################
// Console.h
// Declarations of the functions that manage console
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "Module.h"
#include "CmdDefines.h"
#include "CmdMsgMgr.h"

///Console
class Console : public Module
{
private:
	//Function definitions
	typedef void (Console::*Func)(CmdMsg);
	static struct FuncMap { Cmd cmd; Func func; } funcmap[];

	//Members
	CmdMsgMgr msgMgr;

	//Methods
	void ExecuteCmd(CmdMsg msg);
	void About(CmdMsg msg);
public:
	//Methods
	Console();
	void Initialize();
	void Execute();
};

#endif // !__CONSOLE_H__
