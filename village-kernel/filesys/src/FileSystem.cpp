//###########################################################################
// FileSystem.cpp
// Definitions of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSystem.h"
#include "DevStream.h"


/// @brief Constructor
ConcreteFileSystem::ConcreteFileSystem()
{
}


/// @brief Destructor
ConcreteFileSystem::~ConcreteFileSystem()
{
}


/// @brief File system setup
void ConcreteFileSystem::Setup()
{
	//Get all block device blockDevs
	List<Base*> blockDevs = kernel->device.GetDevices(DriverID::_block);

	//Initialize all hard disk
	for (blockDevs.Begin(); !blockDevs.IsEnd(); blockDevs.Next())
	{
		MountHardDrive(blockDevs.Item()->GetName());
	}

	//Mount system node
	if (MountSystemNode())
		kernel->debug.Info("File system setup completed!");
	else
		kernel->debug.Error("File system setup failed!");
}


/// @brief File system exit
void ConcreteFileSystem::Exit()
{
	//Exit hard drive
	for (medias.Begin(); !medias.IsEnd(); medias.Next())
	{
		UnmountHardDrive(medias.GetName());
	}

	//Release medias
	medias.Release();

	//Release file system
	filesyses.Release();

	//Release mount node
	mounts.Release();
}


/// @brief Register file system
/// @param fs 
/// @param name 
void ConcreteFileSystem::RegisterFS(FileSys* fs, const char* name)
{
	filesyses.Insert(fs, fs->GetSystemID(), (char*)name);
}


/// @brief Unregister file system
/// @param fs 
/// @param name 
void ConcreteFileSystem::UnregisterFS(FileSys* fs, const char* name)
{
	filesyses.Remove(fs, (char*)name);
}


/// @brief Init Hard Drive
/// @param disk 
/// @return 
bool ConcreteFileSystem::MountHardDrive(const char* disk)
{
	static const uint16_t magic = 0xaa55;
	static const uint16_t mbr_sector = 0;

	kernel->debug.Info("Try to setup the hard drive (%s) by using MBR format", disk);

	//Create an devstream object
	DevStream device;

	//Open the disk device
	if (!device.Open(disk, FileMode::_ReadWrite))
	{
		kernel->debug.Error("hard drive (%s) open failed", disk);
		return false;
	}

	//Read the master boot record
	MBR* mbr = new MBR();

	device.Read((char*)mbr, 1, mbr_sector);

	if (magic != mbr->magic)
	{
		kernel->debug.Error("Not a valid disk");
		device.Close();
		delete mbr;
		return false;
	}

	//Create an new disk media
	DiskMedia* media = new DiskMedia(PartitionType::_MBR, (char*)disk);

	//Add to medias list
	medias.Add(media, media->name);

	//Setup the volumes
	for (uint8_t i = 0; i < 4; i++)
	{
		SetupVolume(media, mbr->partition[i]);
	}

	//Leave
	device.Close();
	delete mbr;
	return true;
}


/// @brief Exit Hard Drive
/// @param disk 
/// @return 
bool ConcreteFileSystem::UnmountHardDrive(const char* disk)
{
	//Gets the disk media
	DiskMedia* media = medias.GetItem(disk);

	if (NULL != media)
	{
		//Exit volumes
		for (media->vols.Begin(); !media->vols.IsEnd(); media->vols.Next())
		{
			FileVol* volume = media->vols.Item();
			volume->Exit();
			delete volume;
		}

		//Release volumes
		media->vols.Release();

		//Remove media
		medias.Remove(media);
		delete media;
		return true;
	}

	return false;
}


/// @brief Setup Volume
/// @param media 
/// @param partition 
/// @return 
int ConcreteFileSystem::SetupVolume(DiskMedia* media, DPT partition)
{
	if ((0 != partition.systemID) && (0 != partition.sizeInLBA))
	{
		FileSys* filesys = filesyses.GetItem(partition.systemID);

		if (NULL != filesys)
		{
			FileVol* volume = filesys->CreateVolume();

			if (volume->Setup(media->name, partition.startingLBA))
			{
				return media->vols.Insert(volume, volume->GetName());
			}
			else delete volume;
		}
	}
	return -1;
}


/// @brief Mount node
bool ConcreteFileSystem::MountSystemNode()
{
	for (medias.Begin(); !medias.IsEnd(); medias.Next())
	{
		//Gets the volumes
		List<FileVol*> volumes = medias.Item()->vols;

		//Mount root node "/"
		for (volumes.Begin(); !volumes.IsEnd(); volumes.Next())
		{
			char* name = volumes.GetName();
			if (0 == strcmp(name, "VILLAGE OS"))
			{
				mounts.Add(new MountNode((char*)"/", name, 0755));
				return true;
			}
		}
	}
	kernel->debug.Output(Debug::_Lv2, "Mount system node failed, 'VILLAGE OS' not found");
	return false;
}


/// @brief Get volume
/// @param name 
/// @return 
FileVol* ConcreteFileSystem::GetVolume(const char* name)
{
	for (mounts.Begin(); !mounts.IsEnd(); mounts.Next())
	{
		MountNode* mount = mounts.Item();

		if (0 == strncmp(mount->target, name, strlen(mount->target)))
		{
			for (medias.Begin(); !medias.IsEnd(); medias.Next())
			{
				FileVol* volume = medias.Item()->vols.GetItem(mount->source);
				if (NULL != volume) return volume;
			}
		}
	}
	return NULL;
}
