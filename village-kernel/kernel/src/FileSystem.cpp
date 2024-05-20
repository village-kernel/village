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
	if (!InitDisk()) return;

	if (!ReadMBR()) return;

	InitVolumes();

	MountSystemNode();
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
bool ConcreteFileSystem::InitDisk()
{ 
	if (diskdrv.Open("disk0", FileMode::_ReadWrite)) return true;

	kernel->debug.Error("Not disk driver found");

	return false;
}


/// @brief Read disk MBR section
/// @return 
bool ConcreteFileSystem::ReadMBR()
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
void ConcreteFileSystem::InitVolumes()
{
	for (uint8_t i = 0; i < 4; i++)
	{
		FileSys* fs = fileSys.GetItem(mbr->dpt[i].systemID);

		if (NULL != fs)
		{
			FileVol* volume = fs->CreateVolume();

			if (volume->Setup(&diskdrv, mbr->dpt[i].relativeSectors))
			{
				AttachVolume(volume);
			}
			else delete volume;
		}
	}
}


/// @brief Mount node
void ConcreteFileSystem::MountSystemNode()
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
