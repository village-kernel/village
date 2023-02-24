//###########################################################################
// Console.cpp
// Definitions of the functions that manage console
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Console.h"
#include "string.h"


///Initialize function map table
Console::FuncMap Console::funcmap[] = 
{
	{ _About,           &Console::About                    },
	{ _Null,            NULL                               }
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
}


///Console execute
void Console::Execute()
{
	if (msgMgr.Execute())
	{
		ExecuteCmd(msgMgr.Read());
	}
}


///Console execute cmd
void Console::ExecuteCmd(CmdMsg msg)
{
	for (uint8_t i = 0; funcmap[i].cmd; i++)
	{
		if (msg.cmd == funcmap[i].cmd)
		{
			(this->*funcmap[i].func)(msg);
			break;
		}
	}
}


///Console cmd about handler
void Console::About(CmdMsg msg)
{

}


///Register module
REGISTER_MODULE(new Console(), COMM_APP_ID(0), console);
