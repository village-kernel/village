//###########################################################################
// FileStream.cpp
// Manages system configurations and parameters
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileStream.h"
#include "stdlib.h"
#include "string.h"


///Constructor
FileStream::FileStream(const char* driver)
	: driver((char*)driver)
{
}


///OpenFile
int FileStream::Open(const char* filename, int option)
{
	char path[strlen(driver) + strlen(filename) + 1] = { 0 };
	strcat(path, driver);
	strcat(path, filename);

	FRESULT res = f_mount(&fs, driver, 1);

	if (FR_OK != res) { f_unmount(driver); return res; }
	
	return f_open(&file, path, option);
}


///Writes a specified number of bytes of writeData into provided address
int FileStream::Write(uint8_t* txData, uint32_t size, uint32_t seek)
{
	UINT bw = 0;

	f_lseek(&file, (FSIZE_t)seek);

	f_write(&file, (void*)txData, size, &bw);

	return bw;
}


///Reads a specified number of bytes of writeData into the provided address
int FileStream::Read(uint8_t* rxData, uint32_t size, uint32_t seek)
{
	UINT br = 0;

	f_lseek(&file, (FSIZE_t)seek);

	f_read(&file, (void*)rxData, size, &br);

	return br;
}


///Get file size
int FileStream::Size()
{
	return f_size(&file);
}


///Close file
int FileStream::Close()
{
	FRESULT res = f_close(&file);

	f_unmount(driver);
	
	this->driver = (char*)"";

	return res;
}
