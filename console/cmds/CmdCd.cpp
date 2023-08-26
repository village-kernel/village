//###########################################################################
// CmdCd.cpp
// Definitions of the functions that manage command change directory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"


/// @brief CmdCd
class CmdCd : public Cmd
{
public:
	/// @brief Cmd cd initialize
	void Initialize()
	{

	}


	/// @brief Cmd cd execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		
	}
};


///Register cmd
REGISTER_CMD(new CmdCd(), cd);
