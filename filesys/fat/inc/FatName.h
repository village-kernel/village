//###########################################################################
// FatName.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_NAME_H__
#define __FAT_NAME_H__

#include "FatObjs.h"


/// @brief FatName
class FatName : public FatObjs
{
public:
	//Methods
	uint8_t ChkSum(char* name);

	char* GetShortName(FATSDir* sdir);
	int SetShortName(FATSDir* sdir, const char* name);

	char* GetLongName(FATLDir* ldir, FATSDir* sdir);
	int SetLongName(FATLDir* ldir, FATSDir* sdir, const char* name);

	char* GetVolumeLabel(FATSDir* sdir);
	int SetVolumeLabel(FATSDir* sdir, const char* name);

	char* GetDirName(DirData* data);
	int SetDirName(DirData* data, const char* name);
};

#endif //!__FAT_NAME_H__
