//###########################################################################
// ModInstaller.cpp
// Definitions of the functions that manage module installer
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Debug.h"
#include "ModInstaller.h"


/// @brief Initialize modules
List<ElfParser> ModInstaller::modules;


/// @brief Constructor
ModInstaller::ModInstaller()
{
}


/// @brief Deconstructor
ModInstaller::~ModInstaller()
{
}


/// @brief Module installer
/// @param module 
/// @return result
bool ModInstaller::Install(const char* module)
{
	bool isInstalled = false;

	//Check the module if it has been installed
	for (ElfParser* mod = modules.Begin(); !modules.IsEnd(); mod = modules.Next())
	{
		if (0 == strcmp(module, mod->GetFileName()))
		{
			isInstalled = true;
			break;
		}
	}

	//Install module if it has not install
	if (false == isInstalled)
	{
		ElfParser* mod = new ElfParser();

		if (_OK == mod->Load(module))
		{
			modules.Add(mod);
			mod->InitArray();
			debug.Output(Debug::_Lv2, "%s module install successful", module);
			return _OK;
		}
		else
		{
			debug.Error("%s module install failed", module);
			return _ERR;
		}
	}

	return _OK;
}


/// @brief Module uninstaller
/// @param module 
/// @return 
bool ModInstaller::Uninstall(const char* module)
{
	for (ElfParser* mod = modules.Begin(); !modules.IsEnd(); mod = modules.Next())
	{
		if (0 == strcmp(module, mod->GetFileName()))
		{
			mod->FiniArray();
			modules.Remove(mod);
			debug.Output(Debug::_Lv2, "%s module uninstall successful", module);
			return _OK;	
		}
	}

	debug.Error("%s module not found", module);
	return _ERR;
}
