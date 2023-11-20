//###########################################################################
// FatVolume.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_VOLUME_H__
#define __FAT_VOLUME_H__

#include "Templates.h"
#include "FileOpts.h"
#include "FatDiskio.h"
#include "FatObject.h"
#include "FatEntry.h"


/// @brief FatVolume
class FatVolume : public FileOpts
{
private:
	//Members
	FatDiskio        disk;
	List<FatObject>  objs;

	//Directory Methods
	char* NotDir(const char* path);
	FatObject* SearchPath(const char* path, int reserve = 0);
	FatObject* SearchDir(FatObject* obj, const char* name);
	FatObject* CreateDir(const char* path, int attr);
	FileType GetObjectType(FatObject* obj);
	FileAttr GetObjectAttr(FatObject* obj);
	char* GetObjectName(FatObject* obj);
public:
	//FileOpts Methods
	int SetVolumeLabel(const char* name);
	char* GetVolumeLabel();
	
	int Open(const char* name, int mode);
	int Write(int fd, char* data, int size, int offset);
	int Read(int fd, char* data, int size, int offset);
	int Size(int fd);
	void Close(int fd);

	int OpenDir(const char* path, int mode);
	int ReadDir(int fd, FileDir* dirs, int size, int offset);
	int SizeDir(int fd);
	void CloseDir(int fd);

	int Remove(const char* name);
	int RemoveDir(const char* name);
public:
	//Methods
	FatVolume();
	~FatVolume();

	//Methods
	int Setup(Driver* diskdrv, uint32_t fstSec);
};

#endif //!__FAT_VOLUME_H__
