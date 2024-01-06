//###########################################################################
// ModuleTool.cpp
// Definitions of the functions that manage module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Debug.h"
#include "Loader.h"
#include "ModuleTool.h"


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

	//Check filename is valid
	if (NULL == filename)
	{
		debug.Error("%s module not a valid name", filename);
		return false;
	}

	//Get the libraries pointer
	List<ElfLoader*>* modules = loader.GetModules();

	//Check the module if it has been installed
	for (ElfLoader* mod = modules->Begin(); !modules->IsEnd(); mod = modules->Next())
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
			mod->FillBssZero();
			mod->InitArray();
			modules->Add(mod);
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
	//Get the libraries pointer
	List<ElfLoader*>* modules = loader.GetModules();

	//Search module and remove it
	for (ElfLoader* mod = modules->Begin(); !modules->IsEnd(); mod = modules->Next())
	{
		if (0 == strcmp(filename, mod->GetFileName()))
		{
			mod->FiniArray();
			modules->Remove(mod);
			delete mod;
			debug.Output(Debug::_Lv2, "%s module uninstall successful", filename);
			return _OK;	
		}
	}

	debug.Error("%s module not found", filename);
	return _ERR;
}
