//###########################################################################
// Console.h
// Declarations of the functions that manage console
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "Module.h"
#include "Cmd.h"

///Command create macro
#define CREATE_CMD(cmd, name)    static struct _CMD_##name{_CMD_##name(){cmd;}} const _cmd_##name;

///Command register macro
#define REGISTER_CMD(cmd, name)  CREATE_CMD(Console::Instance().RegisterCmd(cmd, (uint8_t*)#name), name)


///Console
class Console : public Module
{
private:
	//Structures
	struct CmdNode
	{
		Cmd* cmd;
		CmdNode* next;

		CmdNode(Cmd* cmd = NULL) :
			cmd(cmd),
			next(NULL)
		{}
	};

	//Members
	CmdNode*  list;
	CmdMsgMgr msgMgr;

	//Methods
	Console();
	void ExecuteCmd(CmdMsg msg);
public:
	//Methods
	void Initialize();
	void Execute();
	void RegisterCmd(Cmd* cmd, uint8_t* name);
	void DeregisterCmd(Cmd* cmd, uint8_t* name);

	//Singleton Instance
	static Console& Instance();
};

#endif // !__CONSOLE_H__
