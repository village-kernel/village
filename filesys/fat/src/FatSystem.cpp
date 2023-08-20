//###########################################################################
// FAT.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSystem.h"
#include "FatSystem.h"
#include "FatOpts.h"
#include "Kernel.h"
#include "Debug.h"
#include "stdio.h"


/// @brief Constructor
FatSystem::FatSystem()
{
}


/// @brief Destructor
FatSystem::~FatSystem()
{
}


/// @brief Setup
void FatSystem::Setup()
{
	diskdrv = device.GetDriver(DriverID::_storage + 1);

	if (NULL == diskdrv)
	{
		debug.Error("Not disk driver found");
		return;
	}

	mbr = new MBR();

	if (_ERR == ReadMBR())
	{
		debug.Error("Not a valid disk");
		return;
	}

	fats          = new FatDat();
	fats->dbr     = new DBR();
	fats->info    = new Info();

	fats->diskdrv = diskdrv;
	
	fats->fatDisk = new FatDisk();
	fats->fatName = new FatName();
	fats->fatDir  = new FatDir();
	fats->fatFile = new FatFile();

	fats->info->startSector = mbr->dpt[0].relativeSectors;

	fats->fatDisk->Setup(fats);
	fats->fatName->Setup(fats);
	fats->fatDir->Setup(fats);
	fats->fatFile->Setup(fats);

	FatOpts* fatOpts = new FatOpts(fats);
	filesystem.RegisterOpts(fatOpts, "SD");

	debug.Output(Debug::_Lv2, "Fat setup done");
}


/// @brief FAT exit
void FatSystem::Exit()
{
	delete mbr;
	delete fats;
}


/// @brief Read MBR
int FatSystem::ReadMBR()
{
	static const uint8_t mbr_sector = 0;

	if (NULL != mbr)
	{
		diskdrv->Read((uint8_t*)mbr, 1, mbr_sector);

		if (magic == mbr->magic) return _OK;
	}

	return _ERR;
}


///Register file system
REGISTER_FS(new FatSystem(), fat);
