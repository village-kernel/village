//###########################################################################
// FileStream.cpp
// Manages system configurations and parameters
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileStream.h"
#include "stdlib.h"


///Constructor
FileStream::FileStream()
{
}


///OpenFile
int FileStream::Open(std::string filePath, int option)
{
	this->filePath = filePath;
	this->driver = filePath.substr(0, 2);

	FRESULT res = f_mount(&fs, driver.c_str(), 1);

	if (FR_OK != res) return res;
	
	return f_open(&file, filePath.c_str(), option);
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

	f_unmount(driver.c_str());
	
	this->driver = "";
	this->filePath = "";

	return res;
}
