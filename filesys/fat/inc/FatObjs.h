//###########################################################################
// FatObjs.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_OBJS_H__
#define __FAT_OBJS_H__

#include "FatDefs.h"

/// @brief Declarations
class FatDisk;
class FatName;
class FatEntry;
class FatFile;
class FatDir;


/// @brief FatObjs
class FatObjs : public FatDefs
{
protected:
	//Data Members
	DBR*     dbr;
	Info*    info;

	//Class Members
	FatDisk*  fatDisk;
	FatName*  fatName;
	FatEntry* fatEntry;
	FatFile*  fatFile;
	FatDir*   fatDir;

	//Driver Members
	Driver*  diskdrv;
	uint32_t fstSec;

	//Methods
	void Clone(FatObjs* objs);
public:
	//Methods
	FatObjs();
	~FatObjs();
	void Setup(Driver* diskdrv, uint32_t fstSec);
	void Exit();
};

#endif //!__FAT_OBJS_H__
