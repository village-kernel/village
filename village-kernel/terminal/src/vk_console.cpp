//###########################################################################
// vk_console.cpp
// Definitions of the functions that manage console
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_kernel.h"
#include "vk_console.h"
#include "string.h"
#include "stdarg.h"
#include "stdio.h"


/// @brief Console welcome string
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


/// @brief Console setup
void Console::Setup(const char* driver)
{
	//Set default user
	strcpy(user, "root");

	//Set default machine
	strcpy(mach, "village");

	//Set default path
	strcpy(path, "/");

	//Setup msg mgr
	msgMgr.Setup(driver);

	//Output welcome message
	ShowWelcomeMsg();

	//Output console symbol
	ShowUserAndPath();
}


/// @brief Console execute
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

	//Gets all terminal commands
	List<Cmd*> cmds = kernel->terminal.GetCmds();

	//Find the command and execute it 
	for (Cmd* cmd = cmds.Begin(); !cmds.IsEnd(); cmd = cmds.Next())
	{
		if (0 == strcmp(cmds.GetName(), (const char*)msg.cmd))
		{
			regex.Split((const char*)msg.args);
			cmd->Setup(this);
			cmd->Execute(regex.Size(), regex.ToArray());
			cmd->Exit();
			regex.Clear();
			ShowUserAndPath();
			return;
		}
	}

	//Command not found
	msgMgr.Write((uint8_t*)msg.cmd);
	msgMgr.Write((uint8_t*)": command not found\r\n");
	ShowUserAndPath();
}


/// @brief Exit
void Console::Exit()
{
	msgMgr.Exit();
}


/// @brief Console show welcome msg
void Console::ShowWelcomeMsg()
{
	//Disable irq
	kernel->system.DisableIRQ();

	//Output welcome message
	uint8_t sizeofstr = sizeof(vk_welcome) / sizeof(char*);
	for (uint8_t i = 0; i < sizeofstr; i++)
	{
		msgMgr.Write((uint8_t*)vk_welcome[i]);
		msgMgr.Write((uint8_t*)"\r\n");
	}

	//Enable irq
	kernel->system.EnableIRQ();
}


/// @brief Console show user and path
void Console::ShowUserAndPath()
{
	Print("%s@%s %s # ", user, mach, path);
}


/// @brief Console log
/// @param format 
/// @param  
void Console::Log(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsnprintf(data, buf_size, format, arg);
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
	vsnprintf(data, buf_size, format, arg);
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
	vsnprintf(data, buf_size, format, arg);
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
	vsnprintf(data, buf_size, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)"\033[33mWarning: ");
	msgMgr.Write((uint8_t*)data);
	msgMgr.Write((uint8_t*)"\r\n\033[39m");
	mutex.Unlock();
}


/// @brief Console print
/// @param format 
/// @param  
void Console::Print(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsnprintf(data, buf_size, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)data);
	mutex.Unlock();
}


/// @brief Console print line
/// @param format 
/// @param  
void Console::Println(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsnprintf(data, buf_size, format, arg);
	va_end(arg);
	msgMgr.Write((uint8_t*)data);
	msgMgr.Write((uint8_t*)"\r\n");
	mutex.Unlock();
}


/// @brief Console Output
/// @param data 
/// @param size 
void Console::Output(const char* data, int size)
{
	mutex.Lock();
	msgMgr.Write((uint8_t*)data, size);
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


/// @brief AbsolutePath
/// @param filename 
/// @return 
const char* Console::AbsolutePath(const char* path)
{
	char* res = NULL;

	if ('/' != path[0])
	{
		res = new char[strlen(this->path) + strlen(path) + 2]();
		strcat(res, this->path);
		if ('/' != res[strlen(this->path) - 1]) strcat(res, "/");
		strcat(res, path);
	}
	else
	{
		res = new char[strlen(path) + 1]();
		strcat(res, path);
	}

	return res;
}
