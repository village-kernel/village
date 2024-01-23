//###########################################################################
// FAT.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSystem.h"
#include "FatSystem.h"
#include "FatVolume.h"
#include "Kernel.h"
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
	FileSystem* filesys = (FileSystem*)Kernel::modular.GetModuleByName("fileSystem");
	if (NULL == filesys)
	{
		Kernel::debug.Error("file system feature not support");
		return;
	}

	diskdrv = Kernel::device.GetDriver(DriverID::_storage + 1);
	if (NULL == diskdrv)
	{
		Kernel::debug.Error("Not disk driver found");
		return;
	}

	if (_ERR == ReadMBR())
	{
		Kernel::debug.Error("Not a valid disk");
		return;
	}

	for (uint8_t i = 0; i < 4; i++)
	{
		if (_OK == CheckDPT(&mbr->dpt[i]))
		{
			FatVolume* fatOpts = new FatVolume();

			if (_OK != fatOpts->Setup(diskdrv, mbr->dpt[i].relativeSectors))
			{
				delete fatOpts;
				continue;
			}

			filesys->RegisterOpts(fatOpts);
		}
	}

	Kernel::debug.Output(Debug::_Lv2, "Initialize FAT file system successful");
}


/// @brief FAT exit
void FatSystem::Exit()
{
	delete mbr;
}


/// @brief Read MBR
int FatSystem::ReadMBR()
{
	static const uint8_t mbr_sector = 0;

	mbr = new MBR();

	if (NULL != mbr)
	{
		diskdrv->Read((uint8_t*)mbr, 1, mbr_sector);

		if (magic == mbr->magic) return _OK;
	}

	return _ERR;
}


/// @brief 
/// @param dpt 
/// @return 
int FatSystem::CheckDPT(DPT* dpt)
{
	if (dpt->systemID == 11)
	{
		return _OK;
	}
	return _ERR;
}


///Register file system
REGISTER_FS(new FatSystem(), fat);
