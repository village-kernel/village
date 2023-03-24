//###########################################################################
// Loader.cpp
// Definitions of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Loader.h"
#include "rcParser.h"
#include "ElfParser.h"
#include "string.h"


///Loader Initialize
void Loader::Initialize()
{
	LoadLibraries();
	LoadModules();
}


///Loader load libraries
void Loader::LoadLibraries()
{
	
}


///Loader load modules
void Loader::LoadModules()
{
	RcParser rc;
	rc.Load("1:init.rc");
	std::list<std::string> resources = rc.GetResources();
	std::list<std::string>::iterator it = resources.begin();
	std::string path("1:");
	path += (*it).c_str();

	ElfParser elf;
	if (elf.Load(path.c_str()) != ElfParser::_OK) return;
	elf.Execute("Entry");
}


///Register module
REGISTER_MODULE(new Loader(), ModuleID::_loader, loader);
