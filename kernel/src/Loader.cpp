//###########################################################################
// Loader.cpp
// Definitions of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Loader.h"


/// @brief Loader load
/// @param filename rc file path
void Loader::Loading(const char* filename)
{
	//Load rc file
	RcParser* rc = new RcParser(filename);

	//Load, parser and execute init array
	RcParser::RunCmdNode* node = rc->GetRunCmds();
	for (; NULL != node; node = node->next)
	{
		ElfParser* elf = new ElfParser();
		if (elf->Load(node->cmd) == Result::_OK)
		{
			elf->InitArray();
		}
	}

	//Release resource
	rc->Release();
}


/// @brief Loader load
/// @param filename rc file path
void Loader::LibLoading(const char* filename)
{
	//Load rc file
	RcParser* rc = new RcParser(filename);

	//Load, parser and execute init array
	RcParser::RunCmdNode* node = rc->GetRunCmds();
	for (; NULL != node; node = node->next)
	{
		ElfParser* elf = new ElfParser();
		if (Result::_OK != elf->LoadLib(node->cmd)) break;
	}

	//Release resource
	rc->Release();
}


/// @brief LibLoader Initialize
void LibLoader::Initialize()
{
	LibLoading("libraries/init.rc");
}
REGISTER_MODULE(new LibLoader(), ModuleID::_libLoader, libLoader);


/// @brief DrvLoader Initialize
void DrvLoader::Initialize()
{
	Loading("drivers/init.rc");
}
REGISTER_DRIVER(new DrvLoader(), DriverID::_drvLoader, drvLoader);


/// @brief ModLoader Initialize
void ModLoader::Initialize()
{
	Loading("modules/init.rc");
}
REGISTER_MODULE(new ModLoader(), ModuleID::_modLoader, modLoader);
