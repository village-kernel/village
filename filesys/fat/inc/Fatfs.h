//###########################################################################
// Fatfs.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_FILE_SYSTEM_H__
#define __FAT_FILE_SYSTEM_H__

#include "FileOpt.h"


/// @brief Fatfs
class Fatfs : public FileOpt
{
public:
	//Methods
	Fatfs();
	~Fatfs();
	void Mount();
	void Unmount();
	int Open(const char* name, int opt);
	int Write(char* data, int size, int offset);
	int Read(char* data, int size, int offset);
	int Lseek(int offset);
	int Rename(const char* old, const char* now);
	int Copy(const char* from, const char* to);
};

#endif //!__FAT_FILE_SYSTEM_H__
