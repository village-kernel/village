//###########################################################################
// FatName.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_NAME_H__
#define __FAT_NAME_H__

#include "Templates.h"
#include "FatDefs.h"
#include "FatDisk.h"

/// @brief FatName
class FatName : FatDefs
{
private:
	//Members
	FatDisk  disk;

	//Methods
	uint8_t ChkSum(char* name);
	char* GetShortName(FATSDir* sdir);
	char* GetLongName(FATLDir* ldir, FATSDir* sdir);
public:
	void Initialize(FATData* fat, FATDBR* dbr, uint32_t startSector);

	//Methods
	char* GetDirName(DirData* data);
};

#endif //!__FAT_NAME_H__
