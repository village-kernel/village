//###########################################################################
// FileSystem.cpp
// Definitions of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSystem.h"


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
	//Get all block device drivers
	List<Driver*> drivers = kernel->device.GetDrivers(DriverID::_block);

	//Initialize all hard disk
	for (drivers.Begin(); !drivers.IsEnd(); drivers.Next())
	{
		InitMBRDisk(drivers.Item()->GetName());
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
	for (volumes.Begin(); !volumes.IsEnd(); volumes.Next())
	{
		FileVol* volume = volumes.Item();

		volume->Exit();
	}

	fileSys.Release();
}


/// @brief Init disk driver
/// @return 
bool ConcreteFileSystem::InitMBRDisk(const char* diskdrv)
{
	static const uint16_t magic = 0xaa55;
	static const uint16_t mbr_sector = 0;

	kernel->debug.Info("Try to setup the hard drive (%s) by using MBR format", diskdrv);

	//Create an drvstream object
	DrvStream* driver = new DrvStream();

	//Open the disk driver
	if (!driver->Open(diskdrv, FileMode::_ReadWrite))
	{
		kernel->debug.Error("hard drive (%s) open failed", diskdrv);
		delete driver;
		return false;
	}

	//Read the master boot record
	MBR* mbr = new MBR();

	driver->Read((char*)mbr, 1, mbr_sector);

	if (magic != mbr->magic)
	{
		kernel->debug.Error("Not a valid disk");
		delete driver;
		return false;
	}

	//Attach the volumes
	for (uint8_t i = 0; i < 4; i++)
	{
		FileSys* fs = fileSys.GetItem(mbr->dpt[i].systemID);

		if (NULL != fs)
		{
			FileVol* volume = fs->CreateVolume();

			if (volume->Setup(driver, mbr->dpt[i].relativeSectors))
			{
				AttachVolume(volume);
			}
			else delete volume;
		}
	}

	delete mbr;

	return true;
}


/// @brief Mount node
bool ConcreteFileSystem::MountSystemNode()
{
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
	kernel->debug.Output(Debug::_Lv2, "Mount system node failed, '/media/VILLAGE OS' not found");
	return false;
}


/// @brief Register file system
/// @param fs file system
/// @param name file system name
void ConcreteFileSystem::RegisterFS(FileSys* fs, const char* name)
{
	fileSys.Insert(fs, fs->GetSystemID(), (char*)name);
}


/// @brief Deregister file system
/// @param fs file system
/// @param name file system name
void ConcreteFileSystem::DeregisterFS(FileSys* fs, const char* name)
{
	fileSys.RemoveByName(fs, (char*)name);
}


/// @brief Attach volume
/// @param volume
int ConcreteFileSystem::AttachVolume(FileVol* volume)
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
int ConcreteFileSystem::DetachVolume(FileVol* volume)
{
	return volumes.Remove(volume);
}


/// @brief Get File Opts
/// @param name 
/// @return 
FileVol* ConcreteFileSystem::GetVolume(const char* name)
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
