//###########################################################################
// AtaLbaDisk.cpp
// Definitions of the functions that manage lba disk
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "AtaLbaDisk.h"
#include "Kernel.h"


/// @brief Constructor
AtaLbaDisk::AtaLbaDisk()
{
}


/// @brief Decstructor
AtaLbaDisk::~AtaLbaDisk()
{
}


/// @brief SetData
/// @param config 
void AtaLbaDisk::SetData(void* data)
{
	config = *((Config*)data);
}


/// @brief open
bool AtaLbaDisk::Open()
{
	//Stop device from sending interrupts
	mutex.Lock();
	PortByteOut(ATA_PRIMARY_PORT_CTRL, ATA_CTRL_nIEN);
	PortByteOut(ATA_SECOND_PORT_CTRL, ATA_CTRL_nIEN);
	mutex.Unlock();
	return true;
}


/// @brief Write data
/// @param data 
/// @param count 
/// @param blk 
/// @return 
int AtaLbaDisk::Write(uint8_t* data, uint32_t count, uint32_t blk)
{
	mutex.Lock();

	for (uint32_t cnt = 0; cnt < count; cnt++, blk++)
	{
		//LBA 28 mode
		PortByteOut(ATA_MODE, ATA_MODE_LBA | (config.drv << ATA_MODE_DRV_Pos) | ((blk >> 24) & 0x0f));

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

		//Flush cache
		PortByteOut(ATA_CMD, ATA_CMD_FLUSH);

		//Wait
		while (ATA_STATUS_BSY == (PortByteIn(ATA_STATUS) & ATA_STATUS_BSY_Msk)) {}
	}

	mutex.Unlock();

	return count;
}


/// @brief Read data
/// @param data 
/// @param count 
/// @param blk 
/// @return 
int AtaLbaDisk::Read(uint8_t* data, uint32_t count, uint32_t blk)
{
	mutex.Lock();

	for (uint32_t cnt = 0; cnt < count; cnt++, blk++)
	{
		//LBA 28 mode
		PortByteOut(ATA_MODE, ATA_MODE_LBA | (config.drv << ATA_MODE_DRV_Pos) | ((blk >> 24) & 0x0f));

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

	mutex.Unlock();
	
	return count;
}


/// @brief close
void AtaLbaDisk::Close()
{

}


/// @brief Probe
/// @param device 
/// @return 
bool AtaLbaDiskDrv::Probe(PlatDevice* device)
{
	AtaLbaDisk* ataLbaDisk = new AtaLbaDisk(); 
	ataLbaDisk->SetID(DriverID::_block);
	ataLbaDisk->SetName(device->GetDriverName());
	ataLbaDisk->SetData(device->GetDriverData());
	device->SetDriver(ataLbaDisk);
	kernel->device.RegisterBlockDevice((BlockDevice*)device->GetDriver());
	return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool AtaLbaDiskDrv::Remove(PlatDevice* device)
{
	kernel->device.UnregisterBlockDevice((BlockDevice*)device->GetDriver());
	delete (AtaLbaDisk*)device->GetDriver();
	return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new AtaLbaDiskDrv(), ataLbaDisk, ataLbaDiskDrv);
