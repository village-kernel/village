//###########################################################################
// FileSystem.cpp
// Definitions of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "FileSystem.h"
#include "Debug.h"


/// @brief Constructor
FileSystem::FileSystem()
{
}


/// @brief Destructor
FileSystem::~FileSystem()
{
}


/// @brief Singleton Instance
/// @return FileSystem instance
FileSystem& FileSystem::Instance()
{
	static FileSystem instance;
	return instance;
}
EXPORT_SYMBOL(_ZN10FileSystem8InstanceEv);


/// @brief Definitions filesystem and export
FileSystem& filesystem = FileSystem::Instance();
EXPORT_SYMBOL(filesystem);


/// @brief File system initialize
void FileSystem::Initialize()
{
	for (FileSys* fs = fileSys.Begin(); !fileSys.IsEnd(); fs = fileSys.Next())
	{
		fs->Setup();
	}
}


/// @brief File system execute
void FileSystem::Execute()
{
	while (1) {}
}


/// @brief File system exit
void FileSystem::Exit()
{
	for (FileSys* fs = fileSys.Begin(); !fileSys.IsEnd(); fs = fileSys.Next())
	{
		fs->Exit();
	}
}


/// @brief Get file opt
/// @param name file opt name
/// @return file opt
FileOpts* FileSystem::GetFileOpts(const char* name)
{
	return fileOpts.GetItemByName((char*)name);
}
EXPORT_SYMBOL(_ZN10FileSystem11GetFileOptsEPKc);


/// @brief 
/// @param name 
/// @return 
FileOpts* FileSystem::ChangeVolume(const char* name)
{
	if (((name[0] >= 'a' && name[0] <= 'z')  ||
		 (name[0] >= 'A' && name[0] <= 'Z')) &&
		  name[1] == ':')
	{
		return GetFileOpts("SD");
	}
	return NULL;
}
EXPORT_SYMBOL(_ZN10FileSystem12ChangeVolumeEPKc);


/// @brief 
/// @param name 
/// @return 
FileDir* FileSystem::ChangeDirectory(const char* name)
{
	return NULL;
}
EXPORT_SYMBOL(_ZN10FileSystem15ChangeDirectoryEPKc);


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
void FileSystem::RegisterOpts(FileOpts* opts, const char* name)
{
	fileOpts.InsertByName(opts, (char*)name);
}
EXPORT_SYMBOL(_ZN10FileSystem12RegisterOptsEP8FileOptsPKc);


/// @brief Deregister file system
/// @param opts file system opt
/// @param name file system name
void FileSystem::DeregisterOpts(FileOpts* opts, const char* name)
{
	fileOpts.RemoveByName(opts, (char*)name);
}
EXPORT_SYMBOL(_ZN10FileSystem14DeregisterOptsEP8FileOptsPKc);


///Register module
REGISTER_MODULE(&FileSystem::Instance(), ModuleID::_fileSystem, fileSystem);
