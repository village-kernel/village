//###########################################################################
// SpiW25qxx.h
// Declarations of the functions that manage spi w25qxx
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SPI_W25QXX_H__
#define __SPI_W25QXX_H__

#include "Hardware.h"
#include "Driver.h"


/// @brief SpiW25qxx
class SpiW25qxx : public BlockDevice
{
public:
	//Structures
	struct Config
	{
		Spi::Channel spiCh;
		Gpio::Config sckGpio;
		Gpio::Config misoGpio;
		Gpio::Config mosiGpio;
		Gpio::Config csGpio;
		Gpio::Config wpGpio;
	};

	//Enumerations
	enum IOCtrlCmd
	{
		_GetSectorCount = 1,
		_GetSectorSize  = 2,
		_GetBlockSize   = 3,
	};
private:
	//Static Constants
	static const uint16_t OneSectorByteSize = 4096;
	static const uint16_t OneSectorPageSize = 16;
	static const uint16_t OnePageByteSize = 256;
	static const uint16_t DeviceID = 0xEF16;
	static const uint16_t sector_count = 16384;
	static const uint16_t sector_size = 512;
	static const uint16_t block_size = 1;

	//Enumerations
	enum FlashCmd
	{
		_WriteEnable         = 0x06,
		_WriteEnableForVSR   = 0x50,
		_WriteDisable        = 0x04,

		_ReadStatusRegister  = 0x05,
		_WriteStatusRegister = 0x01,

		_ReadData            = 0x03,
		_FastRead            = 0x0B,
		_FastReadDualOutput  = 0x3B,
		_FastReadDualIO      = 0xBB,

		_PageProgram         = 0x02,

		_SectorErase         = 0x20,
		_32KBBlockErase      = 0x52,
		_BlockErase          = 0xD8,
		_ChipErase           = 0xC7,

		_PowerDown                      = 0xB9,
		_ReleasePowerDownDeviceID       = 0xAB,
		_ReadManufacturerDeviceID       = 0x90,
		_ReadManufacturerDeviceIDDualIO = 0x92,
		_ReadUniqueIDNumber             = 0x4B,
		_JEDECID                        = 0x9F,
	};

	//Periph Members
	Spi    spi;
	Gpio   csGpio;
	Gpio   wpGpio;
	Config config;

	//Members
	bool flashError;

	/// @brief Methods
	void PinConfig();
	void WriteAddr(uint32_t addr);
	void WriteCmd(uint8_t cmd);
	void WriteOneByte(uint8_t data);
	uint8_t ReadOneByte();
	void SelectChip();
	void UnselectChip();
	void EnableWP();
	void DisableWP();
	bool IsFlashError();
public:
	/// @brief Methods
	uint16_t GetDeviceID();
	void WriteEnable();
	void WriteDisable();
	void WaitForBusy();
	void EraseChip();
	void EraseSector(uint32_t address);
	void PageWriteBytes(uint8_t* txData, uint16_t size, uint32_t address);
	void SectorWriteBytes(uint8_t* txData, uint16_t size, uint32_t address);
	int WriteAnywhere(uint8_t *txData, uint32_t size, uint32_t address);
public:
	/// @brief Methods
	SpiW25qxx();
	~SpiW25qxx();

	/// @brief Plat Methods
	void SetData(void* data);

	/// @brief Fopts Methods
	bool Open();
	int Write(uint8_t *txData, uint32_t blkSize, uint32_t blk);
	int Read(uint8_t* rxData, uint32_t blkSize, uint32_t blk);
	int IOCtrl(uint8_t cmd, void* data);
	void Close();
};


/// @brief SpiW25qxxDrv
class SpiW25qxxDrv : public PlatDriver
{
public:
	/// @brief Plat Methods
	bool Probe(PlatDevice* device);
	bool Remove(PlatDevice* device);
};

#endif //!__SPI_W25QXX_H__
