//###########################################################################
// Loader.h
// Declarations of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LOADER_H__
#define __LOADER_H__

#include "stdint.h"
#include "stddef.h"

///Loader
class Loader
{
public:
	static void Initialize();
	static void LoadModule();
	static void LoadDevice();
	static void LoadLibrary();
};

#endif //!__LOADER_H__
