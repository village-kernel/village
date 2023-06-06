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
			elf->Execute();
		}
	}

	//Release resource
	rc->Release();
}


/// @brief DrvLoader Initialize
void DrvLoader::Initialize()
{
	Loading("driver.rc");
}
REGISTER_DRIVER(new DrvLoader(), DriverID::_drvLoadr, drvLoader);


/// @brief ModLoader Initialize
void ModLoader::Initialize()
{
	Loading("init.rc");
}
REGISTER_MODULE(new ModLoader(), ModuleID::_modLoader, modLoader);
