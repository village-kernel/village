//###########################################################################
// Loader.cpp
// Definitions of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Loader.h"
#include "string.h"


///Constructor 
Loader::Loader()
{
}


///Loader Initialize
void Loader::Initialize()
{
	//Load and parser init.rc file
	rc.Load("1:init.rc");
	std::list<std::string> resources = rc.GetResources();
	std::list<std::string>::iterator it = resources.begin();
	std::string path("1:");
	path += (*it).c_str();

	//Load, parser and execute elf file
	if (elf.Load(path.c_str()) != Result::_OK) return;
	elf.InitArray();
}


///Loader execute app
void Loader::ExecuteApp()
{
	elf.InitArray();
	elf.Execute();
	elf.FiniArray();
	elf.Exit();
}


///Register module
REGISTER_MODULE(new Loader(), ModuleID::_loader, loader);
