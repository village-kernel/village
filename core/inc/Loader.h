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

///Loader
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
	LibraryTool libraries;
	ModuleTool  modules;

	//Methods
	Loader();
	~Loader();
	void Loading(int type, const char* filename);
public:
	//Methods
	void Initialize();

	//Singleton Instance
	static Loader& Instance();
};

///Declarations loader reference
extern Loader& loader;

#endif //!__LOADER_H__
