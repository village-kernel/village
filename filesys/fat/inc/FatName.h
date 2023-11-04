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

	char* GetShortName(UnionEntry* entry);
	int SetShortName(UnionEntry* entry, const char* name);

	char* GetLongName(UnionEntry* entires);
	int SetLongName(UnionEntry* entires, const char* name);

	char* GetVolumeLabel(UnionEntry* entry);
	int SetVolumeLabel(UnionEntry* entry, const char* name);

	void GenNumName(UnionEntry* entry, int num);
};

#endif //!__FAT_NAME_H__
