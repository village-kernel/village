//###########################################################################
// Console.h
// Declarations of the functions that manage console
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "CmdMsgMgr.h"
#include "CmdDefs.h"
#include "Module.h"
#include "Mutex.h"
#include "Regex.h"
#include "Cmd.h"


///Console
class Console : public Module
{
private:
	//Static constants
	static const uint16_t buf_size = 100;
	static const uint16_t path_size = 100;

	//Members
	List<Cmd> cmds;
	Mutex     mutex;
	Regex     regex;
	CmdMsgMgr msgMgr;
	char      data[buf_size];
	char      path[path_size];

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

	//Output Methods
	void Log(const char* format, ...);
	void Info(const char* format, ...);
	void Error(const char* format, ...);
	void Warn(const char* format, ...);
	void Output(const char* format, ...);
	void OutputRAW(const char* format, ...);
	
	//Path Methods
	void SetPath(const char* path);
	const char* GetPath();
	
	//Singleton Instance
	static Console& Instance();
};

///Declarations Console reference
extern Console& console;

#endif // !__CONSOLE_H__
