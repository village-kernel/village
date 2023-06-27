//###########################################################################
// LibManager.cpp
// Definitions of the functions that manage library
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Debug.h"
#include "LibManager.h"


/// @brief Initialize librarys
List<ElfParser> LibManager::libraries;


/// @brief Constructor
LibManager::LibManager()
{
}


/// @brief Deconstructor
LibManager::~LibManager()
{
}


/// @brief library installer
/// @param library 
/// @return result
bool LibManager::Install(const char* filename)
{
	bool isInstalled = false;

	//Check the library if it has been installed
	for (ElfParser* library = libraries.Begin(); !libraries.IsEnd(); library = libraries.Next())
	{
		if (0 == strcmp(filename, library->GetFileName()))
		{
			isInstalled = true;
			debug.Output(Debug::_Lv2, "%s library has already been installed", filename);
			break;
		}
	}

	//Install library if it has not install
	if (false == isInstalled)
	{
		ElfParser* library = new ElfParser();

		if (_OK == library->Load(filename))
		{
			libraries.Add(library);
			debug.Output(Debug::_Lv2, "%s library install successful", filename);
			return _OK;
		}
		else
		{
			debug.Error("%s library install failed", filename);
			return _ERR;
		}
	}

	return _OK;
}


/// @brief library uninstaller
/// @param library 
/// @return 
bool LibManager::Uninstall(const char* filename)
{
	for (ElfParser* library = libraries.Begin(); !libraries.IsEnd(); library = libraries.Next())
	{
		if (0 == strcmp(filename, library->GetFileName()))
		{
			libraries.Remove(library);
			debug.Output(Debug::_Lv2, "%s library uninstall successful", filename);
			return _OK;	
		}
	}

	debug.Error("%s library not found", filename);
	return _ERR;
}


/// @brief Search symbol
/// @param symbol 
/// @return symbol address
uint32_t LibManager::SearchSymbol(const char* symbol)
{
	for (ElfParser* lib = libraries.Begin(); !libraries.IsEnd(); lib = libraries.Next())
	{
		uint32_t symAddr = lib->GetDynSymAddrByName(symbol);
		if (0 != symAddr) return symAddr;
	}
	return 0;
}
