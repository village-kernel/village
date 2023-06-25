//###########################################################################
// Console.cpp
// Definitions of the functions that manage console
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Console.h"
#include "string.h"
#include "stdarg.h"
#include "stdio.h"


///vk.kernel console welcome string
const char* vk_welcome[] = {
"\r\n",
R"(        _ ____                    __                        __ )",
R"( _   __(_) / /___ _____ ____     / /_____  _________  ___  / / )",
R"(| | / / / / / __ `/ __ `/ _ \   / //_/ _ \/ ___/ __ \/ _ \/ /  )",
R"(| |/ / / / / /_/ / /_/ /  __/  / ,< /  __/ /  / / / /  __/ /   )",
R"(|___/_/_/_/\__,_/\__, /\___/  /_/|_|\___/_/  /_/ /_/\___/_/    )",
R"(                /____/                                         )",
"\r\n",
};


/// @brief Console constructor
Console::Console() :
#ifdef Debug
	enaDebug(true)
#else
	enaDebug(false)
#endif
{
}


/// @brief Console deconstructor
Console::~Console()
{
}


/// @brief Singleton Instance
/// @return Console instance
Console& Console::Instance()
{
	static Console instance;
	return instance;
}
EXPORT_SYMBOL(Console::Instance, _ZN7Console8InstanceEv);


/// @brief Definitions console and export
Console& console = Console::Instance();
Console* pConsole = &console;
EXPORT_SYMBOL(pConsole, console);


/// @brief Console initialize
void Console::Initialize()
{
	//Initialize msg mgr
	msgMgr.Initialize();

	//Initialize cmds
	for (Cmd* cmd = cmds.Begin(); !cmds.IsEnd(); cmd = cmds.Next())
	{
		cmd->Initialize();
	}

	//Output welcome message
	uint8_t sizeofstr = sizeof(vk_welcome) / sizeof(char*);
	for (uint8_t i = 0; i < sizeofstr; i++)
	{	
		msgMgr.Write((uint8_t*)vk_welcome[i]);
		msgMgr.Write((uint8_t*)"\r\n");
		msgMgr.Execute();
	}

	//Output console symbol
	msgMgr.Write((uint8_t*)"# ");
	msgMgr.Execute();
}


/// @brief Recevice and handler message
void Console::Execute()
{
	while (1)
	{
		if (msgMgr.Execute())
		{
			ExecuteCmd(msgMgr.Read());
		}
	}
}


/// @brief Console execute cmd
/// @param msg recevice message data
void Console::ExecuteCmd(CmdMsg msg)
{
	for (Cmd* cmd = cmds.Begin(); !cmds.IsEnd(); cmd = cmds.Next())
	{
		if (0 == strcmp(cmds.GetName(), (const char*)msg.cmd))
		{
			regex.Split((const char*)msg.args);
			cmd->Execute(regex.Size(), regex.ToArray());
			regex.Clear();
			msgMgr.Write((uint8_t*)"# ");
			return;
		}
	}

	msgMgr.Write((uint8_t*)msg.cmd);
	msgMgr.Write((uint8_t*)": command not found\r\n# ");
}


/// @brief Register cmd object
/// @param cmd console command pointer
/// @param name console command name
void Console::RegisterCmd(Cmd* cmd, char* name)
{
	cmds.InsertByName(cmd, name);
}
EXPORT_SYMBOL(Console::RegisterCmd, _ZN7Console11RegisterCmdEP3CmdPc);


/// @brief Deregister cmd object
/// @param cmd console command pointer
/// @param name console command name 
void Console::DeregisterCmd(Cmd* cmd, char* name)
{
	cmds.RemoveByName(cmd, name);
}
EXPORT_SYMBOL(Console::DeregisterCmd, _ZN7Console13DeregisterCmdEP3CmdPc);


/// @brief Console log
/// @param format 
/// @param  
void Console::log(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)"Log: ");
	msgMgr.Write((uint8_t*)data);
	msgMgr.Write((uint8_t*)"\r\n");
	msgMgr.Execute();
	mutex.Unlock();
}
EXPORT_SYMBOL(Console::log, _ZN7Console3logEPKcz);


/// @brief Console info
/// @param format 
/// @param  
void Console::info(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)"\033[36mInfo: ");
	msgMgr.Write((uint8_t*)data);
	msgMgr.Write((uint8_t*)"\r\n\033[39m");
	msgMgr.Execute();
	mutex.Unlock();
}
EXPORT_SYMBOL(Console::info, _ZN7Console4infoEPKcz);


/// @brief Console error
/// @param format 
/// @param  
void Console::error(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)"\033[31mError: ");
	msgMgr.Write((uint8_t*)data);
	msgMgr.Write((uint8_t*)"\r\n\033[39m");
	msgMgr.Execute();
	mutex.Unlock();
}
EXPORT_SYMBOL(Console::error, _ZN7Console5errorEPKcz);


/// @brief Console warn
/// @param format 
/// @param  
void Console::warn(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)"\033[33mWarning: ");
	msgMgr.Write((uint8_t*)data);
	msgMgr.Write((uint8_t*)"\r\n\033[39m");
	msgMgr.Execute();
	mutex.Unlock();
}
EXPORT_SYMBOL(Console::warn, _ZN7Console4warnEPKcz);


/// @brief Console debug
/// @param format 
/// @param  
void Console::debug(const char* format, ...)
{
	if (true == enaDebug)
	{
		mutex.Lock();
		va_list arg;
		va_start(arg, format);
		vsprintf(data, format, arg);
		va_end(arg);
		msgMgr.Write((uint8_t*)"\033[36mDebug: ");
		msgMgr.Write((uint8_t*)data);
		msgMgr.Write((uint8_t*)"\r\n\033[39m");
		msgMgr.Execute();
		mutex.Unlock();
	}
}
EXPORT_SYMBOL(Console::debug, _ZN7Console5debugEPKcz);


/// @brief Console output
/// @param format 
/// @param  
void Console::output(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)data);
	msgMgr.Write((uint8_t*)"\r\n");
	msgMgr.Execute();
	mutex.Unlock();
}
EXPORT_SYMBOL(Console::output, _ZN7Console6outputEPKcz);


///Register module
REGISTER_MODULE(&Console::Instance(), ModuleID::_console, console);
