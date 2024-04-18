//###########################################################################
// Loader.cpp
// Definitions of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Loader.h"


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
	Loading(_Load_Lib, "/libraries/_load_.rc");

	//Loading modules
	Loading(_Load_Mod, "/modules/_load_.rc");

	//Create task
	kernel->thread.CreateTask("Loader", (Method)&ConcreteLoader::Execute, this);
}


/// @brief Loader Exit
void ConcreteLoader::Exit()
{
	libraries.Release();
	modules.Release();
}


/// @brief Loader execute
void ConcreteLoader::Execute()
{
	//Execute the first application of the village
	executor.Run(ElfExecutor::_Background, "/applications/taichi.exec");
}


/// @brief Loader load
/// @param filename rc file path
void ConcreteLoader::Loading(int type, const char* filename)
{
	RcParser* parser = new RcParser(filename);

	List<char*>& runcmds = parser->GetRunCmds();

	for (runcmds.End(); !runcmds.IsBegin(); runcmds.Prev())
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
