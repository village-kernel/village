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
Console::Console()
{
}


/// @brief Console destructor
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


/// @brief Definitions console and export
Console& console = Console::Instance();


/// @brief Console initialize
void Console::Initialize(const char* driver)
{
	//Set default path
	strcpy(path, "/");

	//Initialize msg mgr
	msgMgr.Initialize(driver);

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
	}

	//Output console symbol
	msgMgr.Write((uint8_t*)path);
	msgMgr.Write((uint8_t*)" # ");
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
	msgMgr.Write((uint8_t*)"\r\n");

	for (Cmd* cmd = cmds.Begin(); !cmds.IsEnd(); cmd = cmds.Next())
	{
		if (0 == strcmp(cmds.GetName(), (const char*)msg.cmd))
		{
			regex.Split((const char*)msg.args);
			cmd->Execute(regex.Size(), regex.ToArray());
			regex.Clear();
			msgMgr.Write((uint8_t*)path);
			msgMgr.Write((uint8_t*)" # ");
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


/// @brief Deregister cmd object
/// @param cmd console command pointer
/// @param name console command name 
void Console::DeregisterCmd(Cmd* cmd, char* name)
{
	cmds.RemoveByName(cmd, name);
}


/// @brief Console log
/// @param format 
/// @param  
void Console::Log(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)"Log: ");
	msgMgr.Write((uint8_t*)data);
	msgMgr.Write((uint8_t*)"\r\n");
	mutex.Unlock();
}


/// @brief Console info
/// @param format 
/// @param  
void Console::Info(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)"\033[36mInfo: ");
	msgMgr.Write((uint8_t*)data);
	msgMgr.Write((uint8_t*)"\r\n\033[39m");
	mutex.Unlock();
}


/// @brief Console error
/// @param format 
/// @param  
void Console::Error(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)"\033[31mError: ");
	msgMgr.Write((uint8_t*)data);
	msgMgr.Write((uint8_t*)"\r\n\033[39m");
	mutex.Unlock();
}


/// @brief Console warn
/// @param format 
/// @param  
void Console::Warn(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)"\033[33mWarning: ");
	msgMgr.Write((uint8_t*)data);
	msgMgr.Write((uint8_t*)"\r\n\033[39m");
	mutex.Unlock();
}


/// @brief Console output
/// @param format 
/// @param  
void Console::Output(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)data);
	msgMgr.Write((uint8_t*)"\r\n");
	mutex.Unlock();
}


/// @brief Console output
/// @param format 
/// @param  
void Console::OutputRAW(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)data);
	mutex.Unlock();
}


/// @brief Console set path
/// @param path 
void Console::SetPath(const char* path)
{
	if (path_size > strlen(path))
	{
		strcpy(this->path, path);
	}
	else
	{
		Error("The path length exceeds the limit, the maximum length is %d.", path_size);
	}
}


/// @brief Cosole get path
/// @return path
const char* Console::GetPath()
{
	return path;
}


/// @brief main
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		return -1;
	}
	else
	{
		console.Initialize(argv[1]);
		console.Execute();
		return 0;
	}
}
