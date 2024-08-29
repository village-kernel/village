//###########################################################################
// FatSystem.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_FILE_SYSTEM_H__
#define __FAT_FILE_SYSTEM_H__

#include "FatDiskio.h"
#include "FatObject.h"
#include "FileSys.h"
#include "List.h"


/// @brief FatVolume
class FatVolume : public FileVol
{
private:
	//Members
	FatDiskio        fatdisk;
	List<FatObject*> objs;

	//Members
	uint32_t bytesPerSec;
	uint32_t secPerClust;

	//Directory Methods
	char* BaseName(const char* path);
	FatObject* SearchPath(const char* path, int reserve = 0);
	FatObject* SearchDir(FatObject* obj, const char* name);
	FatObject* CreateDir(const char* path, int attr);
public:
	//File Volume Methods
	bool SetName(const char* name);
	char* GetName();
	
	int Open(const char* name, int mode);
	int Write(int fd, char* data, int size, int offset);
	int Read(int fd, char* data, int size, int offset);
	int Size(int fd);
	void Close(int fd);

	int OpenDir(const char* path, int mode);
	int ReadDir(int fd, FileDir* dirs, int size, int offset);
	int SizeDir(int fd);
	void CloseDir(int fd);

	FileType GetFileType(const char* name);
	bool IsExist(const char* name, FileType type);
	bool Remove(const char* name);
public:
	//Methods
	FatVolume();
	~FatVolume();

	//Methods
	bool Setup(const char* disk, uint32_t startingLBA);
	void Exit();
};


/// @brief FatSystem
class FatSystem : public FileSys
{
public:
	//Methods
	uint32_t GetSystemID();
	FileVol* CreateVolume();
};

#endif //!__FAT_FILE_SYSTEM_H__
