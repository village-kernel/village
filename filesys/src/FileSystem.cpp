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


/// @brief Deconstructor
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
	for (FileOpt* opt = fileOpts.Begin(); !fileOpts.IsEnd(); opt = fileOpts.Next())
	{
		opt->Setup();
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
	for (FileOpt* opt = fileOpts.Begin(); !fileOpts.IsEnd(); opt = fileOpts.Next())
	{
		opt->Exit();
	}
}


/// @brief Get file opt
/// @param name file opt name
/// @return file opt
FileOpt* FileSystem::GetFileOpt(const char* name)
{
	return fileOpts.GetItemByName((char*)name);
}
EXPORT_SYMBOL(_ZN10FileSystem10GetFileOptEPKc);


/// @brief 
/// @param name 
/// @return 
FileOpt* FileSystem::ChangeVolume(const char* name)
{
	if (((name[0] >= 'a' && name[0] <= 'z')  ||
		 (name[0] >= 'A' && name[0] <= 'Z')) &&
		  name[1] == ':')
	{
		return GetFileOpt("fat");
	}
	return NULL;
}


/// @brief 
/// @param name 
/// @return 
FileDir* FileSystem::ChangeDirectory(const char* name)
{
	return NULL;
}


/// @brief Register file system
/// @param fileOpt file system opt
/// @param name file system name
void FileSystem::RegisterOpt(FileOpt* fileOpt, const char* name)
{
	fileOpts.InsertByName(fileOpt, (char*)name);
}
EXPORT_SYMBOL(_ZN10FileSystem11RegisterOptEP7FileOptPKc);


/// @brief Deregister file system
/// @param fileOpt file system opt
/// @param name file system name
void FileSystem::DeregisterOpt(FileOpt* fileOpt, const char* name)
{
	fileOpts.RemoveByName(fileOpt, (char*)name);
}
EXPORT_SYMBOL(_ZN10FileSystem13DeregisterOptEP7FileOptPKc);


///Register module
REGISTER_MODULE(&FileSystem::Instance(), ModuleID::_fileSystem, fileSystem);
