//###########################################################################
// vk_terminal.h
// Declarations of the functions that manage terminal
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_TERMINAL_H__
#define __VK_TERMINAL_H__

#include "vk_kernel.h"
#include "vk_class.h"
#include "vk_console.h"
#include "vk_list.h"
#include "vk_cmd.h"


/// @brief ConcreteTerminal
class ConcreteTerminal : public Terminal, public Class
{
private:
	//Members
	VkList<Cmd*>     cmds;
	VkList<Sandbox*> sandboxes;

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
	void UnregisterCmd(Cmd* cmd, char* name);
	VkList<Cmd*> GetCmds();

	//Console Methods
	int CreateConsole(const char* driver);
	bool DestroyConsole(const char* driver);
	VkList<Sandbox*> GetSandboxes();
};

#endif // !__VK_TERMINAL_H__
