//###########################################################################
// FileSys.cpp
// Definitions of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSys.h"
#include "Kernel.h"
#include "List.h"
#include "DrvStream.h"


/// @brief ConcreteFileSys
class ConcreteFileSys : public FileSys
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
private:
	//Static constants
	static const uint16_t magic = 0xaa55;

	//Members
	MBR*              mbr;
	DrvStream         diskdrv;
	List<FileSystem*> fileSys;
	List<FileVolume*> volumes;
	List<MountNode*>  mounts;
private:
	/// @brief 
	/// @return 
	bool InitDisk()
	{ 
		if (diskdrv.Open("disk0", FileMode::_ReadWrite)) return true;

		kernel->debug.Error("Not disk driver found");

		return false;
	}


	/// @brief 
	/// @return 
	bool ReadMBR()
	{
		static const uint8_t mbr_sector = 0;

		mbr = new MBR();

		if (NULL != mbr)
		{
			diskdrv.Read((char*)mbr, 1, mbr_sector);

			if (magic == mbr->magic) return true;
		}

		kernel->debug.Error("Not a valid disk");

		return false;
	}

	
	/// @brief Init volumes
	void InitVolumes()
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			FileSystem* fs = fileSys.GetItem(mbr->dpt[i].systemID);

			if (NULL != fs)
			{
				FileVolume* volume = fs->CreateVolume();

				if (volume->Setup(&diskdrv, mbr->dpt[i].relativeSectors))
				{
					AttachVolume(volume);
				}
				else delete volume;
			}
		}
	}


	/// @brief Mount node
	void MountSystemNode()
	{
		//Mount root node "/"
		for (volumes.Begin(); !volumes.IsEnd(); volumes.Next())
		{
			char* volumelab = volumes.GetName();
			if (0 == strcmp(volumelab, "/media/VILLAGE OS"))
			{
				mounts.Add(new MountNode((char*)"/", volumelab, 0755));
				return;
			}
		}
		kernel->debug.Output(Debug::_Lv2, "Mount system node failed, '/media/VILLAGE OS' not found");
	}
public:
	/// @brief Constructor
	ConcreteFileSys()
	{
	}


	/// @brief Destructor
	~ConcreteFileSys()
	{
	}


	/// @brief File system setup
	void Setup()
	{
		if (!InitDisk()) return;

		if (!ReadMBR()) return;

		InitVolumes();

		MountSystemNode();
	}


	/// @brief File system exit
	void Exit()
	{
		for (volumes.Begin(); !volumes.IsEnd(); volumes.Next())
		{
			FileVolume* volume = volumes.Item();

			volume->Exit();
		}

		fileSys.Release();
	}


	/// @brief Register file system
	/// @param fs file system
	/// @param name file system name
	void RegisterFS(FileSystem* fs, const char* name)
	{
		fileSys.Insert(fs, fs->GetSystemID(), (char*)name);
	}


	/// @brief Deregister file system
	/// @param fs file system
	/// @param name file system name
	void DeregisterFS(FileSystem* fs, const char* name)
	{
		fileSys.RemoveByName(fs, (char*)name);
	}


	/// @brief Attach volume
	/// @param volume
	int AttachVolume(FileVolume* volume)
	{
		char* prefix = (char*)"/media/";
		char* label  = volume->GetVolumeLabel();
		char* name   = new char[strlen(prefix) + strlen(label) + 1]();
		strcat(name, prefix);
		strcat(name, label);
		return volumes.InsertByName(volume, name);
	}


	/// @brief Detach volume
	/// @param volume
	int DetachVolume(FileVolume* volume)
	{
		return volumes.Remove(volume);
	}


	/// @brief Get File Opts
	/// @param name 
	/// @return 
	FileVolume* GetVolume(const char* name)
	{
		for (MountNode* mount = mounts.Begin(); !mounts.IsEnd(); mount = mounts.Next())
		{
			if (0 == strncmp(mount->target, name, strlen(mount->target)))
			{
				return volumes.GetItemByName(mount->source);
			}
		}
		return NULL;
	}
};


///Register module
REGISTER_MODULE(new ConcreteFileSys(), ModuleID::_feature, filesys);
