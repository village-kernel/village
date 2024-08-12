//###########################################################################
// Loader.h
// Declarations of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LOADER_H__
#define __LOADER_H__

#include "Kernel.h"
#include "rcParser.h"
#include "LibraryTool.h"
#include "ModuleTool.h"
#include "List.h"


/// @brief ConcreteLoader
class ConcreteLoader : public Loader, public Class
{
private:
	/// @brief Members
	List<ElfLoader*> libraries;
	List<ElfLoader*> modules;
	LibraryTool      libraryTool;
	ModuleTool       moduleTool;

	/// @brief Methods
	void Execute();
public:
	/// @brief Methods
	ConcreteLoader();
	~ConcreteLoader();
	void Setup();
	void Exit();

	/// @brief Load Methods
	void Load(int type, const char* filename);
	void Unload(int type, const char* filename);

	/// @brief Install Methods
	bool Install(int type, const char* filename);
	bool Uninstall(int type, const char* filename);

	/// @brief Data Methods
	List<ElfLoader*>* GetLibraries();
	List<ElfLoader*>* GetModules();
};

#endif //!__LOADER_H__
