//###########################################################################
// FatObjs.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatObjs.h"
#include "FatDir.h"
#include "FatDisk.h"
#include "FatName.h"
#include "FatFile.h"


/// @brief Create
/// @param diskdrv 
/// @param fstSec 
void FatObjs::Create(Driver* diskdrv, uint32_t fstSec)
{
	this->dbr     = new DBR();
	this->info    = new Info();

	this->fatDisk = new FatDisk();
	this->fatName = new FatName();
	this->fatFile = new FatFile();
	this->fatDir  = new FatDir();

	this->diskdrv = diskdrv;
	this->fstSec  = fstSec;
}


/// @brief Setup
/// @param objs 
void FatObjs::Setup(FatObjs* objs)
{
	this->dbr     = objs->dbr;
	this->info    = objs->info;

	this->fatDisk = objs->fatDisk;
	this->fatName = objs->fatName;
	this->fatFile = objs->fatFile;
	this->fatDir  = objs->fatDir;

	this->diskdrv = objs->diskdrv;
	this->fstSec  = objs->fstSec;
}


/// @brief 
/// @param dat 
void FatObjs::Setup()
{
	fatDisk->Setup(this);
	fatName->Setup(this);
	fatFile->Setup(this);
	fatDir->Setup(this);
}


/// @brief Destroy
void FatObjs::Destroy()
{
	delete dbr;
	delete info;

	delete fatDisk;
	delete fatName;
	delete fatFile;
	delete fatDir;
}
