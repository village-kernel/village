//###########################################################################
// vk_ata_lba_disk.h
// Declarations of the functions that manage ata lab disk
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_ATA_LBA_DISK_H__
#define __VK_ATA_LBA_DISK_H__

#include "vk_hardware.h"
#include "vk_driver.h"
#include "vk_mutex.h"


/// @brief AtaLbaDisk
class AtaLbaDisk : public BlockDriver
{
public:
	//Config
	struct Config
	{
		uint8_t drv;
	};
private:
	/// @brief Members
	Config  config;
	Mutex   mutex;
public:
	/// @brief Methods
	AtaLbaDisk();
	~AtaLbaDisk();

	/// @brief Plat Methods
	void SetData(void* data);

	/// @brief Fopts Methods
	bool Open();
	int Write(uint8_t* data, uint32_t count, uint32_t blk);
	int Read(uint8_t* data, uint32_t count, uint32_t blk);
	void Close();
};


/// @brief AtaLbaDiskDrv
class AtaLbaDiskDrv : public PlatDriver
{
public:
	/// @brief Plat Methods
	bool Probe(PlatDevice* device);
	bool Remove(PlatDevice* device);
};

#endif //!__VK_ATA_LBA_DISK_H__
