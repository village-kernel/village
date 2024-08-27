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
	fileSys.Release();

	//Release mount node
	mounts.Release();
}


/// @brief Register file system
/// @param fs 
/// @param name 
void ConcreteFileSystem::RegisterFS(FileSys* fs, const char* name)
{
	fileSys.Insert(fs, fs->GetSystemID(), (char*)name);
}


/// @brief Unregister file system
/// @param fs 
/// @param name 
void ConcreteFileSystem::UnregisterFS(FileSys* fs, const char* name)
{
	fileSys.RemoveByName(fs, (char*)name);
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

	//Attach the volumes
	for (uint8_t i = 0; i < 4; i++)
	{
		FileSys* fs = fileSys.GetItem(mbr->dpt[i].systemID);

		if (NULL != fs)
		{
			FileVol* volume = fs->CreateVolume();

			if (volume->Setup(disk, mbr->dpt[i].relativeSectors))
			{
				AttachVolume(media, volume);
			}
			else delete volume;
		}
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
	DiskMedia* media = medias.GetItemByName(disk);

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


/// @brief Attach volume
/// @param volume
int ConcreteFileSystem::AttachVolume(DiskMedia* media, FileVol* volume)
{
	char* prefix = (char*)"/media/";
	char* label  = volume->GetVolumeLabel();
	char* name   = new char[strlen(prefix) + strlen(label) + 1]();
	strcat(name, prefix);
	strcat(name, label);
	return media->vols.InsertByName(volume, name);
}


/// @brief Detach volume
/// @param volume
int ConcreteFileSystem::DetachVolume(DiskMedia* media, FileVol* volume)
{
	return media->vols.Remove(volume);
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
				FileVol* volume = medias.Item()->vols.GetItemByName(mount->source);
				if (NULL != volume) return volume;
			}
		}
	}
	return NULL;
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
			char* volumelab = volumes.GetName();
			if (0 == strcmp(volumelab, "/media/VILLAGE OS"))
			{
				mounts.Add(new MountNode((char*)"/", volumelab, 0755));
				return true;
			}
		}
	}
	kernel->debug.Output(Debug::_Lv2, "Mount system node failed, '/media/VILLAGE OS' not found");
	return false;
}
