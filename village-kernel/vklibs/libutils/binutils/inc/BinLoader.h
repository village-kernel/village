//###########################################################################
// BinLoader.h
// Declarations of the functions that manage bin loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __BIN_LOADER_H__
#define __BIN_LOADER_H__

#include "ElfDefines.h"


/// @brief BinLoader
class BinLoader : public ElfDefines
{
private:
	//ELF structure
	struct BIN
	{
		uint32_t load;
		uint32_t exec;

		uint32_t offset;
		uint32_t dynamic;
		uint32_t entry;
	};
private:
	//Members
	BIN   bin;
	char* filename;

	//Methods
	bool LoadBin();
	bool PreParser();
	bool RelEntries();
public:
	//Methods
	BinLoader(const char* filename = NULL);
	~BinLoader();
	bool Load(const char* filename);
	bool Execute(int argc = 0, char* argv[] = NULL);
	bool Exit();
};

#endif //!__BIN_LOADER_H__
