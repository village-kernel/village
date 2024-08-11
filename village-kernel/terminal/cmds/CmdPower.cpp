//###########################################################################
// CmdPower.cpp
// Definitions of the functions that manage command reboot
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Kernel.h"


/// @brief CmdSleep
class CmdSleep : public Cmd
{
public:
	/// @brief Cmd sleep execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		kernel->Sleep();
	}


	/// @brief Cmd sleep help
	void Help()
	{
		console->Output("cmd sleep: sleep device");
	}
};


/// @brief CmdReboot
class CmdReboot : public Cmd
{
public:
	/// @brief Cmd reboot execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		kernel->Reboot();
	}


	/// @brief Cmd reboot help
	void Help()
	{
		console->Output("cmd reboot: reboot device");
	}
};


/// @brief CmdShutdown
class CmdShutdown : public Cmd
{
public:
	/// @brief Cmd shutdown execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		kernel->Shutdown();
	}


	/// @brief Cmd shutdown help
	void Help()
	{
		console->Output("cmd shutdown: shutdown device");
	}
};



///Register cmd
REGISTER_CMD(new CmdSleep(),    sleep   );
REGISTER_CMD(new CmdReboot(),   reboot  );
REGISTER_CMD(new CmdShutdown(), shutdown);
