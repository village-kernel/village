//###########################################################################
// Disk.cpp
// Definitions of the functions that manage lba disk
//
// $Copyright: Copyright (C)
//###########################################################################
#include "Disk.h"
#include "Kernel.h"


/// @brief Constructor
DiskDrv::DiskDrv(uint8_t drv)
	:drv(drv)
{
}


/// @brief Constructor
DiskDrv::DiskDrv()
	:drv(0)
{
}


/// @brief Deconstructor
DiskDrv::~DiskDrv()
{
}


/// @brief Write data
/// @param data 
/// @param count 
/// @param blk 
/// @return 
int DiskDrv::Write(uint8_t* data, uint32_t count, uint32_t blk)
{
	for (uint32_t cnt = 0; cnt < count; cnt++, blk++)
	{
		//LBA 28 mode
		PortByteOut(ATA_MODE, ATA_MODE_LBA | (drv << ATA_MODE_DRV_Pos) | ((blk >> 24) & 0x0f));

		//Write one sector
		PortByteOut(ATA_SECTOR_CNT, 1);

		//Set block address
		PortByteOut(ATA_SECTOR_0_7_BITS,   (uint8_t)(blk >>  0));
		PortByteOut(ATA_SECTOR_8_15_BITS,  (uint8_t)(blk >>  8));
		PortByteOut(ATA_SECTOR_16_23_BITS, (uint8_t)(blk >> 16));

		//Write cmd
		PortByteOut(ATA_CMD, ATA_CMD_WRITE);
		
		//Wait
		while (ATA_STATUS_BSY == (PortByteIn(ATA_STATUS) & ATA_STATUS_BSY_Msk)) {}
		while (ATA_STATUS_RDY != (PortByteIn(ATA_STATUS) & ATA_STATUS_RDY_Msk)) {}

		//Write data
		for (uint16_t size = 0; size < 256; size++)
		{
			PortWordOut(ATA_DATA, ((uint16_t*)data)[size + cnt * 256]);
		}
	}

	return 0;
}


/// @brief Read data
/// @param data 
/// @param count 
/// @param blk 
/// @return 
int DiskDrv::Read(uint8_t* data, uint32_t count, uint32_t blk)
{
	for (uint32_t cnt = 0; cnt < count; cnt++, blk++)
	{
		//LBA 28 mode
		PortByteOut(ATA_MODE, ATA_MODE_LBA | (drv << ATA_MODE_DRV_Pos) | ((blk >> 24) & 0x0f));

		//Read one sector
		PortByteOut(ATA_SECTOR_CNT, 1);
		
		//Set block address
		PortByteOut(ATA_SECTOR_0_7_BITS,   (uint8_t)(blk >>  0));
		PortByteOut(ATA_SECTOR_8_15_BITS,  (uint8_t)(blk >>  8));
		PortByteOut(ATA_SECTOR_16_23_BITS, (uint8_t)(blk >> 16));

		//Read cmd
		PortByteOut(ATA_CMD, ATA_CMD_READ);

		//Wait
		while (ATA_STATUS_BSY == (PortByteIn(ATA_STATUS) & ATA_STATUS_BSY_Msk)) {}
		while (ATA_STATUS_RDY != (PortByteIn(ATA_STATUS) & ATA_STATUS_RDY_Msk)) {}

		//Read data
		for (uint16_t size = 0; size < 256; size++)
		{
			((uint16_t*)data)[size + cnt * 256] = PortWordIn(ATA_DATA);
		}
	}
	
	return 0;
}


///Register driver
REGISTER_DRIVER(new DiskDrv(0), DriverID::_storage + 0, hda);
REGISTER_DRIVER(new DiskDrv(1), DriverID::_storage + 1, hdb);
