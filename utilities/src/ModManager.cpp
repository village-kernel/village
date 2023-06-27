//###########################################################################
// ModManager.cpp
// Definitions of the functions that manage module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Debug.h"
#include "ModManager.h"


/// @brief Initialize modules
List<ElfParser> ModManager::modules;


/// @brief Constructor
ModManager::ModManager()
{
}


/// @brief Deconstructor
ModManager::~ModManager()
{
}


/// @brief Module installer
/// @param module 
/// @return result
bool ModManager::Install(const char* filename)
{
	bool isInstalled = false;

	//Check the module if it has been installed
	for (ElfParser* mod = modules.Begin(); !modules.IsEnd(); mod = modules.Next())
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
		ElfParser* mod = new ElfParser();

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
bool ModManager::Uninstall(const char* filename)
{
	for (ElfParser* mod = modules.Begin(); !modules.IsEnd(); mod = modules.Next())
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
