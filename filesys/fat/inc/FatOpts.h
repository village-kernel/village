//###########################################################################
// FatOpts.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_OPTS_H__
#define __FAT_OPTS_H__

#include "Templates.h"
#include "FileOpts.h"
#include "FatDefs.h"
#include "FatData.h"


/// @brief FatOpts
class FatOpts : public FileOpts, FatDefs
{
private:
	//Lists
	List<DirEntry>    files;
	List<DirEntries>  dirs;

	//Members
	FatData fatData;

	//Methods
	FileType GetFileType(DirEntry* entry);
	FileAttr GetFileAttr(DirEntry* entry);
public:
	//Methods
	FatOpts();
	~FatOpts();

	//Methods
	int Setup(Driver* diskdrv, uint32_t fstSec);
	void Exit();

	//Mount
	int Mount(const char* path, const char* mount, int opt);
	int Unmount(const char* mount);
	int SetVolumeLabel(const char* name);
	char* GetVolumeLabel();
	
	//File
	int Open(const char* name, int mode);
	int Write(int fd, char* data, int size, int offset);
	int Read(int fd, char* data, int size, int offset);
	int Size(int fd);
	void Close(int fd);

	//Directory
	int OpenDir(const char* name, int mode);
	int ReadDir(int fd, FileDir* dirs, int size, int offset);
	int SizeDir(int fd);
	void CloseDir(int fd);

	//Operate
	int Move(int fd, const char* from, const char* to);
	int Copy(int fd, const char* from, const char* to);
	int Remove(int fd);
};

#endif //!__FAT_OPTS_H__
