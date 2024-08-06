//###########################################################################
// CmdMem.cpp
// Definitions of the functions that manage command memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Kernel.h"


/// @brief CmdMem
class CmdMem : public Cmd
{
public:
	/// @brief Cmd memeory execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		uint32_t size = kernel->memory.GetSize();
		uint32_t used = kernel->memory.GetUsed();
		uint32_t per  = used * 100 / size;
		console.Output("memory size: %d Byte, memory used: %d Byte, percentage used: %d %", size, used, per);
	}


	/// @brief Cmd memory help
	void Help()
	{
		console.Output("cmd memory: show memory used information");
	}
};


///Register cmd
REGISTER_CMD(new CmdMem(), memory);
