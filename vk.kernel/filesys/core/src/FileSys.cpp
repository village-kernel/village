//###########################################################################
// FileSys.cpp
// Definitions of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSys.h"
#include "Kernel.h"
#include "List.h"


/// @brief ConcreteFileSys
class ConcreteFileSys : public FileSys
{
private:
	//Members
	List<FileSystem*> fileSys;
	List<FileVolume*> volumes;
	List<MountNode*>  mounts;
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
		for (fileSys.Begin(); !fileSys.IsEnd(); fileSys.Next())
		{
			FileSystem* fs = fileSys.Item();

			fs->Setup();
		}

		MountSystemNode();
	}


	/// @brief File system exit
	void Exit()
	{
		for (fileSys.Begin(); !fileSys.IsEnd(); fileSys.Next())
		{
			FileSystem* fs = fileSys.Item();

			fs->Exit();
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


	/// @brief Register file system
	/// @param fileOpt file system opt
	/// @param name file system name
	void RegisterFS(FileSystem* fs, const char* name)
	{
		fileSys.InsertByName(fs, (char*)name);
	}


	/// @brief Deregister file system
	/// @param fileOpt file system opt
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
