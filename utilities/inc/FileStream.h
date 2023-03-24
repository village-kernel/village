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
#include <string>
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
	std::string driver;
	std::string filePath;
	FATFS fs; 
	FIL file;
public:
	//Methods
	FileStream();
	int Open(std::string filePath, int option);
	int Write(uint8_t* txData, uint32_t size, uint32_t seek = 0);
	int Read(uint8_t* rxData, uint32_t size, uint32_t seek = 0);
	int Size();
	int Close();
};

#endif // !__FILE_STREAM_H__
