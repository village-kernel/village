//###########################################################################
// Disk.cpp
// Definitions of the functions that manage lba disk
//
// $Copyright: Copyright (C)
//###########################################################################
#include "Disk.h"
#include "Kernel.h"


/// @brief Constructor
Disk::Disk(uint8_t drv)
	:drv(drv)
{
}


/// @brief Constructor
Disk::Disk()
	:drv(0)
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
		//LBA 28 mode
		PortByteOut(0x1f6, 0xe0 | (drv << 4) | ((blk >> 24) & 0x0f));

		//Write one sector
		PortByteOut(0x1f2, 0);

		//Set block address
		PortByteOut(0x1f3, (uint8_t)(blk >>  0));
		PortByteOut(0x1f4, (uint8_t)(blk >>  8));
		PortByteOut(0x1f5, (uint8_t)(blk >> 16));

		//Write cmd
		PortByteOut(0x1f7, 0x30);
		
		//Wait
		while (PortByteIn(0x1f7) & 0x80) {}
		while (!(PortByteIn(0x1f7) & 0x08)) {}

		//Write data
		for (uint16_t i = 0; i < 256; i++)
		{
			PortWordOut(0x1f0, ((uint16_t*)data)[i]);
		}
	}

	return 0;
}


/// @brief Read data
/// @param data 
/// @param count 
/// @param blk 
/// @return 
int Disk::Read(uint8_t* data, uint32_t count, uint32_t blk)
{
	for (uint32_t cnt = 0; cnt < count; cnt++, blk++)
	{
		//LBA 28 mode
		PortByteOut(0x1f6, 0xe0 | (drv << 4) | ((blk >> 24) & 0x0f));

		//Read one sector
		PortByteOut(0x1f2, 1);
		
		//Set block address
		PortByteOut(0x1f3, (uint8_t)(blk >>  0));
		PortByteOut(0x1f4, (uint8_t)(blk >>  8));
		PortByteOut(0x1f5, (uint8_t)(blk >> 16));

		//Read cmd
		PortByteOut(0x1f7, 0x20);

		//Wait
		while (PortByteIn(0x1f7) & 0x80) {}
		while (!(PortByteIn(0x1f7) & 0x08)) {}

		//Read data
		for (uint16_t size = 0; size < 256; size++)
		{
			((uint16_t*)data)[size + cnt * 256] = PortWordIn(0x1f0);
		}
	}
	
	return 0;
}


///Register driver
REGISTER_DRIVER(new Disk(0), DriverID::_storage + 0, hda);
REGISTER_DRIVER(new Disk(1), DriverID::_storage + 1, hdb);
