//###########################################################################
// FileStream.h
// Manages binary file in storage
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_STREAM_H__
#define __FILE_STREAM_H__

#include "stdint.h"
#include "stddef.h"
#include "ff.h"

///FileStream
class FileStream
{
public:
	enum Option
	{
		_Create = FA_CREATE_ALWAYS,
		_Write = FA_WRITE,
		_Read  = FA_READ,
		_WriteRead = FA_CREATE_ALWAYS | FA_WRITE | FA_READ,
	};
private:
	//Methods
	char* driver;
	FATFS fs; 
	FIL file;
public:
	//Methods
	FileStream(const char* driver = "1:");
	int Open(const char* filename, int option);
	int Write(uint8_t* txData, uint32_t size, uint32_t seek = 0);
	int Read(uint8_t* rxData, uint32_t size, uint32_t seek = 0);
	int Size();
	int Close();
};

#endif // !__FILE_STREAM_H__
