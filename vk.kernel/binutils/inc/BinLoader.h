//###########################################################################
// BinLoader.h
// Declarations of the functions that manage bin loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __BIN_LOADER_H__
#define __BIN_LOADER_H__

#include "Defines.h"

/// @brief BinLoader
class BinLoader
{
private:
	//Type define
	typedef void(*Entry)(int argc, char* argv[]);

	//ELF structure
	struct BIN
	{
		uint32_t load;
		uint32_t exec;
	};
private:
	//Members
	BIN   bin;
	char* filename;

	//Methods
	int LoadBin();
public:
	//Methods
	BinLoader(const char* filename = NULL);
	~BinLoader();
	int Load(const char* filename);
	int Execute(int argc = 0, char* argv[] = NULL);
	int Exit();
};

#endif //!__BIN_LOADER_H__
