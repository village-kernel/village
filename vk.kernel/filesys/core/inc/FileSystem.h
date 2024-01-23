//###########################################################################
// FileSystem.h
// Declarations of the functions that manage file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include "Module.h"
#include "FileSys.h"
#include "FileOpts.h"
#include "Templates.h"


/// @brief FileSystem
class FileSystem : public Module
{
private:
	//Members
	List<FileSys*>   fileSys;
	List<FileOpts*>  fileOpts;
	List<MountNode*> mounts;
public:
	//Methods
	FileSystem();
	~FileSystem();
	void Initialize();
	void Exit();

	void RegisterFS(FileSys* fs, const char* name);
	void DeregisterFS(FileSys* fs, const char* name);

	int RegisterOpts(FileOpts* opts);
	int DeregisterOpts(FileOpts* opts);

	FileOpts* GetFileOpts(const char* name);
};

#endif //!__FILE_SYSTEM_H__
