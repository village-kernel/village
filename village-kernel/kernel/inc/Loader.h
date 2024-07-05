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
	//Members
	List<ElfLoader*> libraries;
	List<ElfLoader*> modules;
	LibraryTool      libraryTool;
	ModuleTool       moduleTool;

	//Methods
	void Execute();
public:
	//Methods
	ConcreteLoader();
	~ConcreteLoader();
	void Setup();
	void Exit();
	void Loading(int type, const char* filename);
	List<ElfLoader*>* GetLibraries();
	List<ElfLoader*>* GetModules();
};

#endif //!__LOADER_H__
