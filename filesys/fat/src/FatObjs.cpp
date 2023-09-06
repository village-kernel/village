//###########################################################################
// FatObjs.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatObjs.h"
#include "FatDisk.h"
#include "FatName.h"
#include "FatEntry.h"
#include "FatData.h"


/// @brief Constructor
FatObjs::FatObjs()
{
}


/// @brief Destructor
FatObjs::~FatObjs()
{
}


/// @brief Clone
/// @param objs 
void FatObjs::Clone(FatObjs* objs)
{
	this->dbr      = objs->dbr;
	this->info     = objs->info;

	this->fatDisk  = objs->fatDisk;
	this->fatData  = objs->fatData;

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
	this->fatData  = new FatData();

	fatDisk->Clone(this);
	fatData->Clone(this);
}


/// @brief Exit
void FatObjs::Exit()
{
	delete dbr;
	delete info;
	delete fatDisk;
	delete fatData;
}
