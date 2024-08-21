//###########################################################################
// FileSystem.h
// Declarations of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include "FileDefs.h"
#include "FileSys.h"
#include "List.h"
#include "Kernel.h"


/// @brief ConcreteFileSystem
class ConcreteFileSystem : public FileSystem
{
	private:
	/// @brief Enumerates
	enum BootIndicator
	{
		_NotBootable = 0x00,
		_Bootable    = 0x80,
	};

	/// @brief Structures
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
private:
	/// @brief Members
	List<FileSys*>    fileSys;
	List<FileVol*>    volumes;
	List<MountNode*>  mounts;

	/// @brief Methods
	bool InitMBRDisk(const char* disk);
	bool MountSystemNode();
public:
	/// @brief Methods
	ConcreteFileSystem();
	~ConcreteFileSystem();
	void Setup();
	void Exit();
	
	/// @brief Register Methods
	void RegisterFS(FileSys* fs, const char* name);
	void DeregisterFS(FileSys* fs, const char* name);
	
	/// @brief Volume Methods
	int AttachVolume(FileVol* volume);
	int DetachVolume(FileVol* volume);
	FileVol* GetVolume(const char* name);
};

#endif //!__FILE_SYSTEM_H__
