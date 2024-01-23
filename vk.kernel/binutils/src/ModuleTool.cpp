//###########################################################################
// ModuleTool.cpp
// Definitions of the functions that manage module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "ModuleTool.h"
#include "Kernel.h"
#include "Loader.h"


/// @brief Constructor
ModuleTool::ModuleTool()
{
}


/// @brief Destructor
ModuleTool::~ModuleTool()
{
}


/// @brief Module tool get modules
List<ElfLoader*>* ModuleTool::GetModules()
{
	//Get the loader module
	Loader* loader = (Loader*)Kernel::modular.GetModuleByName("loader");
	if (NULL == loader)
	{
		Kernel::debug.Error("loader feature not support");
		return NULL;
	}

	//Get the modules pointer
	List<ElfLoader*>* modules = loader->GetModules();
	if (NULL == modules)
	{
		Kernel::debug.Error("get modules address failed");
		return NULL;
	}

	return modules;
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
		Kernel::debug.Error("%s module not a valid name", filename);
		return false;
	}

	//Get the modules pointer
	List<ElfLoader*>* modules = GetModules();
	if (NULL == modules) return false;

	//Check the module if it has been installed
	for (ElfLoader* mod = modules->Begin(); !modules->IsEnd(); mod = modules->Next())
	{
		if (0 == strcmp(filename, mod->GetFileName()))
		{
			isInstalled = true;
			Kernel::debug.Output(Debug::_Lv2, "%s module has already been installed", filename);
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
			Kernel::debug.Output(Debug::_Lv2, "%s module install successful", filename);
		}
		else
		{
			Kernel::debug.Error("%s module install failed", filename);
			return false;
		}
	}

	return true;
}


/// @brief Module uninstaller
/// @param module 
/// @return 
bool ModuleTool::Uninstall(const char* filename)
{
	//Check filename is valid
	if (NULL == filename)
	{
		Kernel::debug.Error("%s module not a valid name", filename);
		return false;
	}

	//Get the modules pointer
	List<ElfLoader*>* modules = GetModules();
	if (NULL == modules) return false;

	//Search module and remove it
	for (ElfLoader* mod = modules->Begin(); !modules->IsEnd(); mod = modules->Next())
	{
		if (0 == strcmp(filename, mod->GetFileName()))
		{
			mod->FiniArray();
			modules->Remove(mod);
			delete mod;
			Kernel::debug.Output(Debug::_Lv2, "%s module uninstall successful", filename);
			return true;	
		}
	}

	Kernel::debug.Error("%s module not found", filename);
	return false;
}
