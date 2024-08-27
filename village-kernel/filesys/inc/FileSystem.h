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

	/// @brief DPT
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

	/// @brief MBR
	struct MBR
	{
		uint8_t  boot[446];
		DPT      dpt[4];
		uint16_t magic;
	} __attribute__((packed));

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
	List<FileSys*>    fileSys;
	List<DiskMedia*>  medias;
	List<MountNode*>  mounts;

	/// @brief Methods
	int  AttachVolume(DiskMedia* media, FileVol* volume);
	int  DetachVolume(DiskMedia* media, FileVol* volume);
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
