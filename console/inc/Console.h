//###########################################################################
// Console.h
// Declarations of the functions that manage console
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "SyncLock.h"
#include "CmdMsgMgr.h"
#include "Module.h"
#include "Regex.h"
#include "Cmd.h"

///Command create macro
#define CREATE_CMD(cmd, name)    static struct _CMD_##name{_CMD_##name(){cmd;}} const _cmd_##name;

///Command register macro
#define REGISTER_CMD(cmd, name)  CREATE_CMD(Console::Instance().RegisterCmd(cmd, (char*)#name), name)

//Debug level
enum DebugLevel
{
	_Debug_L0 = 0,
	_Debug_L1,
	_Debug_L2,
	_Debug_L3,
	_Debug_L4,
	_Debug_L5
};

///Console
class Console : public Module
{
private:
	//Static constants
	static const uint16_t buf_size = 100;

	//Members
	List<Cmd> cmds;
	Mutex     mutex;
	Regex     regex;
	CmdMsgMgr msgMgr;
	char      data[buf_size];
	int       debugLevel;

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
	void log(const char* format, ...);
	void info(const char* format, ...);
	void error(const char* format, ...);
	void warn(const char* format, ...);
	void output(const char* format, ...);
	
	
	//Debug methods
	void debug(int level, const char* format, ...);
	void SetDebugLevel(int level);
	
	//Singleton Instance
	static Console& Instance();
};

///Declarations Console reference
extern Console& console;

#endif // !__CONSOLE_H__
