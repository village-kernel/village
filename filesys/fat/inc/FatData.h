//###########################################################################
// FatData.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_DATA_H__
#define __FAT_DATA_H__

#include "FatDefs.h"
#include "FatDisk.h"
#include "FatEntry.h"
#include "FatName.h"


/// @brief FatData
class FatData : public FatDefs
{
private:
	//Members
	DBR*    dbr;
	Info*   info;
	FatDisk fatDisk;
	FatName fatName;

	//Methods
	int ReadDBR();
	int CheckFS();

	//Directory Methods
	char* NotDir(const char* path);
	char* GetDirName(FatEntry* data);
	int CheckDirName(DirEntries* dirents, UnionEntry* unient);
	DirEntry* SearchPath(const char* path, int forward = 0);
	DirEntry* SearchDir(DirEntry* dirent, const char* name);
	DirEntries* OpenDir(DirEntry* dirent);
	UnionEntry* CreateEntry(DirEntry* dirent, const char* name, uint8_t& num);
	DirEntry* CreateFile(DirEntry* dirent, const char* name);
	DirEntries* CreateDir(DirEntry* dirent, const char* name);
	DirEntry* CreateFile(const char* path);
	DirEntries* CreateDir(const char* path);
public:
	//Methods
	int Setup(Driver* diskdrv, uint32_t fstSec);

	//File Methods
	DirEntry* Open(const char* name, int mode);
	int Write(char* data, uint32_t size, DirEntry* dirent);
	int Read(char* data, uint32_t size, DirEntry* dirent);
	int Size(DirEntry* dirent);

	//Directory Methods
	DirEntries* OpenDir(const char* path, int mode);
	DirEntry* ReadDir(DirEntries* dirents);
	int SizeDir(DirEntries* dirents);

	//Opts Methods
	int Move(const char* from, const char* to);
	int Copy(const char* from, const char* to);
	int Remove(const char* name);
	int MoveDir(const char* from, const char* to);
	int CopyDir(const char* from, const char* to);
	int RemoveDir(const char* name);

	//Volume Methods
	char* GetVolumeLabel();
	int SetVolumeLabel(const char* name);
};

#endif //!__FAT_DATA_H__
