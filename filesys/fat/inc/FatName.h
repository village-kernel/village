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
private:
	//Methods
	uint8_t ChkSum(char* name);
	char* GetShortName(FATSDir* sdir);
	char* GetLongName(FATLDir* ldir, FATSDir* sdir);
	void SetShortName(FATSDir* sdir, char* name);
	void SetLongName(FATLDir* ldir, FATSDir* sdir, char* name);
public:
	//Methods
	char* GetDirName(DirData* data);
	void SetDirName(DirData* data, char* name);
};

#endif //!__FAT_NAME_H__
