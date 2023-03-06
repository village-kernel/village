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

#include "CmdAbout.h"
#include "CmdHelp.h"


///Console
class Console : public Module
{
private:
	//Function definitions
	typedef void (Console::*Func)(CmdMsg);
	static struct FuncMap { const char* cmd; Func func; } funcmap[];

	//Members
	CmdMsgMgr msgMgr;
	CmdAbout  about;
	CmdHelp   help;

	//Methods
	void ReceviceThread();
	void ExecuteCmd(CmdMsg msg);
	void About(CmdMsg msg);
	void Help(CmdMsg msg);
public:
	//Methods
	Console();
	void Initialize();
};

#endif // !__CONSOLE_H__
