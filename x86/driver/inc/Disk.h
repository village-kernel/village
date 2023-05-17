//###########################################################################
// Disk.h
// Declarations of the functions that manage lba disk
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DISK_H__
#define __DISK_H__

#include "Hardware.h"
#include "Driver.h"

/// @brief Disk
class Disk : public Driver
{
private:
	//Members
	uint8_t drv;
public: 
	//Methods
	Disk(uint8_t drv);
	Disk();
	~Disk();
	int Write(uint8_t* data, uint32_t count = 0, uint32_t blk = 0);
	int Read(uint8_t* data, uint32_t count = 0, uint32_t blk = 0);
};

#endif //!__DISK_H__
