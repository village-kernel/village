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
#include "FatName.h"
#include "FatFile.h"
#include "FatDir.h"


/// @brief FAT
class FAT : public FileOpt, FatDat
{
private:
	//Members
	MBR*     mbr;

	//Lists
	List<DirEntry> files;
	List<DirData>  dirs;

	//Methods
	int ReadMBR();
	int ReadDBR();
	int CheckFS();
	FileType GetFileType(DirEntry* entry);
	FileAttr GetFileAttr(DirEntry* entry);
public:
	//Methods
	FAT();
	~FAT();
	void Setup();
	void Exit();

	//Mount
	int Mount(const char* path, const char* mount, int opt);
	int Unmount(const char* mount);
	
	//File
	int Open(const char* name, int mode);
	int Write(int fd, char* data, int size, int offset);
	int Read(int fd, char* data, int size, int offset);
	int Size(int fd);
	void Close(int fd);

	//Dir
	int OpenDir(const char* name, int mode);
	int ReadDir(int fd, FileDir* dirs, int size, int offset);
	int SizeDir(int fd);
	void CloseDir(int fd);

	//Operate
	int Rename(int fd, const char* old, const char* now);
	int Copy(int fd, const char* from, const char* to);
	int Remove(int fd);
};

#endif //!__FAT_FILE_SYSTEM_H__
