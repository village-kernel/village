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

	//Mount root node
	if (MountRootNode())
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

	kernel->debug.Info("Setup the hard drive (%s)", disk);

	//Create an devstream object
	DevStream* device = new DevStream();

	//Open the disk device
	if (!device->Open(disk, FileMode::_ReadWrite))
	{
		kernel->debug.Error("hard drive (%s) open failed", disk);
		return false;
	}

	//Read the master boot record
	MBR* mbr = new MBR();

	device->Read((char*)mbr, 1, mbr_sector);

	if (magic != mbr->magic)
	{
		kernel->debug.Error("Not a valid disk");
		device->Close();
		delete device;
		delete mbr;
		return false;
	}

	//Create an new disk media
	DiskMedia* media = new DiskMedia((char*)disk, device);

	//Add to medias list
	medias.Add(media, media->name);
	
	//Media with partition table
	if (CheckPartiionTable(mbr->partition[0]))
	{
		//Set the media for GPT partition format
		if (0xee == mbr->partition[0].OSIndicator)
		{
			//Set media partition type as GPT
			media->type = PartitionType::_GPT;

			//Create GPT object
			GPT* gpt = new GPT();

			//Read GPT header
			device->Read((char*)gpt, 1, mbr->partition[0].startingLBA);

			//Calculate the size of volume
			uint8_t size = gpt->numberOfPartitionEntries / gpt->sizeOfPartitionEntry;

			//Create GPT partition table object
			GPTPartition* partition = new GPTPartition();

			//Setup partitions
			for (uint8_t i = 0; i < size; i++)
			{
				//Read partition record
				device->Read((char*)partition, 1, gpt->partitionEntryLBA + i);

				//Setup GPT volume
				SetupVolume(media, partition->startingLBA);
			}

			//Leave
			delete gpt;
			delete partition;
		}
		//Set the media for MBR partition format
		else
		{
			//Set media partition type as MBR
			media->type = PartitionType::_MBR;

			//Setup MBR partitions
			for (uint8_t i = 0; i < 4; i++)
			{
				if (0 != mbr->partition[i].sizeInLBA)
				{
					SetupVolume(media, mbr->partition[i].startingLBA);
				}
			}
		}
	}
	else
	{
		//Setup single partition
		SetupVolume(media, 0);
	}

	//Leave
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

		//Close device
		media->dev->Close();

		//Remove media
		medias.Remove(media);
		delete media;
		return true;
	}

	return false;
}


/// @brief Determine whether partition table exists
/// @param partition 
/// @return 
bool ConcreteFileSystem::CheckPartiionTable(MBRPartition partition)
{
	if ((0 != partition.OSIndicator) && (0 != partition.sizeInLBA))
	{
		uint8_t  size = sizeof(MBRPartition);
		uint8_t* data = (uint8_t*)&partition;

		for (uint8_t i = 0; i < size; i++)
		{
			if (data[0] != data[i]) return true;
		}
	}

	return false;
}


/// @brief Setup Volume
/// @param media 
/// @param partition 
/// @return 
int ConcreteFileSystem::SetupVolume(DiskMedia* media, uint32_t startingLBA)
{
	for (filesyses.Begin(); !filesyses.IsEnd(); filesyses.Next())
	{
		FileVol* volume = filesyses.Item()->CreateVolume();

		if (volume->Setup(media->dev, startingLBA))
		{
			return media->vols.Insert(volume, volume->GetName());
		}
		else delete volume;
	}
	return -1;
}


/// @brief Mount root node
bool ConcreteFileSystem::MountRootNode()
{
	//Create root mount node
	MountNode* mount = new MountNode((char*)"/", (char*)"VILLAGE OS", 0755);

	//Try to mount root node
	for (medias.Begin(); !medias.IsEnd(); medias.Next())
	{
		if (MountSystemNode(medias.Item()->vols, mount)) return true;
	}

	//Output info
	kernel->debug.Error("Mount root node failed, 'VILLAGE OS' not found");

	//Leave
	delete mount;
	return false;
}


/// @brief Mount system node
/// @param volumes 
/// @return 
bool ConcreteFileSystem::MountSystemNode(List<FileVol*> volumes, MountNode* mount)
{
	for (volumes.Begin(); !volumes.IsEnd(); volumes.Next())
	{
		if (0 == strcmp(volumes.GetName(), mount->source))
		{
			mounts.Add(mount);
			return true;
		}
	}
	return false;
}


/// @brief Get volume
/// @param name 
/// @return 
FileVol* ConcreteFileSystem::GetVolume(const char* name)
{
	for (mounts.Begin(); !mounts.IsEnd(); mounts.Next())
	{
		return GetVolume(name, mounts.Item());
	}
	return NULL;
}


/// @brief Get volume
/// @param name 
/// @param mount 
/// @return 
FileVol* ConcreteFileSystem::GetVolume(const char* name, MountNode* mount)
{
	if (0 == strncmp(mount->target, name, strlen(mount->target)))
	{
		for (medias.Begin(); !medias.IsEnd(); medias.Next())
		{
			FileVol* volume = medias.Item()->vols.GetItem(mount->source);
			if (NULL != volume) return volume;
		}
	}
	return NULL;
}
