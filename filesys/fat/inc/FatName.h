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

	char* GetShortName(FATEnt* entry);
	int SetShortName(FATEnt* entry, const char* name);

	char* GetLongName(FATEnt* entires);
	int SetLongName(FATEnt* entires, const char* name);

	char* GetVolumeLabel(FATEnt* entry);
	int SetVolumeLabel(FATEnt* entry, const char* name);

	void GenNumName(FATEnt* entry, int num);
};

#endif //!__FAT_NAME_H__
