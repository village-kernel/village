//###########################################################################
// FatSystem.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_FILE_SYSTEM_H__
#define __FAT_FILE_SYSTEM_H__

#include "FileSystem.h"


/// @brief FatSystem
class FatSystem : public FileSystem
{
public:
	//Methods
	FatSystem();
	~FatSystem();
	uint32_t GetSystemID();
	FileVolume* CreateVolume();
};

#endif //!__FAT_FILE_SYSTEM_H__
