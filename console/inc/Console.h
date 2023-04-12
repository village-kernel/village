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
#define REGISTER_CMD(cmd, name)  CREATE_CMD(Console::Instance().RegisterCmd(cmd, (char*)#name), name)


///Console
class Console : public Module
{
private:
	//Members
	List<Cmd> cmds;
	CmdMsgMgr msgMgr;

	//Methods
	Console();
	~Console();
	void ExecuteCmd(CmdMsg msg);
public:
	//Methods
	void Initialize();
	void Execute();
	void RegisterCmd(Cmd* cmd, char* name);
	void DeregisterCmd(Cmd* cmd, char* name);

	//Methods
	int log(...);
	int info(...);
	int error(...);
	int warn(...);

	//Singleton Instance
	static Console& Instance();
};

///Declarations Console reference
extern Console& console;

#endif // !__CONSOLE_H__
