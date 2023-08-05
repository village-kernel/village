//###########################################################################
// FatFile.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_FILE_H__
#define __FAT_FILE_H__

#include "Templates.h"
#include "FatDefs.h"
#include "FatDisk.h"

/// @brief FatFile
class FatFile : FatDefs
{
private:
	//Members
	FatDisk disk;
public:
	//Methods
	void Initialize(FATData* fat, DBR* dbr, uint32_t fstSecNum);
	
	//File Methods
	int Read(char* data, uint32_t size, DirEntry* entry);
	uint32_t Size(DirEntry* entry);
};

#endif //!__FAT_FILE_H__
