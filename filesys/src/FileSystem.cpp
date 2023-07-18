//###########################################################################
// FileSystem.cpp
// Definitions of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "FileSystem.h"


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


/// @brief Definitions filesystem and export
FileSystem& filesystem = FileSystem::Instance();


/// @brief File system initialize
void FileSystem::Initialize()
{
	FileOpt* opt = GetFileOpt("fatfs");
	if (NULL != opt)
	{
		opt->Mount("/dev/hdb", "/data", 0);
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
	FileOpt* opt = GetFileOpt("fatfs");
	if (NULL != opt)
	{
		opt->Unmount("/data");
	}
}


/// @brief Register file system
/// @param fileOpt file system opt
/// @param name file system name
void FileSystem::RegisterOpt(FileOpt* fileOpt, const char* name)
{
	fileOpts.InsertByName(fileOpt, (char*)name);
}


/// @brief Deregister file system
/// @param fileOpt file system opt
/// @param name file system name
void FileSystem::DeregisterOpt(FileOpt* fileOpt, const char* name)
{
	fileOpts.RemoveByName(fileOpt, (char*)name);
}


/// @brief Get file opt
/// @param name file opt name
/// @return file opt
FileOpt* FileSystem::GetFileOpt(const char* name)
{
	return fileOpts.GetItemByName((char*)name);
}


///Register module
REGISTER_MODULE(&FileSystem::Instance(), ModuleID::_fileSystem, fileSystem);
