//###########################################################################
// CmdRemove.cpp
// Definitions of the functions that manage command remove
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"


/// @brief CmdRemove
class CmdRemove : public Cmd
{
public:
	/// @brief Cmd remove initialize
	void Initialize()
	{

	}


	/// @brief Cmd remove execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		
	}
};


///Register cmd
REGISTER_CMD(new CmdRemove(), rm);
