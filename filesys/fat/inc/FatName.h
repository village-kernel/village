//###########################################################################
// FatName.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_NAME_H__
#define __FAT_NAME_H__

#include "FatDefs.h"


/// @brief FatName
class FatName : public FatDefs
{
public:
	//Methods
	uint8_t ChkSum(char* name);

	char* GetShortName(UnionEntry* unient);
	int SetShortName(UnionEntry* unient, const char* sfn);

	char* GetLongName(UnionEntry* unients);
	int SetLongName(UnionEntry* unients, const char* lfn);

	char* GetVolumeLabel(UnionEntry* unient);
	int SetVolumeLabel(UnionEntry* unient, const char* lbn);

	void GenNumName(UnionEntry* unient, int num);
};

#endif //!__FAT_NAME_H__
