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

	user = this;
	handler = (ThreadHandlerCpp)(&Console::RecvMsgThread);
	Thread::CreateTask(Console::ThreadHandler);
}


///Console execute
void Console::Execute()
{

}


///Recevice message thread
void Console::RecvMsgThread()
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
	msgMgr.Write((uint8_t*)"vk.kernel 0.0.1(beta), Copyright (C) village.\r\n");
}


///Console cmd help handler
void Console::Help(CmdMsg msg)
{
	msgMgr.Write((uint8_t*)"usage: help\r\n");
}


///Register module
REGISTER_MODULE(new Console(), COMM_APP_ID(0), console);
