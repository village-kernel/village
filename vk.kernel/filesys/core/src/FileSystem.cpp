//###########################################################################
// FileSystem.cpp
// Definitions of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSystem.h"
#include "Templates.h"
#include "Kernel.h"


/// @brief ConcreteFileSystem
class ConcreteFileSystem : public FileSystem
{
private:
	//Members
	List<FileSys*>   fileSys;
	List<FileOpts*>  fileOpts;
	List<MountNode*> mounts;

	/// @brief RegisterFileSyss
	void RegisterFileSyss()
	{
		extern FileSysInfo __filesys_start;
		extern FileSysInfo __filesys_end;

		uint32_t count = &__filesys_end - &__filesys_start;
		FileSysInfo* filesys = &__filesys_start;

		for (uint32_t i = 0; i < count; i++)
		{
			RegisterFS(filesys[i].fs, filesys[i].name);
		}
	}
public:
	/// @brief Constructor
	ConcreteFileSystem()
	{
	}


	/// @brief Destructor
	~ConcreteFileSystem()
	{
	}


	/// @brief File system setup
	void Setup()
	{
		RegisterFileSyss();

		for (FileSys* fs = fileSys.Begin(); !fileSys.IsEnd(); fs = fileSys.Next())
		{
			fs->Setup();
		}

		MountSystemNode();
	}


	/// @brief File system exit
	void Exit()
	{
		for (FileSys* fs = fileSys.Begin(); !fileSys.IsEnd(); fs = fileSys.Next())
		{
			fs->Exit();
		}
	}


	/// @brief Mount node
	void MountSystemNode()
	{
		//Mount root node "/"
		for (fileOpts.Begin(); !fileOpts.IsEnd(); fileOpts.Next())
		{
			char* volumelab = fileOpts.GetName();
			if (0 == strcmp(volumelab, "/media/VILLAGE OS"))
			{
				mounts.Add(new MountNode((char*)"/", volumelab, 0755));
				return;
			}
		}
		kernel->debug->Output(Debug::_Lv2, "Mount system node failed, '/media/VILLAGE OS' not found");
	}


	/// @brief Register file system
	/// @param fileOpt file system opt
	/// @param name file system name
	void RegisterFS(FileSys* fs, const char* name)
	{
		fileSys.InsertByName(fs, (char*)name);
	}


	/// @brief Deregister file system
	/// @param fileOpt file system opt
	/// @param name file system name
	void DeregisterFS(FileSys* fs, const char* name)
	{
		fileSys.RemoveByName(fs, (char*)name);
	}


	/// @brief Register file system
	/// @param opts file system opt
	/// @param name file system name
	int RegisterOpts(FileOpts* opts)
	{
		char* prefix = (char*)"/media/";
		char* label  = opts->GetVolumeLabel();
		char* name   = new char[strlen(prefix) + strlen(label) + 1]();
		strcat(name, prefix);
		strcat(name, label);
		return fileOpts.InsertByName(opts, name);
	}


	/// @brief Deregister file system
	/// @param opts file system opt
	/// @param name file system name
	int DeregisterOpts(FileOpts* opts)
	{
		return fileOpts.Remove(opts);
	}


	/// @brief Get File Opts
	/// @param name 
	/// @return 
	FileOpts* GetFileOpts(const char* name)
	{
		for (MountNode* mount = mounts.Begin(); !mounts.IsEnd(); mount = mounts.Next())
		{
			if (0 == strncmp(mount->target, name, strlen(mount->target)))
			{
				return fileOpts.GetItemByName(mount->source);
			}
		}
		return NULL;
	}
};


///Register module
REGISTER_MODULE(ConcreteFileSystem, ModuleID::_fileSystem, fileSystem);
