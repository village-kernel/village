//###########################################################################
// LibraryTool.cpp
// Definitions of the functions that manage library
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Debug.h"
#include "Loader.h"
#include "LibraryTool.h"


/// @brief Constructor
LibraryTool::LibraryTool()
{
}


/// @brief Deconstructor
LibraryTool::~LibraryTool()
{
}


/// @brief library installer
/// @param library 
/// @return result
bool LibraryTool::Install(const char* filename)
{
	bool isInstalled = false;

	//Check filename is valid
	if (NULL == filename)
	{
		debug.Error("%s library not a valid name", filename);
		return false;
	}

	//Get the libraries pointer
	List<ElfLoader*>* libraries = loader.GetLibraries();

	//Check the library if it has been installed
	for (ElfLoader* library = libraries->Begin(); !libraries->IsEnd(); library = libraries->Next())
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
		ElfLoader* library = new ElfLoader();

		library->IgnoreUnresolvedSymbols();

		if (_OK == library->Load(filename))
		{
			library->FillBssZero();
			library->InitArray();
			libraries->Add(library);
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
bool LibraryTool::Uninstall(const char* filename)
{
	//Get the libraries pointer
	List<ElfLoader*>* libraries = loader.GetLibraries();

	//Search library and remove it
	for (ElfLoader* library = libraries->Begin(); !libraries->IsEnd(); library = libraries->Next())
	{
		if (0 == strcmp(filename, library->GetFileName()))
		{
			library->FiniArray();
			libraries->Remove(library);
			delete library;
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
uint32_t LibraryTool::SearchSymbol(const char* symbol)
{
	//Get the libraries pointer
	List<ElfLoader*>* libraries = loader.GetLibraries();

	//Search symbol
	for (ElfLoader* lib = libraries->Begin(); !libraries->IsEnd(); lib = libraries->Next())
	{
		uint32_t symAddr = lib->GetDynSymAddrByName(symbol);
		if (0 != symAddr) return symAddr;
	}
	return 0;
}
