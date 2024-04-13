//###########################################################################
// FatVolume.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_VOLUME_H__
#define __FAT_VOLUME_H__

#include "List.h"
#include "FileVolume.h"
#include "FatDiskio.h"
#include "FatObject.h"


/// @brief FatVolume
class FatVolume : public FileVolume
{
private:
	//Members
	FatDiskio        disk;
	List<FatObject*> objs;

	//Directory Methods
	char* NotDir(const char* path);
	FatObject* SearchPath(const char* path, int reserve = 0);
	FatObject* SearchDir(FatObject* obj, const char* name);
	FatObject* CreateDir(const char* path, int attr);
public:
	//FileVolume Methods
	bool SetVolumeLabel(const char* label);
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

	bool Remove(const char* name);
public:
	//Methods
	FatVolume();
	~FatVolume();

	//Methods
	bool Setup(DrvStream* diskdrv, uint32_t fstSec);
	void Exit();
};

#endif //!__FAT_VOLUME_H__