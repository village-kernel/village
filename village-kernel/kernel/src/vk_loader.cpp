//###########################################################################
// vk_loader.cpp
// Definitions of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_loader.h"


/// @brief Constructor
ConcreteLoader::ConcreteLoader()
{
}


/// @brief Destructor
ConcreteLoader::~ConcreteLoader()
{
}


/// @brief Loader setup
void ConcreteLoader::Setup()
{
	//Loading libraries
	Load(Loader::_Lib, "/libraries/_load_.rc");

	//Loading modules
	Load(Loader::_Mod, "/modules/_load_.rc");

	//Output debug info
	kernel->debug.Info("Loader setup done!");
}


/// @brief Loader Exit
void ConcreteLoader::Exit()
{
	//Unloading modules
	Unload(Loader::_Mod, "/modules/_load_.rc");

	//Unloading libraries
	Unload(Loader::_Lib, "/libraries/_load_.rc");
}


/// @brief Loader load
/// @param filename rc file path
void ConcreteLoader::Load(int type, const char* filename)
{
	RcParser* parser = new RcParser(filename);

	List<char*>& runcmds = parser->GetRunCmds();

	for (runcmds.End(); !runcmds.IsBegin(); runcmds.Prev())
	{
		if (!Install(type, runcmds.Item())) break;
	}

	parser->Release();
	delete parser;
}


/// @brief Loader unload
/// @param filename rc file path
void ConcreteLoader::Unload(int type, const char* filename)
{
	RcParser* parser = new RcParser(filename);

	List<char*>& runcmds = parser->GetRunCmds();

	for (runcmds.Begin(); !runcmds.IsEnd(); runcmds.Next())
	{
		if (!Uninstall(type, runcmds.Item())) break;
	}

	parser->Release();
	delete parser;
}


/// @brief Loader install
/// @param type 
/// @param filename 
bool ConcreteLoader::Install(int type, const char* filename)
{
	if (Loader::_Lib == type)
	{
		return libraryTool.Install(filename);
	}
	else if (Loader::_Mod == type)
	{
		return moduleTool.Install(filename);
	}
	return false;
}


/// @brief Loader install
/// @param type 
/// @param filename 
bool ConcreteLoader::Uninstall(int type, const char* filename)
{
	if (Loader::_Lib == type)
	{
		return libraryTool.Uninstall(filename);
	}
	else if (Loader::_Mod == type)
	{
		return moduleTool.Uninstall(filename);
	}
	return false;
}


/// @brief Get libraries
/// @return libraries
List<ElfLoader*>* ConcreteLoader::GetLibraries()
{
	return &libraries;
}


/// @brief Get modules
/// @return modules
List<ElfLoader*>* ConcreteLoader::GetModules()
{
	return &modules;
}
