//###########################################################################
// FatSystem.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_FILE_SYSTEM_H__
#define __FAT_FILE_SYSTEM_H__

#include "FileSys.h"
#include "Driver.h"


/// @brief FatSystem
class FatSystem : public FileSys
{
private:
	//Enumerates
	enum BootIndicator
	{
		_NotBootable = 0x00,
		_Bootable    = 0x80,
	};

	//Structures
	struct DPT
	{
		uint32_t bootIndicator : 8;
		uint32_t startingHead : 8;
		uint32_t startingSector : 6;
		uint32_t startingCylinder: 10;
		uint32_t systemID : 8;
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

	struct FAT32FSInfo
	{
		uint32_t leadSig;
		uint8_t  reserved1[480];
		uint32_t structSig;
		uint32_t freeCount;
		uint32_t nextFree;
		uint8_t  reserved2[12];
		uint32_t trailSig;
	} __attribute__((packed));
private:
	//Static constants
	static const uint16_t magic = 0xaa55;

	//Members
	MBR*     mbr;
	Driver*  diskdrv;

	//Methods
	int ReadMBR();
	int CheckDPT(DPT* dpt);
public:
	//Methods
	FatSystem();
	~FatSystem();
	void Setup();
	void Exit();
};

#endif //!__FAT_FILE_SYSTEM_H__
