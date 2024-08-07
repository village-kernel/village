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
#include "Mutex.h"
#include "Regex.h"
#include "Cmd.h"
#include "List.h"


/// @brief Console
class Console
{
private:
	//Static constants
	static const uint16_t buf_size = 256;
	static const uint16_t path_size = 100;

	//Members
	Mutex      mutex;
	Regex      regex;
	CmdMsgMgr  msgMgr;
	char       data[buf_size];
	char       path[path_size];
	
	//Methods
	void ExecuteCmd(CmdMsg msg);
public:
	//Methods
	Console();
	~Console();
	void Setup(const char* driver);
	void Execute();
	void Exit();

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
};

#endif // !__CONSOLE_H__
