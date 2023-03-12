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
public:
	void Initialize();
	void LoadModule();
	void LoadDevice();
	void LoadLibrary();
};

#endif //!__LOADER_H__
