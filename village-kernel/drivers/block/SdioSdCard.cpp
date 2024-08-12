//###########################################################################
// SdioSdCard.cpp
// Definitions of the functions that manage sdio sdcard disk
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Driver.h"
#include "Kernel.h"
#include "HwConfig.h"
#include "Hardware.h"


/// @brief SdioSdCard
class SdioSdCard : public Driver
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
	//const static members
	const static uint32_t sd_timeout = 30000;
	const static uint32_t sd_block_size = 512;

	//Members
	Sdio sdio;
	Config config;
private:
	/// @brief Init config
	inline void InitConfig()
	{
		config = SDMMC_CONFIG;
	}

	/// @brief Pin configure
	/// @param config 
	inline void PinConfig()
	{
		Gpio pin;
		pin.Initialize(config.d0Gpio);
		pin.Initialize(config.d1Gpio);
		pin.Initialize(config.d2Gpio);
		pin.Initialize(config.d3Gpio);
		pin.Initialize(config.ckGpio);
		pin.Initialize(config.cmdGpio);
	}
private:
	/// @brief GetTicks
	/// @return 
	uint32_t GetTicks()
	{
		return kernel->system.GetSysClkCounts();
	}


	/// @brief CheckStatus
	/// @return 
	bool CheckStatus()
	{
		return (sdio.GetCardState() == Sdio::MSD_OK);
	}


	/// @brief CheckStatusWithTimeout
	/// @param timeout 
	/// @return 
	bool CheckStatusWithTimeout(uint32_t timeout)
	{
		uint32_t timer = GetTicks();

		//block until SDIO IP is ready again or a timeout occur
		while (GetTicks() - timer < timeout)
		{
			if (sdio.GetCardState() == Sdio::SD_TRANSFER_OK)
			{
				return true;
			}
		}

		return false;
	}
public: 
	/// @brief open
	bool Open()
	{
		//Init config
		InitConfig();

		//Pin config
		PinConfig();

		//Initialize sdio
		if (Sdio::MSD_OK == sdio.Initialize())
		{
			return CheckStatus();
		}

		return false;
	}


	/// @brief Write data
	/// @param data 
	/// @param blkSize 
	/// @param sector 
	/// @return 
	int Write(uint8_t* data, uint32_t blkSize, uint32_t sector)
	{
		uint32_t count = 0;
		uint32_t timeout = 0;

		sdio.ClearWriteStatus();

		if (CheckStatusWithTimeout(sd_timeout) == false)
		{
			return count;
		}

		if (sdio.WriteBlocksDMA(data, blkSize, sector) == Sdio::MSD_OK)
		{
			//Wait that writing process is completed or a timeout occurs
			timeout = GetTicks();
			while ((sdio.GetWriteStatus() == false) && ((GetTicks() - timeout) < sd_timeout)) {}

			//in case of a timeout return error
			if (sdio.GetWriteStatus() == false)
			{
				count = 0;
			}
			else
			{
				sdio.ClearWriteStatus();
				timeout = GetTicks();

				while ((GetTicks() - timeout) < sd_timeout)
				{
					if (sdio.GetCardState() == Sdio::SD_TRANSFER_OK)
					{
						count = blkSize;
						break;
					}
				}
			}
		}

		return count;
	}


	/// @brief Read data
	/// @param data 
	/// @param blkSize 
	/// @param sector 
	/// @return 
	int Read(uint8_t* data, uint32_t blkSize, uint32_t sector)
	{
		uint32_t count = 0;
		uint32_t timeout = 0;

		//ensure the SDCard is ready for a new operation
		if (CheckStatusWithTimeout(sd_timeout) == false)
		{
			return count;
		}

		if (sdio.ReadBlocksDMA(data, blkSize, sector) == Sdio::MSD_OK)
		{
			sdio.ClearReadStatus();
			
			//Wait that the reading process is completed or a timeout occurs
			timeout = GetTicks();
			while((sdio.GetReadStatus() == false) && ((GetTicks() - timeout) < sd_timeout)) {}
			
			//in case of a timeout return error
			if (sdio.GetReadStatus() == false)
			{
				count = 0;
			}
			else
			{
				sdio.ClearReadStatus();
				timeout = GetTicks();

				while ((GetTicks() - timeout) < sd_timeout)
				{
					if (sdio.GetCardState() == Sdio::SD_TRANSFER_OK)
					{
						count = blkSize;
						break;
					}
				}
			}
		}

		return count;
	}


	/// @brief SdioSdCard io ctrl
	/// @param cmd 
	/// @param data 
	/// @return 
	int IOCtrl(uint8_t cmd, void *data)
	{
		Sdio::SDCardInfo cardInfo;

		switch (cmd)
		{
			//Make sure that no pending write process
			case _CtrlSync :
				break;

			//Get number of sectors on the disk (uint32_t)
			case _GetSectorCount :
				sdio.GetCardInfo(&cardInfo);
				*(uint32_t*)data = cardInfo.LogBlockNbr;
				break;

			//Get R/W sector size (uint32_t)
			case _GetSectorSize :
				sdio.GetCardInfo(&cardInfo);
				*(uint32_t*)data = cardInfo.LogBlockSize;
				break;

			//Get erase block size in unit of sector (uint32_t)
			case _GetBlockSzie :
				sdio.GetCardInfo(&cardInfo);
				*(uint32_t*)data = cardInfo.LogBlockSize / sd_block_size;
				break;

			default: break;
		}
		return 0;
	}


	/// @brief close
	void Close()
	{
		sdio.Uninitialize();
	}
};


///Register driver
REGISTER_DRIVER(new SdioSdCard(), DriverID::_block, sdioSdCard);
