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
class Loader : public Module
{
private:
	//Members
	RcParser  rc;
	ElfParser elf;
public:
	//Methods
	Loader();
	void Initialize();
	void ExecuteApp();
};

#endif //!__LOADER_H__
