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
	/// @brief BootIndicator
	enum BootIndicator
	{
		_NotBootable = 0x00,
		_Bootable    = 0x80,
	};


	/// @brief PartitionTableType
	enum PartitionType
	{
		_None = 0,
		_MBR,
		_GPT,
	};


	/// @brief MBR Partition record
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
		uint32_t startingLBA;
		uint32_t sizeInLBA;
	} __attribute__((packed));


	/// @brief MBR Partition table
	struct MBR
	{
		uint8_t  boot[424];
		uint8_t  reserved[16];
		uint32_t uniqueMBRDiskSignature;
		uint16_t unknown;
		DPT      partition[4];
		uint16_t magic;
	} __attribute__((packed));


	/// @brief GPT
	struct GPT
	{
		char     signature[8];
		uint32_t revision;
		uint32_t headerSize;
		uint32_t headerCRC32;
		uint32_t reserved0;
		uint64_t myLBA;
		uint64_t alternateLBA;
		uint64_t firstUsableLBA;
		uint64_t lastUsableLBA;
		char     diskGUID[16];
		uint64_t PartitionEntryLBA;
		uint32_t numberOfPartitionEntries;
		uint32_t sizeOfPartitionEntry;
		uint32_t partitionEntryArrayCRC32;
		char     reserved1[420];
	};


	/// @brief GPT Entry
	struct GPTEntry
	{
		char     partitionTypeGUID[16];
		char     uniquePartitionGUID[16];
		uint64_t startingLBA;
		uint64_t endingLBA;
		uint64_t attributes;
		char     partitionName[72];
		char     reserved[384];
	};


	/// @brief MountNode
	struct MountNode
	{
		char*    target;
		char*    source;
		uint16_t access;

		MountNode(char* target, char* source, uint16_t access)
			:target(target),
			source(source),
			access(access)
		{}
	};


	/// @brief DiskMedia
	struct DiskMedia
	{
		int            type;
		char*          name;
		List<FileVol*> vols;

		DiskMedia(int type, char* name)
			:type(type),
			name(name)
		{}
	};
private:
	/// @brief Members
	List<FileSys*>    filesyses;
	List<DiskMedia*>  medias;
	List<MountNode*>  mounts;

	/// @brief Methods
	int  SetupVolume(DiskMedia* media, DPT partition);
	bool MountSystemNode();
public:
	/// @brief Methods
	ConcreteFileSystem();
	~ConcreteFileSystem();
	void Setup();
	void Exit();

	/// @brief Register Methods
	void RegisterFS(FileSys* fs, const char* name);
	void UnregisterFS(FileSys* fs, const char* name);

	/// @brief Hard Drive Methods
	bool MountHardDrive(const char* disk);
	bool UnmountHardDrive(const char* disk);
	
	/// @brief Volume Methods
	FileVol* GetVolume(const char* name);
};

#endif //!__FILE_SYSTEM_H__
