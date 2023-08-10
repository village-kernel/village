//###########################################################################
// FatSystem.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_FILE_SYSTEM_H__
#define __FAT_FILE_SYSTEM_H__

#include "Templates.h"
#include "FileOpt.h"
#include "FatDefs.h"
#include "FatDisk.h"
#include "FatFile.h"
#include "FatDir.h"


/// @brief FAT
class FAT : public FileOpt, FatDefs
{
private:
	//Members
	FatDisk disk;
	FatFile file;
	FatDir  dir;

	List<DirEntry> files;

	//Methods
	int ReadDBR();
	int CheckFS();
public:
	//Methods
	FAT();
	~FAT();
	int Mount(const char* path, const char* mount, int opt, int startSector);
	int Unmount(const char* mount);
	int Open(const char* name, int mode);
	int Write(int fd, char* data, int size, int offset);
	int Read(int fd, char* data, int size, int offset);
	int Seek(int fd, int offset);
	int Rename(int fd, const char* old, const char* now);
	int Copy(int fd, const char* from, const char* to);
	int Remove(int fd);
	int Size(int fd);
	int Close(int fd);
};

#endif //!__FAT_FILE_SYSTEM_H__
