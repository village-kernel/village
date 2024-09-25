//###########################################################################
// Sdio.h
// Hardware Layer class that manages a single sdio module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SDIO_H__
#define __SDIO_H__

#include "stm32h7xx.h"
#include "Gpio.h"


/// @brief Sdio
class Sdio
{
public:
	enum SDStatus
	{
		MSD_OK                    = 0x00,
		MSD_ERROR                 = 0x01,
		MSD_ERROR_SD_NOT_PRESENT  = 0x02,
	};

	enum SDTransferStatus
	{
		SD_TRANSFER_OK           = 0x00,
		SD_TRANSFER_BUSY         = 0x01,
	};

	enum SDInitStatus
	{
		SD_PRESENT               = 0x01,
		SD_NOT_PRESENT           = 0x00,
		SD_DATATIMEOUT           = 100000000,
	};

	struct SDCardInfo
	{
		uint32_t CardType;
		uint32_t CardVersion;
		uint32_t Class;
		uint32_t RelCardAdd;
		uint32_t BlockNbr;
		uint32_t BlockSize;
		uint32_t LogBlockNbr;
		uint32_t LogBlockSize;
		uint32_t CardSpeed;
	} ;
private:
	//Members
	static SD_HandleTypeDef hsd;

	//Static members
	static volatile uint8_t writeStatus;
	static volatile uint8_t readStatus;
public:
	//Methods
	uint8_t Initialize();
	uint8_t Uninitialize();
	uint8_t WriteBlocks(uint8_t* data, uint32_t count, uint32_t blk, uint32_t timeout);
	uint8_t ReadBlocks(uint8_t* data, uint32_t count, uint32_t blk, uint32_t timeout);
	uint8_t WriteBlocksDMA(uint8_t* data, uint32_t count, uint32_t blk);
	uint8_t ReadBlocksDMA(uint8_t* data, uint32_t count, uint32_t blk);
	uint8_t Erase(uint32_t startAddr, uint32_t endAddr);
	uint8_t GetCardState();
	void GetCardInfo(SDCardInfo *cardInfo);

	//Static methods
	static void IRQHandler();
	static void ClearWriteStatus();
	static void SetWriteStatus();
	static void ClearReadStatus();
	static void SetReadStatus();
	static bool GetWriteStatus();
	static bool GetReadStatus();
};

#endif // !__SDIO_H__
