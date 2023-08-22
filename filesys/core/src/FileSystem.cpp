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
	:assignLetter('C')
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
	if (assignLetter >= 'A' && assignLetter < 'Z')
	{
		return fileOpts.Insert(opts, assignLetter++);
	}
	return 0;
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


/// @brief Change volume
/// @param name 
/// @return 
FileOpts* FileSystem::ChangeVolume(const char* name)
{
	if (((name[0] >= 'a' && name[0] <= 'z')  ||
		 (name[0] >= 'A' && name[0] <= 'Z')) &&
		  name[1] == ':')
	{
		char letter = 0;

		if (name[0] >= 'a' && name[0] <= 'z')
			letter = name[0] - 0x20;
		else
			letter = name[0];

		return fileOpts.GetItem(letter);
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


///Register module
REGISTER_MODULE(&FileSystem::Instance(), ModuleID::_fileSystem, fileSystem);
