//###########################################################################
// CmdMem.cpp
// Definitions of the functions that manage command memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Village.h"


/// @brief CmdMem
class CmdMem : public Cmd
{
private:
	//Members
	Village village;
public:
	/// @brief Cmd memeory execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		uint32_t size = village.GetMemSize();
		uint32_t used = village.GetMemUsed();
		uint32_t per  = (uint32_t)((float)used / (float)size * 100);
		console.Output("memory size: %d Byte, memory used: %d Byte, percentage used: %d %", size, used, per);
	}
};


///Register cmd
REGISTER_CMD(new CmdMem(), memory);
