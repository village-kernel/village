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
#include "FatEntry.h"


/// @brief Constructor
FatObjs::FatObjs()
{
}


/// @brief Destructor
FatObjs::~FatObjs()
{
	Exit();
}


/// @brief Clone
/// @param objs 
void FatObjs::Clone(FatObjs* objs)
{
	this->dbr      = objs->dbr;
	this->info     = objs->info;

	this->fatDisk  = objs->fatDisk;
	this->fatName  = objs->fatName;
	this->fatEntry = objs->fatEntry;
	this->fatFile  = objs->fatFile;
	this->fatDir   = objs->fatDir;

	this->diskdrv  = objs->diskdrv;
	this->fstSec   = objs->fstSec;
}


/// @brief Setup
/// @param diskdrv 
/// @param fstSec 
void FatObjs::Setup(Driver* diskdrv, uint32_t fstSec)
{
	this->diskdrv  = diskdrv;
	this->fstSec   = fstSec;

	this->dbr      = new DBR();
	this->info     = new Info();

	this->fatDisk  = new FatDisk();
	this->fatName  = new FatName();
	this->fatEntry = new FatEntry();
	this->fatFile  = new FatFile();
	this->fatDir   = new FatDir();

	fatDisk->Clone(this);
	fatName->Clone(this);
	fatEntry->Clone(this);
	fatFile->Clone(this);
	fatDir->Clone(this);
}


/// @brief Exit
void FatObjs::Exit()
{
	delete dbr;
	delete info;

	delete fatDisk;
	delete fatName;
	delete fatEntry;
	delete fatFile;
	delete fatDir;
}
