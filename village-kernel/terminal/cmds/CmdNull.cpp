//###########################################################################
// CmdNull.cpp
// Definitions of the functions that manage command null
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Kernel.h"


/// @brief CmdNull
class CmdNull : public Cmd
{
public:
	/// @brief Cmd null execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		
	}


	/// @brief Cmd null help
	void Help()
	{

	}
};


///Register cmd
REGISTER_CMD(new CmdNull(), null);
