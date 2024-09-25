//###########################################################################
// SdioSdCard.h
// Declarations of the functions that manage sdio sdcard
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SDIO_SD_CARD_H__
#define __SDIO_SD_CARD_H__

#include "Driver.h"
#include "Gpio.h"
#include "Sdio.h"


/// @brief SdioSdCard
class SdioSdCard : public BlockDriver
{
public:
	//Structures
	struct Config
	{
		Gpio::Config d0Gpio;
		Gpio::Config d1Gpio;
		Gpio::Config d2Gpio;
		Gpio::Config d3Gpio;
		Gpio::Config ckGpio;
		Gpio::Config cmdGpio;
	};

	//Enumerations
	enum IOCtrlCmd
	{
		_CtrlSync       = 0,
		_GetSectorCount = 1,
		_GetSectorSize  = 2,
		_GetBlockSzie   = 3,
		_Ctrltrim       = 4,

		_GetType        = 10,
		_GetCSDData     = 11,
		_GetCIDData     = 12,
		_GetOCRData     = 13,
		_GetSdstat      = 14,
	};
private:
	/// @brief const static members
	const static uint32_t sd_timeout = 30000;
	const static uint32_t sd_block_size = 512;

	/// @brief Members
	Sdio   sdio;
	Config config;

	/// @brief Methods
	void PinConfig();
	uint32_t GetTicks();
	bool CheckStatus();
	bool CheckStatusWithTimeout(uint32_t timeout);
public:
	/// @brief Methods
	SdioSdCard();
	~SdioSdCard();

	/// @brief Plat Methods
	void SetData(void* data);

	/// @brief Fopts Methods
	bool Open();
	int Write(uint8_t* data, uint32_t blkSize, uint32_t blk);
	int Read(uint8_t* data, uint32_t blkSize, uint32_t blk);
	int IOCtrl(uint8_t cmd, void *data);
	void Close();
};


/// @brief SdioSdCardDrv
class SdioSdCardDrv : public PlatDriver
{
public:
	/// @brief Plat Methods
	bool Probe(PlatDevice* device);
	bool Remove(PlatDevice* device);
};

#endif //!__SDIO_SD_CARD_H__
