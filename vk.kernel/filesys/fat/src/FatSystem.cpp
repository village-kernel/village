//###########################################################################
// FAT.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatSystem.h"
#include "FatVolume.h"
#include "FileSys.h"
#include "Kernel.h"


/// @brief Constructor
FatSystem::FatSystem()
{
}


/// @brief Destructor
FatSystem::~FatSystem()
{
}


/// @brief GetSystemID
/// @return system id
uint32_t FatSystem::GetSystemID()
{
	const static uint32_t systemID = 11;
	return systemID;
}


/// @brief CreateVolume
/// @return fat volume
FileVolume* FatSystem::CreateVolume()
{
	return new FatVolume();
}


///Register file system
REGISTER_FS(new FatSystem(), fat);
