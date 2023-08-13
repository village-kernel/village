//###########################################################################
// FileSystem.cpp
// Definitions of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "FileSystem.h"
#include "Debug.h"


/// @brief Constructor
FileSystem::FileSystem()
	:disk(NULL)
{
}


/// @brief Deconstructor
FileSystem::~FileSystem()
{
}


/// @brief Singleton Instance
/// @return FileSystem instance
FileSystem& FileSystem::Instance()
{
	static FileSystem instance;
	return instance;
}
EXPORT_SYMBOL(_ZN10FileSystem8InstanceEv);


/// @brief Definitions filesystem and export
FileSystem& filesystem = FileSystem::Instance();
EXPORT_SYMBOL(filesystem);


/// @brief CHS to LBA address
/// @param path 
/// @param mount 
/// @param opt 
/// @return 
uint32_t FileSystem::CHS2LBA(uint8_t head, uint8_t sector, uint16_t cylinder)
{
	//LBA = (C × HPC + H) × SPT + (S − 1)
	return (cylinder * 16 + head) * 63 + (sector - 1);
}


/// @brief 
/// @param lba 
/// @param head 
/// @param sector 
/// @param cylinder 
void FileSystem::LBA2CHS(uint32_t lba, uint8_t& head, uint8_t& sector, uint16_t& cylinder)
{
	//C = LBA ÷ (HPC × SPT)
	//H = (LBA ÷ SPT) mod HPC
	//S = (LBA mod SPT) + 1
}


/// @brief Read MBR
int FileSystem::ReadMBR()
{
	static const uint8_t mbr_sector = 0;
	
	mbr = new MBR();

	if (NULL != mbr)
	{
		disk->Read((uint8_t*)mbr, 1, mbr_sector);
		
		if (magic == mbr->magic) return _OK;
	}

	return _ERR;
}


/// @brief File system initialize
void FileSystem::Initialize()
{
	disk = device.GetDriver(DriverID::_storage + 1);

	if (NULL == disk)
	{
		debug.Error("Not disk driver found");
		return;
	}

	if (_ERR == ReadMBR())
	{
		debug.Error("Not a valid disk");
		return;
	}

	FileOpt* opt = GetFileOpt("fat");
	if (NULL != opt)
	{
		opt->Mount("/dev/hdb", "/data", 0, mbr->dpt[0].relativeSectors);
	}
}


/// @brief File system execute
void FileSystem::Execute()
{
	while (1) {}
}


/// @brief File system exit
void FileSystem::Exit()
{
	FileOpt* opt = GetFileOpt("fat");
	if (NULL != opt)
	{
		opt->Unmount("/data");
	}
}


/// @brief Register file system
/// @param fileOpt file system opt
/// @param name file system name
void FileSystem::RegisterOpt(FileOpt* fileOpt, const char* name)
{
	fileOpts.InsertByName(fileOpt, (char*)name);
}
EXPORT_SYMBOL(_ZN10FileSystem11RegisterOptEP7FileOptPKc);


/// @brief Deregister file system
/// @param fileOpt file system opt
/// @param name file system name
void FileSystem::DeregisterOpt(FileOpt* fileOpt, const char* name)
{
	fileOpts.RemoveByName(fileOpt, (char*)name);
}
EXPORT_SYMBOL(_ZN10FileSystem13DeregisterOptEP7FileOptPKc);


/// @brief Get file opt
/// @param name file opt name
/// @return file opt
FileOpt* FileSystem::GetFileOpt(const char* name)
{
	return fileOpts.GetItemByName((char*)name);
}
EXPORT_SYMBOL(_ZN10FileSystem10GetFileOptEPKc);


///Register module
REGISTER_MODULE(&FileSystem::Instance(), ModuleID::_fileSystem, fileSystem);
