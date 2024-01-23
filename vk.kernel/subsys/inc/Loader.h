//###########################################################################
// Loader.h
// Declarations of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LOADER_H__
#define __LOADER_H__

#include "Module.h"
#include "Templates.h"
#include "LibraryTool.h"
#include "ModuleTool.h"
#include "ElfLoader.h"
#include "Executor.h"


/// @brief Loader
class Loader : public Module
{
private:
	//Enumerations
	enum LoadType
	{
		_Load_Lib = 0,
		_Load_Mod,
	};

	//Members
	List<ElfLoader*> libraries;
	List<ElfLoader*> modules;
	LibraryTool      libraryTool;
	ModuleTool       moduleTool;
	Executor         executor;

	//Methods
	void Loading(int type, const char* filename);
public:
	//Methods
	Loader();
	~Loader();
	void Initialize();
	void Execute();

	List<ElfLoader*>* GetLibraries();
	List<ElfLoader*>* GetModules();
};

#endif //!__LOADER_H__
