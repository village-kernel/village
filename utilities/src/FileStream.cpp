//###########################################################################
// FileStream.cpp
// Manages system configurations and parameters
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileStream.h"
#include "stdlib.h"
#include "ff.h"


///Constructor
FileStream::FileStream()
{
}


///Constructor
FileStream::FileStream(std::string filePath)
	:filePath(filePath)
{
}


///OpenFile
void FileStream::Open(std::string filePath)
{
	this->filePath = filePath;
	this->driver = filePath.substr(0, 2);
}


///Writes a specified number of bytes of writeData into provided address
int FileStream::Write(uint8_t* txData, uint32_t size, uint32_t seek)
{
	FATFS fs; FIL file; UINT bw = 0;

	if (f_mount(&fs, driver.c_str(), 1) == FR_OK)
	{
		if (f_open(&file, filePath.c_str(), FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
		{
			f_lseek(&file, (FSIZE_t)seek);
			f_write(&file, (void*)txData, size, &bw);
			f_close(&file);
		}
		f_unmount(driver.c_str());
	}

	return bw;
}


///Reads a specified number of bytes of writeData into the provided address
int FileStream::Read(uint8_t* rxData, uint32_t size, uint32_t seek)
{
	FATFS fs; FIL file; UINT br = 0;

	if (f_mount(&fs, driver.c_str(), 1) == FR_OK)
	{
		if (f_open(&file, filePath.c_str(), FA_READ) == FR_OK)
		{
			f_lseek(&file, (FSIZE_t)seek);
			f_read(&file, (void*)rxData, size, &br);
			f_close(&file);
		}
		f_unmount(driver.c_str());
	}

	return br;
}


///Close file
void FileStream::Close()
{
	this->filePath = "";
}
