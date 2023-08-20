//###########################################################################
// FileSystem.h
// Declarations of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include "Module.h"
#include "FileOpt.h"
#include "FileDefs.h"


/// @brief FileSystem
class FileSystem : public Module
{
private:
	//Members
	List<FileOpt> fileOpts;
	
	//Methods
	FileSystem();
	~FileSystem();
public:
	//Methods
	void Initialize();
	void Execute();
	void Exit();
	void RegisterOpt(FileOpt* fileOpt, const char* name);
	void DeregisterOpt(FileOpt* fileOpt, const char* name);

	FileOpt* GetFileOpt(const char* name);
	FileOpt* ChangeVolume(const char* name);
	FileDir* ChangeDirectory(const char* name);
	
	//Singleton Instance
	static FileSystem& Instance();
};

///Declarations FileSystem reference
extern FileSystem& filesystem;

#endif //!__FILE_SYSTEM_H__
