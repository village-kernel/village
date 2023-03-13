//###########################################################################
// FileStream.h
// Manages binary file in storage
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_STREAM_H__
#define __FILE_STREAM_H__

#include "HalHeaders.h"
#include <string>


///FileStream
class FileStream
{
private:
	//Methods
	std::string driver;
	std::string filePath;
public:
	//Methods
	FileStream();
	FileStream(std::string filePath);
	void Open(std::string filePath);
	int Write(uint8_t* txData, uint32_t size, uint32_t seek = 0);
	int Read(uint8_t* rxData, uint32_t size, uint32_t seek = 0);
	void Close();
};

#endif // !__FILE_STREAM_H__
