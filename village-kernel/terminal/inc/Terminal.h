//###########################################################################
// Terminal.h
// Declarations of the functions that manage terminal
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include "Kernel.h"
#include "Class.h"
#include "Console.h"
#include "List.h"
#include "Cmd.h"


/// @brief ConcreteTerminal
class ConcreteTerminal : public Terminal, public Class
{
private:
	//Members
	List<Cmd*>     cmds;
	List<Sandbox*> sandboxes;

	//Methods
	void Execute();
	char* ThreadName(const char* driver);
	void ConsoleSandbox(Sandbox* sandbox);
public:
	//Methods
	ConcreteTerminal();
	~ConcreteTerminal();
	void Setup();
	void Exit();

	//Cmd Methods
	void RegisterCmd(Cmd* cmd, char* name);
	void DeregisterCmd(Cmd* cmd, char* name);
	List<Cmd*> GetCmds();

	//Console Methods
	int CreateConsole(const char* driver);
	bool DestroyConsole(const char* driver);
	List<Sandbox*> GetSandboxes();
};

#endif // !__TERMINAL_H__
