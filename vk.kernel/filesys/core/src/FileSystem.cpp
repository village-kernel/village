//###########################################################################
// FileSystem.cpp
// Definitions of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSystem.h"
#include "Kernel.h"


/// @brief Constructor
FileSystem::FileSystem()
{
}


/// @brief Destructor
FileSystem::~FileSystem()
{
}


/// @brief File system initialize
void FileSystem::Initialize()
{
	for (FileSys* fs = fileSys.Begin(); !fileSys.IsEnd(); fs = fileSys.Next())
	{
		fs->Setup();
	}

	//Mount root node "/"
	mounts.Add(new MountNode((char*)"/", (char*)"/media/VILLAGE OS", 0755));
}


/// @brief File system exit
void FileSystem::Exit()
{
	for (FileSys* fs = fileSys.Begin(); !fileSys.IsEnd(); fs = fileSys.Next())
	{
		fs->Exit();
	}
}


/// @brief Register file system
/// @param fileOpt file system opt
/// @param name file system name
void FileSystem::RegisterFS(FileSys* fs, const char* name)
{
	fileSys.InsertByName(fs, (char*)name);
}
EXPORT_SYMBOL(_ZN10FileSystem10RegisterFSEP7FileSysPKc);


/// @brief Deregister file system
/// @param fileOpt file system opt
/// @param name file system name
void FileSystem::DeregisterFS(FileSys* fs, const char* name)
{
	fileSys.RemoveByName(fs, (char*)name);
}
EXPORT_SYMBOL(_ZN10FileSystem12DeregisterFSEP7FileSysPKc);


/// @brief Register file system
/// @param opts file system opt
/// @param name file system name
int FileSystem::RegisterOpts(FileOpts* opts)
{
	char* prefix = (char*)"/media/";
	char* label  = opts->GetVolumeLabel();
	char* name   = new char[strlen(prefix) + strlen(label) + 1]();
	strcat(name, prefix);
	strcat(name, label);
	return fileOpts.InsertByName(opts, name);
}
EXPORT_SYMBOL(_ZN10FileSystem12RegisterOptsEP8FileOpts);


/// @brief Deregister file system
/// @param opts file system opt
/// @param name file system name
int FileSystem::DeregisterOpts(FileOpts* opts)
{
	return fileOpts.Remove(opts);
}
EXPORT_SYMBOL(_ZN10FileSystem14DeregisterOptsEP8FileOpts);


/// @brief Get File Opts
/// @param name 
/// @return 
FileOpts* FileSystem::GetFileOpts(const char* name)
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
EXPORT_SYMBOL(_ZN10FileSystem11GetFileOptsEPKc);


///Register module
REGISTER_MODULE(new FileSystem(), ModuleID::_fileSystem, fileSystem);
