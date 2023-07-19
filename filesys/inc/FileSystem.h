//###########################################################################
// FileSystem.h
// Declarations of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include "Module.h"
#include "Driver.h"
#include "FileOpt.h"
#include "FileDefs.h"


/// @brief FileSystem
class FileSystem : public Module
{
private:
	struct DPT
	{
		uint32_t bootIndicator : 8;
		uint32_t startingHead : 8;
		uint32_t startingSector : 6;
		uint32_t startingCylinder: 10;
		uint32_t sectorID : 8;
		uint32_t endingHead : 8;
		uint32_t endingSector : 6;
		uint32_t endingCylinder : 10;
		uint32_t relativeSectors;
		uint32_t totalSectors;
	} __attribute__((packed));

	struct MBR
	{
		uint8_t  boot[446];
		DPT      dpt[4];
		uint16_t magic;
	} __attribute__((packed));

	//Static constants
	static const uint16_t magic = 0xaa55;

	//Members
	Driver*       disk;
	MBR*          mbr;
	List<FileOpt> fileOpts;
	
	//Methods
	FileSystem();
	~FileSystem();
	int ReadMBR();
	uint32_t CHS2LBA(uint8_t head, uint8_t sector, uint16_t cylinder);
	void LBA2CHS(uint32_t lba, uint8_t& head, uint8_t& sector, uint16_t& cylinder);
public:
	//Methods
	void Initialize();
	void Execute();
	void Exit();
	void RegisterOpt(FileOpt* fileOpt, const char* name);
	void DeregisterOpt(FileOpt* fileOpt, const char* name);
	FileOpt* GetFileOpt(const char* name);

	//Singleton Instance
	static FileSystem& Instance();
};

///Declarations FileSystem reference
extern FileSystem& filesystem;

#endif //!__FILE_SYSTEM_H__
