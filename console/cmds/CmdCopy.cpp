//###########################################################################
// CmdCopy.cpp
// Definitions of the functions that manage command copy
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"


/// @brief CmdCopy
class CmdCopy : public Cmd
{
public:
	/// @brief Cmd copy initialize
	void Initialize()
	{

	}


	/// @brief Cmd copy execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		
	}
};


///Register cmd
REGISTER_CMD(new CmdCopy(), cp);
