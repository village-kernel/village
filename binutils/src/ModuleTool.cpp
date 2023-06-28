//###########################################################################
// ModuleTool.cpp
// Definitions of the functions that manage module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Debug.h"
#include "ModuleTool.h"


/// @brief Initialize modules
List<ElfLoader> ModuleTool::modules;


/// @brief Constructor
ModuleTool::ModuleTool()
{
}


/// @brief Deconstructor
ModuleTool::~ModuleTool()
{
}


/// @brief Module installer
/// @param module 
/// @return result
bool ModuleTool::Install(const char* filename)
{
	bool isInstalled = false;

	//Check the module if it has been installed
	for (ElfLoader* mod = modules.Begin(); !modules.IsEnd(); mod = modules.Next())
	{
		if (0 == strcmp(filename, mod->GetFileName()))
		{
			isInstalled = true;
			debug.Output(Debug::_Lv2, "%s module has already been installed", filename);
			break;
		}
	}

	//Install module if it has not install
	if (false == isInstalled)
	{
		ElfLoader* mod = new ElfLoader();

		if (_OK == mod->Load(filename))
		{
			modules.Add(mod);
			mod->InitArray();
			debug.Output(Debug::_Lv2, "%s module install successful", filename);
			return _OK;
		}
		else
		{
			debug.Error("%s module install failed", filename);
			return _ERR;
		}
	}

	return _OK;
}


/// @brief Module uninstaller
/// @param module 
/// @return 
bool ModuleTool::Uninstall(const char* filename)
{
	for (ElfLoader* mod = modules.Begin(); !modules.IsEnd(); mod = modules.Next())
	{
		if (0 == strcmp(filename, mod->GetFileName()))
		{
			mod->FiniArray();
			modules.Remove(mod);
			debug.Output(Debug::_Lv2, "%s module uninstall successful", filename);
			return _OK;	
		}
	}

	debug.Error("%s module not found", filename);
	return _ERR;
}
