//###########################################################################
// Console.cpp
// Definitions of the functions that manage console
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Console.h"
#include "string.h"


///Thread members initialize
ThreadEndpoint* Console::user;
ThreadHandlerCpp Console::handler;


///Initialize function map table
Console::FuncMap Console::funcmap[] = 
{
	{ "about",           &Console::About                    },
	{ "help",            &Console::Help                     },
	{ "null",            NULL                               }
};


///Constructor
Console::Console()
{
}


///Console initialize
void Console::Initialize()
{
	//Initialize msg mgr
	msgMgr.Initialize();

	//Initialize cmds
	about.Initialize(&msgMgr);
	help.Initialize(&msgMgr);

	//Set execute thread to thread task
	user = this;
	handler = (ThreadHandlerCpp)(&Console::ExecuteThread);
	Thread::CreateTask(Console::ThreadHandler);
}


///Recevice message thread
void Console::ExecuteThread()
{
	while (1)
	{
		if (msgMgr.Execute())
		{
			ExecuteCmd(msgMgr.Read());
		}
		Thread::Sleep(50);
	}
}


///ThreadHandler
void Console::ThreadHandler()
{
	if (user != 0) { (user->*handler)(); }
}


///Console execute cmd
void Console::ExecuteCmd(CmdMsg msg)
{
	for (uint8_t i = 0; (0 != strcmp(funcmap[i].cmd, "null")); i++)
	{
		if (0 == strcmp(funcmap[i].cmd, (const char*)msg.cmd))
		{
			(this->*funcmap[i].func)(msg);
			msgMgr.Write((uint8_t*)"# ");
			return;
		}
	}

	msgMgr.Write((uint8_t*)msg.cmd);
	msgMgr.Write((uint8_t*)": command not found\r\n# ");
}


///Console cmd about handler
void Console::About(CmdMsg msg)
{
	about.SetArgs(msg.args);
	about.Execute();
}


///Console cmd help handler
void Console::Help(CmdMsg msg)
{
	help.SetArgs(msg.args);
	help.Execute();
}


///Register module
REGISTER_MODULE(new Console(), ModuleID::_console, console);
