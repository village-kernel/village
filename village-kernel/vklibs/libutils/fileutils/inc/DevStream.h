//###########################################################################
// DevStream.h
// Declarations of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEV_STREAM_H__
#define __DEV_STREAM_H__

#include "FileDefs.h"
#include "Driver.h"


/// @brief DevStream
class DevStream
{
private:
	//Members
	Fopts* fopts;
public:
	//Methods
	DevStream(const char* name = NULL, int mode = 0);
	~DevStream();
	bool Open(const char* name, int mode = 0);
	int Write(char* data, int size, int offset = 0);
	int Read(char* data, int size, int offset = 0);
	int IOCtrl(uint8_t cmd, void* data);
	void Close();
};

#endif //!__DEV_STREAM_H__
