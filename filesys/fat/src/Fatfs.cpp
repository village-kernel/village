//###########################################################################
// Fatfs.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSystem.h"
#include "Fatfs.h"
#include "Debug.h"


/// @brief Constructor
Fatfs::Fatfs()
{
}


/// @brief Deconstructor
Fatfs::~Fatfs()
{
}


void Fatfs::Mount()
{
	debug.Output(Debug::_Lv2, "Fatfs mount");
}


void Fatfs::Unmount()
{

}


int Fatfs::Open(const char* name, int opt)
{
	return 0;
}


int Fatfs::Write(char* data, int size, int offset)
{
	return 0;
}


int Fatfs::Read(char* data, int size, int offset)
{
	return 0;
}


int Fatfs::Lseek(int offset)
{
	return 0;
}


int Fatfs::Rename(const char* old, const char* now)
{
	return 0;
}


int Fatfs::Copy(const char* from, const char* to)
{
	return 0;
}


///Register file system
REGISTER_FS(new Fatfs(), fatfs);
