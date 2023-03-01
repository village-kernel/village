//###########################################################################
// SpiFlash.h
//
// Communicates with an external flash using the SPI bus
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SPI_FLASH_H__
#define __SPI_FLASH_H__

#include "HalHeaders.h"
#include "Driver.h"
#include "Spi.h"
#include "Gpo.h"

///SpiFlash
class SpiFlash : public Driver
{
public:
	//Structures
	struct Config
	{
		Spi::Channel SpiCh;
		Spi::PinConfig SpiConfig;
		Gpio::GpioChannel flashcsCh;
		uint16_t flashcsPin;
		Gpio::GpioChannel flashwpCh;
		uint16_t flashwpPin;
	};
private:
	//Static Constants
	static const uint16_t OneSectorByteSize = 4096;
	static const uint16_t OneSectorPageSize = 16;
	static const uint16_t OnePageByteSize = 256;
	static const uint16_t DeviceID = 0xEF16;

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
	Spi spi;
	Gpo csPin;
	Gpo wpPin;
	Config config;

	//Members
	static bool flashError;

	//Methods
	void InitConfig();
	void WriteAddr(uint32_t addr);
	void WriteCmd(uint8_t cmd);
	void WriteOneByte(uint8_t data);
	uint8_t ReadOneByte();
	void SelectChip();
	void UnselectChip();
	void WaitForBusy();
	void WriteEnable();
	void WriteDisable();
public:
	//Methods
	void Initialize();
	void EraseChip();
	void EraseSector(uint32_t wordAddress);
	uint16_t GetDeviceID();

	void PageWriteBytes(uint8_t* txData, uint16_t size, uint32_t wordAddress);
	void SectorWriteBytes(uint8_t* txData, uint16_t size, uint32_t wordAddress);
	int WriteAnywhere(uint8_t *txData, uint32_t size, uint32_t wordAddress);
	
	int Write(uint8_t *txData, uint32_t size, uint32_t wordAddress);
	int Read(uint8_t* rxData, uint32_t size, uint32_t wordAddress);

	//Enable write protection
	inline void EnableWP() { wpPin.Clear(); }

	//Disable write protection
	inline void DisableWP() { wpPin.Set(); }

	//Check flash is error
	inline bool IsFlashError() { return flashError; }
};

#endif //!__SPI_FLASH_H__
