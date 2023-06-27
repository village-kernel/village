//###########################################################################
// Loader.h
// Declarations of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LOADER_H__
#define __LOADER_H__

#include "Templates.h"

///Loader
class Loader
{
private:
	//Methods
	Loader();
	~Loader();
	void LoadingLib(const char* filename);
	void LoadingMod(const char* filename);
public:
	//Methods
	void Initialize();

	//Singleton Instance
	static Loader& Instance();
};

///Declarations loader reference
extern Loader& loader;

#endif //!__LOADER_H__
