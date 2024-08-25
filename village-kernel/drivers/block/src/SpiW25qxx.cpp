//###########################################################################
// SpiW25qxx.cpp
// Definitions of the functions that manage spi w25qxx disk
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "SpiW25qxx.h"
#include "Kernel.h"


/// @brief Constructor
SpiW25qxx::SpiW25qxx()
{
}


/// @brief Destructor
SpiW25qxx::~SpiW25qxx()
{
}


/// @brief Init config
void SpiW25qxx::SetData(void* data)
{
	config = *((Config*)data);
	flashError = false;
}


/// @brief Pin config
inline void SpiW25qxx::PinConfig()
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


/// @brief Spi flash write writeAddr
/// @param addr 
inline void SpiW25qxx::WriteAddr(uint32_t addr)
{
	spi.WriteAndReadOneByte(addr >> 16);
	spi.WriteAndReadOneByte(addr >> 8);
	spi.WriteAndReadOneByte(addr);
}


/// @brief Spi flash write cmd
/// @param cmd 
inline void SpiW25qxx::WriteCmd(uint8_t cmd)
{
	spi.WriteAndReadOneByte(cmd);
}


/// @brief Spi flash write one byte writeData
/// @param data 
inline void SpiW25qxx::WriteOneByte(uint8_t data)
{
	spi.WriteAndReadOneByte(data);
}


/// @brief Spi flash read one byte writeData
/// @return 
inline uint8_t SpiW25qxx::ReadOneByte()
{
	return spi.WriteAndReadOneByte(0x00);
}


/// @brief Spi flash Select chip
inline void SpiW25qxx::SelectChip()
{
	csGpio.Clear();
}


/// @brief Spi flash Unselect chip
inline void SpiW25qxx::UnselectChip()
{
	csGpio.Set();
}


/// @brief Enable write protection
inline void SpiW25qxx::EnableWP()
{
	wpGpio.Clear();
}


/// @brief Disable write protection
inline void SpiW25qxx::DisableWP()
{
	wpGpio.Set();
}


/// @brief Check flash is error
/// @return 
inline bool SpiW25qxx::IsFlashError()
{
	return flashError;
}


/// @brief Spi flash Get ID
/// @return 
uint16_t SpiW25qxx::GetDeviceID()
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
void SpiW25qxx::WriteEnable()
{
	SelectChip();

	WriteCmd(_WriteEnable);

	UnselectChip();
}


/// @brief Spi flash chip disable
void SpiW25qxx::WriteDisable()
{
	SelectChip();

	WriteCmd(_WriteDisable);

	UnselectChip();
}


/// @brief Spi flash check busy
void SpiW25qxx::WaitForBusy()
{
	SelectChip();

	WriteCmd(_ReadStatusRegister);

	while ((ReadOneByte() & 0x01)) {}

	UnselectChip();
}


/// @brief Spi flash chip erase
void SpiW25qxx::EraseChip()
{
	WriteEnable();
	SelectChip();

	WriteCmd(_ChipErase);

	UnselectChip();
	WaitForBusy();
}


/// @brief Spi flash sector erase
/// @param address 
void SpiW25qxx::EraseSector(uint32_t address)
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
void SpiW25qxx::PageWriteBytes(uint8_t* txData, uint16_t size, uint32_t address)
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
void SpiW25qxx::SectorWriteBytes(uint8_t* txData, uint16_t size, uint32_t address)
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
int SpiW25qxx::WriteAnywhere(uint8_t *txData, uint32_t size, uint32_t address)
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


/// @brief Initializes the spi flase module
/// @return 
bool SpiW25qxx::Open()
{
	//Pin config
	PinConfig();

	//Initialize spi
	spi.Initialize(config.spiCh);
	spi.ConfigModeAndPins(Spi::_Master, Spi::_Cpol0Cpha0);
	spi.ConfigBaudRatePrescaler(Spi::_Fpclk16);
	spi.ConfigFrame(Spi::_MsbFirst, Spi::_8Bit);
	spi.Enable();

	//Check if the device id is correct
	if (GetDeviceID() != config.deviceID) flashError = true;

	return !flashError;
}


/// @brief Writes a specified number of bytes of writeData into provided address
/// @param txData 
/// @param blkSize 
/// @param blk 
/// @return 
int SpiW25qxx::Write(uint8_t *txData, uint32_t blkSize, uint32_t blk)
{
	//return if there are any problems with the flash;
	if (flashError) return 0;

	//Adapte fatfs
	uint32_t bytesRemain = blkSize * sector_size;
	uint32_t writeAddr = blk * sector_size;
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

	return flashError ? 0 : blkSize;
}


/// @brief Reads a specified number of bytes of writeData into the provided address
/// @param rxData 
/// @param blkSize 
/// @param blk 
/// @return 
int SpiW25qxx::Read(uint8_t* rxData, uint32_t blkSize, uint32_t blk)
{
	//return if there are any problems with the flash;
	if (flashError) return 0;

	//Adapte fatfs
	uint32_t readAddr = blk * sector_size;
	uint32_t readSize = blkSize * sector_size;

	SelectChip();

	WriteCmd(_ReadData);
	WriteAddr(readAddr);

	for (uint32_t i = 0; i < readSize; i++)
	{
		rxData[i] = ReadOneByte();
	}

	UnselectChip();

	return flashError ? 0 : blkSize;
}


/// @brief Spi flash io ctrl
/// @param cmd 
/// @param data 
/// @return 
int SpiW25qxx::IOCtrl(uint8_t cmd, void* data)
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
void SpiW25qxx::Close()
{

}


/// @brief Probe
/// @param device 
/// @return 
bool SpiW25qxxDrv::Probe(PlatDevice* device)
{
	SpiW25qxx* spiW25qxx = new SpiW25qxx(); 
	spiW25qxx->SetID(DriverID::_framebuffer);
	spiW25qxx->SetName(device->GetDriverName());
	spiW25qxx->SetData(device->GetDriverData());
	device->SetDriver(spiW25qxx);
	kernel->device.RegisterBlockDevice((BlockDevice*)device->GetDriver());
	return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool SpiW25qxxDrv::Remove(PlatDevice* device)
{
	kernel->device.UnregisterBlockDevice((BlockDevice*)device->GetDriver());
	delete (SpiW25qxx*)device->GetDriver();
	return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new SpiW25qxxDrv(), spiW25qxx, spiW25qxxDrv);
