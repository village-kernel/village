//###########################################################################
// SpiW25qxx.cpp
// Definitions of the functions that manage spi w25qxx disk
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "HwConfig.h"
#include "Hardware.h"
#include "Driver.h"
#include "Kernel.h"


/// @brief SpiW25qxx
class SpiW25qxx : public Driver
{
public:
	//Enumerations
	enum IOCtrlCmd
	{
		_GetSectorCount = 1,
		_GetSectorSize  = 2,
		_GetBlockSize   = 3,
	};

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
	Spi spi;
	Gpio csGpio;
	Gpio wpGpio;
	Config config;

	//Members
	bool flashError;
private:
	/// @brief Init config
	inline void InitConfig()
	{
		config = SPI_FLASH_CONFIG;
		flashError = false;
	}


	/// @brief Pin config
	inline void PinConfig()
	{
		Gpio gpio;

		gpio.Initialize(config.sckGpio);
		gpio.ConfigOutputType(Gpio::_PushPull);
		gpio.ConfigInputType(Gpio::_PullUp);
		gpio.ConfigSpeed(Gpio::_HighSpeed);

		gpio.Initialize(config.mosiGpio);
		gpio.ConfigOutputType(Gpio::_PushPull);
		gpio.ConfigInputType(Gpio::_PullUp);
		gpio.ConfigSpeed(Gpio::_HighSpeed);

		gpio.Initialize(config.misoGpio);
		gpio.ConfigOutputType(Gpio::_PushPull);
		gpio.ConfigInputType(Gpio::_PullUp);
		gpio.ConfigSpeed(Gpio::_HighSpeed);

		csGpio.Initialize(config.csGpio);
		wpGpio.Initialize(config.wpGpio);
	}
private:
	/// @brief Spi flash write writeAddr
	/// @param addr 
	inline void WriteAddr(uint32_t addr)
	{
		spi.WriteAndReadOneByte(addr >> 16);
		spi.WriteAndReadOneByte(addr >> 8);
		spi.WriteAndReadOneByte(addr);
	}


	/// @brief Spi flash write cmd
	/// @param cmd 
	inline void WriteCmd(uint8_t cmd)
	{
		spi.WriteAndReadOneByte(cmd);
	}


	/// @brief Spi flash write one byte writeData
	/// @param data 
	inline void WriteOneByte(uint8_t data)
	{
		spi.WriteAndReadOneByte(data);
	}


	/// @brief Spi flash read one byte writeData
	/// @return 
	inline uint8_t ReadOneByte()
	{
		return spi.WriteAndReadOneByte(0x00);
	}


	/// @brief Spi flash Select chip
	inline void SelectChip() { csGpio.Clear(); }


	/// @brief Spi flash Unselect chip
	inline void UnselectChip() { csGpio.Set(); }


	/// @brief Enable write protection
	inline void EnableWP() { wpGpio.Clear(); }


	/// @brief Disable write protection
	inline void DisableWP() { wpGpio.Set(); }


	/// @brief Check flash is error
	/// @return 
	inline bool IsFlashError() { return flashError; }
private:
	/// @brief Spi flash Get ID
	/// @return 
	uint16_t GetDeviceID()
	{
		SelectChip();

		WriteCmd(_ReadManufacturerDeviceID);
		WriteAddr(0);

		//manufacturer id and device id
		uint16_t id = (uint16_t)ReadOneByte() << 8 | (uint16_t)ReadOneByte();

		UnselectChip();
		return id;
	}


	/// @brief Spi flash chip enable
	void WriteEnable()
	{
		SelectChip();

		WriteCmd(_WriteEnable);

		UnselectChip();
	}


	/// @brief Spi flash chip disable
	void WriteDisable()
	{
		SelectChip();

		WriteCmd(_WriteDisable);

		UnselectChip();
	}


	/// @brief Spi flash check busy
	void WaitForBusy()
	{
		SelectChip();

		WriteCmd(_ReadStatusRegister);

		while ((ReadOneByte() & 0x01)) {}

		UnselectChip();
	}


	/// @brief Spi flash chip erase
	void EraseChip()
	{
		WriteEnable();
		SelectChip();

		WriteCmd(_ChipErase);

		UnselectChip();
		WaitForBusy();
	}


	/// @brief Spi flash sector erase
	/// @param address 
	void EraseSector(uint32_t address)
	{
		WriteEnable();
		SelectChip();

		WriteCmd(_SectorErase);
		WriteAddr(address);

		UnselectChip();
		WaitForBusy();
	}


	/// @brief Spi flash page write
	/// @param txData 
	/// @param size 
	/// @param address 
	void PageWriteBytes(uint8_t* txData, uint16_t size, uint32_t address)
	{
		WriteEnable();
		SelectChip();

		WriteCmd(_PageProgram);
		WriteAddr(address);

		for (uint16_t i = 0; i < size; i++)
		{
			WriteOneByte(txData[i]);
		}

		UnselectChip();
		WaitForBusy();
	}


	/// @brief Spi flash sector write
	/// @param txData 
	/// @param size 
	/// @param address 
	void SectorWriteBytes(uint8_t* txData, uint16_t size, uint32_t address)
	{
		uint16_t bytesRemain = size;
		uint32_t writeAddr = address;
		uint8_t* writeData = txData;

		while (bytesRemain)
		{
			//Calculate the size of the write data
			uint16_t writeSize = OnePageByteSize - (uint8_t)writeAddr;
			if (bytesRemain < writeSize) writeSize = bytesRemain;

			//Write bytes
			PageWriteBytes(writeData, writeSize, writeAddr);
			bytesRemain -= writeSize;
			writeAddr += writeSize;
			writeData += writeSize;
		}
	}


