//###########################################################################
// CmdMod.cpp
// Definitions of the functions that manage command insmod and rmmod
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "CmdMod.h"
#include "Console.h"
#include "string.h"


/// @brief Initialize
void CmdInsMod::Initialize()
{
	
}


/// @brief Cmd insmod execute
/// @param argc 
/// @param argv 
void CmdInsMod::Execute(int argc, char* argv[])
{
	if (argc < 2)
	{
		console.Output("Usage: insmod [module]");
		return;
	}
	if (_OK != modules.Install(argv[1]))
	{
		console.Error("Install module %s failed", argv[1]);
	}
}


///Register cmd
REGISTER_CMD(new CmdInsMod(), insmod);


/// @brief Initialize
void CmdRmMod::Initialize()
{
	
}


/// @brief Cmd rmmod execute
/// @param argc 
/// @param argv 
void CmdRmMod::Execute(int argc, char* argv[])
{
	if (argc < 2)
	{
		console.Output("Usage: rmmod [module]");
		return;
	}
	if (_OK != modules.Uninstall(argv[1]))
	{
		console.Error("Uninstall module %s failed", argv[1]);
	}
}


///Register cmd
REGISTER_CMD(new CmdRmMod(), rmmod);
