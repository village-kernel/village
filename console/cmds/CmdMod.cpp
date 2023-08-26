//###########################################################################
// CmdMod.cpp
// Definitions of the functions that manage command insmod and rmmod
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "ModuleTool.h"
#include "string.h"


/// @brief CmdInsMod
class CmdInsMod : public Cmd
{
private:
	//Members
	ModuleTool modules;
public:
	/// @brief Initialize
	void Initialize()
	{
		
	}


	/// @brief Cmd insmod execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
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
};


/// @brief CmdRmMod
class CmdRmMod : public Cmd
{
private:
	//Members
	ModuleTool modules;
public:
	/// @brief Initialize
	void Initialize()
	{
		
	}


	/// @brief Cmd rmmod execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
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
};


///Register cmd
REGISTER_CMD(new CmdInsMod(), insmod);
REGISTER_CMD(new CmdRmMod(), rmmod);