	/// @brief Writes a specified number of bytes of writeData into provided address
	/// @param txData 
	/// @param size 
	/// @param address 
	/// @return 
	int WriteAnywhere(uint8_t *txData, uint32_t size, uint32_t address)
	{
		//return if there are any problems with the flash;
		if (flashError) return -1;

		uint32_t bytesRemain = size;
		uint32_t writeAddr = address;
		uint8_t* writeData = txData;
		uint8_t  buffer[OneSectorByteSize] = { 0 };

		while (bytesRemain)
		{
			//Calculate the size of the write data
			uint32_t sectorStartAddr = writeAddr >> 12 << 12;
			uint32_t sectorWriteAddr = writeAddr & (OneSectorByteSize - 1);
			uint32_t sectorWriteSize = OneSectorByteSize - sectorWriteAddr;
			if (bytesRemain < sectorWriteSize) sectorWriteSize = bytesRemain;

			//Read sector data to buffer
			Read(buffer, OneSectorByteSize, sectorStartAddr);
			
			//Erase sector
			EraseSector(sectorStartAddr);

			//Integrate data into the buffer
			for (uint32_t i = 0; i < sectorWriteSize; i++)
			{
				buffer[sectorWriteAddr + i] = writeData[i];
			}

			//Calculate write address offset
			uint32_t offset = 0;
			for (uint32_t i = 0; i < OneSectorByteSize; i++)
			{
				if (buffer[i] != 0xff)
				{
					offset = i;
					break;
				}
			}

			//Calculate the size of the write data
			uint32_t writeSize = 0;
			for (uint32_t i = OneSectorByteSize; i > 0; i--)
			{
				if (buffer[i - 1] != 0xff)
				{
					writeSize = i - offset;
					break;
				}
			}

			//Write data into sector
			SectorWriteBytes(buffer + offset, writeSize, sectorStartAddr + offset);

			//Update bytes reamin, write address and write data
			bytesRemain -= sectorWriteSize;
			writeAddr += sectorWriteSize;
			writeData += sectorWriteSize;
		}

		return size;
	}
public:
	/// @brief Initializes the spi flase module
	/// @return 
	bool Open()
	{
		//Init config
		InitConfig();

		//Pin config
		PinConfig();

		//Initialize spi
		spi.Initialize(config.spiCh);
		spi.ConfigModeAndPins(Spi::_Master, Spi::_Cpol0Cpha0);
		spi.ConfigBaudRatePrescaler(Spi::_Fpclk16);
		spi.ConfigFrame(Spi::_MsbFirst, Spi::_8Bit);
		spi.Enable();

		//Check if the device id is correct
		if (GetDeviceID() != DeviceID) flashError = true;

		return !flashError;
	}

	
	/// @brief Writes a specified number of bytes of writeData into provided address
	/// @param txData 
	/// @param blkSize 
	/// @param sector 
	/// @return 
	int Write(uint8_t *txData, uint32_t blkSize, uint32_t sector)
	{
		//return if there are any problems with the flash;
		if (flashError) return -1;

		//Adapte fatfs
		uint32_t bytesRemain = blkSize * sector_size;
		uint32_t writeAddr = sector * sector_size;
		uint8_t* writeData = txData;

		while (bytesRemain)
		{
			//Erase sector
			if (0 == (writeAddr % OneSectorByteSize))
			{
				EraseSector(writeAddr);
			}

			//Calculate the size of the write data
			uint16_t writeSize = OnePageByteSize - (uint8_t)writeAddr;
			if (bytesRemain < writeSize) writeSize = bytesRemain;

			//Write bytes
			PageWriteBytes(writeData, writeSize, writeAddr);
			bytesRemain -= writeSize;
			writeAddr += writeSize;
			writeData += writeSize;
		}

		return flashError ? -1 : 0;
	}


	/// @brief Reads a specified number of bytes of writeData into the provided address
	/// @param rxData 
	/// @param blkSize 
	/// @param sector 
	/// @return 
	int Read(uint8_t* rxData, uint32_t blkSize, uint32_t sector)
	{
		//return if there are any problems with the flash;
		if (flashError) return -1;

		//Adapte fatfs
		uint32_t readAddr = sector * sector_size;
		uint32_t readSize = blkSize * sector_size;

		SelectChip();

		WriteCmd(_ReadData);
		WriteAddr(readAddr);

		for (uint32_t i = 0; i < readSize; i++)
		{
			rxData[i] = ReadOneByte();
		}

		UnselectChip();

		return flashError ? -1 : 0;;
	}


	/// @brief Spi flash io ctrl
	/// @param cmd 
	/// @param data 
	/// @return 
	int IOCtrl(uint8_t cmd, void* data)
	{
		switch (cmd)
		{
			case _GetSectorCount:
				*(uint32_t*)data = sector_count;
				break;
			case _GetSectorSize:
				*(uint16_t *)data = sector_size;
				break;
			case _GetBlockSize:
				*(uint16_t *)data = block_size;
			default: break;
		}
		return 0;
	}


	/// @brief Close
	void Close()
	{

	}
};


///Register driver
REGISTER_DRIVER(new SpiW25qxx(), DriverID::_block, spiW25qxx);
