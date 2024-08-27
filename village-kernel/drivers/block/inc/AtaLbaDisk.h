//###########################################################################
// AtaLabDisk.h
// Declarations of the functions that manage ata lab disk
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ATA_LBA_DISK_H__
#define __ATA_LBA_DISK_H__

#include "Hardware.h"
#include "Driver.h"
#include "Mutex.h"


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

#endif //!__ATA_LBA_DISK_H__
