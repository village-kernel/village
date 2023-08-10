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

/// @brief FatName
class FatName : FatDefs
{
private:
	//Methods
	uint8_t ChkSum(char* name);
public:
	//Methods
	char* GetShortName(FATSDir* sdir);
	char* GetLongName(FATLDir* ldir, FATSDir* sdir);
};

#endif //!__FAT_NAME_H__
