//###########################################################################
// vk_cmd_null.cpp
// Definitions of the functions that manage command null
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_cmd.h"
#include "vk_console.h"
#include "vk_kernel.h"


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
