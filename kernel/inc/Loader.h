//###########################################################################
// Loader.h
// Declarations of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LOADER_H__
#define __LOADER_H__

#include "Module.h"
#include "rcParser.h"
#include "ElfParser.h"


///Loader
class Loader
{
protected:
	//Methods
	void Loading(const char* filename);
};


///Drivers laoder
class DrvLoader : public Loader, public Driver
{
public:
	//Methods
	void Initialize();
};


///Module loader
class ModLoader : public Loader, public Module
{
public:
	//Methods
	void Initialize();
};

#endif //!__LOADER_H__
