//###########################################################################
// Loader.cpp
// Definitions of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Loader.h"
#include "Kernel.h"
#include "rcParser.h"


/// @brief Constructor
Loader::Loader()
{
}


/// @brief Deconstructor
Loader::~Loader()
{
}


/// @brief Singleton Instance
/// @return Loader instance
Loader& Loader::Instance()
{
	static Loader instance;
	return instance;
}
EXPORT_SYMBOL(_ZN6Loader8InstanceEv);


/// @brief Definitions loader
Loader& loader = Loader::Instance();
EXPORT_SYMBOL(loader);


/// @brief Loader initialize
void Loader::Initialize()
{
	Loading(_Load_Lib, "/libraries/_load_.rc");
	Loading(_Load_Mod, "/modules/_load_.rc");
}


/// @brief Loader execute
void Loader::Execute()
{
	//Execute the first application of the village
	executor.Run("/applications/taichi.exec");
}


/// @brief Loader load
/// @param filename rc file path
void Loader::Loading(int type, const char* filename)
{
	RcParser* parser = new RcParser(filename);

	List<char*>& runcmds = parser->GetRunCmds();

	for (runcmds.End(); runcmds.IsBegin(); runcmds.Prev())
	{
		if (_Load_Lib == type)
		{
			if (!libraryTool.Install(runcmds.Item())) break;
		}
		else if (_Load_Mod == type)
		{
			if (!moduleTool.Install(runcmds.Item())) break;
		}
	}

	parser->Release();
	delete parser;
}
EXPORT_SYMBOL(_ZN6Loader7LoadingEiPKc);


/// @brief Get libraries
/// @return libraries
List<ElfLoader*>* Loader::GetLibraries()
{
	return &libraries;
}
EXPORT_SYMBOL(_ZN6Loader12GetLibrariesEv);


/// @brief Get modules
/// @return modules
List<ElfLoader*>* Loader::GetModules()
{
	return &modules;
}
EXPORT_SYMBOL(_ZN6Loader10GetModulesEv);


///Register module
REGISTER_MODULE(&Loader::Instance(), ModuleID::_loader, loader);
