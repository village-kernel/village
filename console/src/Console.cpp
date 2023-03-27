//###########################################################################
// Console.cpp
// Definitions of the functions that manage console
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Console.h"
#include "string.h"


///Initialize cmd core
Console::CmdNode* Console::list = NULL;


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
	for (volatile CmdNode* node = list; NULL != node; node = node->next)
	{
		node->cmd->Initialize(&msgMgr);
	}

	//Set execute thread to thread task
	Thread::CreateTaskCpp(this, (ThreadHandlerCpp)&Console::ReceviceThread);
}


///Recevice message thread
void Console::ReceviceThread()
{
	while (1)
	{
		if (msgMgr.Execute())
		{
			ExecuteCmd(msgMgr.Read());
		}
		Thread::Sleep(1);
	}
}


///Console execute cmd
void Console::ExecuteCmd(CmdMsg msg)
{
	for (volatile CmdNode* node = list; NULL != node; node = node->next)
	{
		if (0 == strcmp((const char*)(node->cmd->GetName()), (const char*)msg.cmd))
		{
			node->cmd->SetArgs(msg.args);
			node->cmd->Execute();
			msgMgr.Write((uint8_t*)"# ");
			return;
		}
	}

	msgMgr.Write((uint8_t*)msg.cmd);
	msgMgr.Write((uint8_t*)": command not found\r\n# ");
}


///Register cmd object
void Console::RegisterCmd(Cmd* cmd, uint8_t* name)
{
	CmdNode** nextNode = &list;

	if (cmd) cmd->SetName(name); else return;

	while (NULL != *nextNode)
	{
		uint8_t* curCmdName = (*nextNode)->cmd->GetName();
		uint8_t* newCmdName = cmd->GetName();

		if (strcmp((const char*)newCmdName, (const char*)curCmdName) < 0)
		{
			CmdNode* curNode = *nextNode;
			*nextNode = new CmdNode(cmd);
			(*nextNode)->next = curNode;
			return;
		}

		nextNode = &(*nextNode)->next;
	}

	*nextNode = new CmdNode(cmd);
}


///Deregister cmd object
void Console::DeregisterCmd(Cmd* cmd, uint8_t* name)
{
	CmdNode** prevNode = &list;
	CmdNode** currNode = &list;

	while (NULL != *currNode)
	{
		if (cmd == (*currNode)->cmd)
		{
			delete *currNode;

			if (*prevNode == *currNode)
				*prevNode = (*currNode)->next;
			else
				(*prevNode)->next = (*currNode)->next;

			break;
		}
		else
		{
			prevNode = currNode;
			currNode = &(*currNode)->next;
		}
	}
}


///Register module
REGISTER_MODULE(new Console(), ModuleID::_console, console);
