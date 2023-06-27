//###########################################################################
// Loader.cpp
// Definitions of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Loader.h"
#include "rcParser.h"
#include "ElfParser.h"
#include "Environment.h"


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
EXPORT_SYMBOL(Loader::Instance, _ZN6Loader8InstanceEv);


/// @brief Definitions loader
Loader& loader = Loader::Instance();
static Loader* ploader = &loader;
EXPORT_SYMBOL(ploader, loader);


/// @brief Loader initialize
void Loader::Initialize()
{
	LoadingLib("libraries/_load_.rc");
	LoadingMod("modules/_load_.rc");
}


/// @brief Loader load lib
/// @param filename rc file path
void Loader::LoadingLib(const char* filename)
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


/// @brief Loader load module
/// @param filename rc file path
void Loader::LoadingMod(const char* filename)
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
