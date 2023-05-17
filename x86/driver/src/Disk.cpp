//###########################################################################
// Disk.cpp
// Definitions of the functions that manage lba disk
//
// $Copyright: Copyright (C)
//###########################################################################
#include "Disk.h"
#include "Kernel.h"


/// @brief Constructor
Disk::Disk()
{
}


/// @brief Deconstructor
Disk::~Disk()
{
}


/// @brief Write data
/// @param data 
/// @param count 
/// @param blk 
/// @return 
int Disk::Write(uint8_t* data, uint32_t count, uint32_t blk)
{
	while (count--)
	{
		//Write one sector
		PortByteOut(0x1f2, 0);

		//Set block address
		PortByteOut(0x1f3, ((blk >>  0) & 0xff));
		PortByteOut(0x1f4, ((blk >>  8) & 0xff));
		PortByteOut(0x1f5, ((blk >> 16) & 0xff));

		//LBA mode
		PortByteOut(0x1f6, 0xe | ((blk >> 24) & 0x0f));

		//Write cmd
		PortByteOut(0x1f7, 0x30);
		
		//Wait
		while(0x08 != (PortByteIn(0x1f7) & 0x88)) {}

		//Write data
		for (uint16_t i = 0; i < 256; i++)
		{
			PortWordOut(0x1f0, ((uint16_t*)data)[i]);
		}
	}

	return count;
}


/// @brief Read data
/// @param data 
/// @param count 
/// @param blk 
/// @return 
int Disk::Read(uint8_t* data, uint32_t count, uint32_t blk)
{
	while (count--)
	{
		//Read one sector
		PortByteOut(0x1f2, 0);
		
		//Set block address
		PortByteOut(0x1f3, ((blk >>  0) & 0xff));
		PortByteOut(0x1f4, ((blk >>  8) & 0xff));
		PortByteOut(0x1f5, ((blk >> 16) & 0xff));

		//LBA mode
		PortByteOut(0x1f6, 0xe0 | ((blk >> 24) & 0x0f));

		//Read cmd
		PortByteOut(0x1f7, 0x20);

		//Wait
		while(0x08 != (PortByteIn(0x1f7) & 0x88)) {}

		//Read data
		for (uint16_t i = 0; i < 256; i++)
		{
			((uint16_t*)data)[i] = PortWordIn(0x1f0);
		}
	}
	
	return count;
}


///Register driver
REGISTER_DRIVER(new Disk(), DriverID::_storage, disk);
