//###########################################################################
// FatFile.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_FILE_H__
#define __FAT_FILE_H__

#include "FatDefs.h"


/// @brief FatFile
class FatFile : public FatDat
{
public:
	//File Methods
	DirEntry* Open(const char* name, int mode);
	int Read(char* data, uint32_t size, DirEntry* entry);
	uint32_t Size(DirEntry* entry);
};

#endif //!__FAT_FILE_H__
