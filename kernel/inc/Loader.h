//###########################################################################
// Loader.h
// Declarations of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LOADER_H__
#define __LOADER_H__

#include "Module.h"


///Loader
class Loader : public Module
{
private:

public:
	//Methods
	void Initialize();
	void LoadLibraries();
	void LoadModules();
};

#endif //!__LOADER_H__
