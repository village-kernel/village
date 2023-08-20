//###########################################################################
// FatSystem.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_FILE_SYSTEM_H__
#define __FAT_FILE_SYSTEM_H__

#include "Templates.h"
#include "FileSys.h"
#include "FatDefs.h"
#include "Driver.h"


/// @brief FAT
class FatSystem : public FileSys, FatDefs
{
private:
	//Members
	MBR*     mbr;
	FatDat*  fats;
	Driver*  diskdrv;

	//Methods
	int ReadMBR();
public:
	//Methods
	FatSystem();
	~FatSystem();
	void Setup();
	void Exit();
};

#endif //!__FAT_FILE_SYSTEM_H__
