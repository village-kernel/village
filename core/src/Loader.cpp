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


/// @brief Definitions loader
Loader& loader = Loader::Instance();


/// @brief Loader initialize
void Loader::Initialize()
{
	Loading(_Load_Lib, "C:/libraries/_load_.rc");
	Loading(_Load_Mod, "C:/modules/_load_.rc");
}


/// @brief Loader execute
void Loader::Execute()
{
	//Execute the first application of the village
	executor.Run("C:/applications/taichi.exec");
}


/// @brief Loader load
/// @param filename rc file path
void Loader::Loading(int type, const char* filename)
{
	//Load rc file
	RcParser* rc = new RcParser(filename);

	//Load, parser and execute init array
	RcParser::RunCmdNode* node = rc->GetRunCmds();
	for (; NULL != node; node = node->next)
	{
		if (_Load_Lib == type)
		{
			libraries.Install(node->cmd);
		}
		else if (_Load_Mod == type)
		{
			modules.Install(node->cmd);
		}
	}

	//Release resource
	rc->Release();
	delete rc;
}


///Register module
REGISTER_MODULE(&Loader::Instance(), ModuleID::_loader, loader);
