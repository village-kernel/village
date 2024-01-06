//###########################################################################
// CmdPower.cpp
// Definitions of the functions that manage command reboot
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Village.h"


/// @brief CmdReboot
class CmdReboot : public Cmd
{
public:
	/// @brief Cmd reboot execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		village.Reboot();
	}
};


///Register cmd
REGISTER_CMD(new CmdReboot(), reboot);
