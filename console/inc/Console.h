//###########################################################################
// Console.h
// Declarations of the functions that manage console
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "Module.h"
#include "Thread.h"
#include "CmdDefines.h"
#include "CmdMsgMgr.h"


///Console
class Console : public Module, public ThreadEndpoint
{
private:
	//Thread definitions
	static ThreadEndpoint* user;
	static ThreadHandlerCpp handler;

	//Function definitions
	typedef void (Console::*Func)(CmdMsg);
	static struct FuncMap { const char* cmd; Func func; } funcmap[];

	//Members
	CmdMsgMgr msgMgr;

	//Methods
	void ExecuteThread();
	void ExecuteCmd(CmdMsg msg);
	void About(CmdMsg msg);
	void Help(CmdMsg msg);
public:
	//Methods
	Console();
	void Initialize();

	//Static methods
	static void ThreadHandler();
};

#endif // !__CONSOLE_H__
