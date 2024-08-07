//###########################################################################
// CmdMod.cpp
// Definitions of the functions that manage command insmod and rmmod
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Kernel.h"
#include "string.h"


/// @brief CmdListMod
class CmdListMod : public Cmd
{
public:
	/// @brief Cmd lsmod execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 1)
		{
			console->Output("Usage: lsmod");
			return;
		}

		List<ElfLoader*>* mods = kernel->loader.GetModules();
		if (NULL != mods)
		{
			for (mods->Begin(); !mods->IsEnd(); mods->Next())
			{
				console->Output("name %s", mods->GetName());
			}
		}
	}


	/// @brief Cmd lsmod help
	void Help()
	{
		console->Output("cmd lsmod: list installed module information");
	}
};


/// @brief CmdInsMod
class CmdInsMod : public Cmd
{
public:
	/// @brief Cmd insmod execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 2)
		{
			console->Output("Usage: insmod [module]");
			return;
		}
		if (!kernel->loader.Install(Loader::_Mod, argv[1]))
		{
			console->Error("Install module %s failed", argv[1]);
		}
	}


	/// @brief Cmd insmod help
	void Help()
	{
		console->Output("cmd insmod: install module");
	}
};


/// @brief CmdRmMod
class CmdRmMod : public Cmd
{
public:
	/// @brief Cmd rmmod execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 2)
		{
			console->Output("Usage: rmmod [module]");
			return;
		}
		if (!kernel->loader.Uninstall(Loader::_Mod, argv[1]))
		{
			console->Error("Uninstall module %s failed", argv[1]);
		}
	}


	/// @brief Cmd rmmod help
	void Help()
	{
		console->Output("cmd rmmod: remove module");
	}
};


///Register cmd
REGISTER_CMD(new CmdListMod(), lsmod);
REGISTER_CMD(new CmdInsMod(), insmod);
REGISTER_CMD(new CmdRmMod(), rmmod);
