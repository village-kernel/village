//###########################################################################
// SDMMC.cpp
// Definitions of the functions that manage sd mmc disk
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Driver.h"
#include "Kernel.h"
#include "HwConfig.h"
#include "Hardware.h"


/// @brief SDMMC
class SDMMC : public Driver
{
public:
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
	Sdio::Config config;
private:
	/// @brief Init config
	inline void InitConfig()
	{
		config.d0Ch     = SDMMC_D0_CH;
		config.d0Pin    = SDMMC_D0_PIN;
		config.d0AltNum = SDMMC_D0_AF_NUM;

		config.d1Ch     = SDMMC_D1_CH;
		config.d1Pin    = SDMMC_D1_PIN;
		config.d1AltNum = SDMMC_D1_AF_NUM;

		config.d2Ch     = SDMMC_D2_CH;
		config.d2Pin    = SDMMC_D2_PIN;
		config.d2AltNum = SDMMC_D2_AF_NUM;

		config.d3Ch     = SDMMC_D3_CH;
		config.d3Pin    = SDMMC_D3_PIN;
		config.d3AltNum = SDMMC_D3_AF_NUM;

		config.ckCh     = SDMMC_CK_CH;
		config.ckPin    = SDMMC_CK_PIN;
		config.ckAltNum = SDMMC_CK_AF_NUM;

		config.cmdCh     = SDMMC_CMD_CH;
		config.cmdPin    = SDMMC_CMD_PIN;
		config.cmdAltNum = SDMMC_CMD_AF_NUM;
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
	/// @brief Constructor
	SDMMC()
	{
	}


	/// @brief Destructor
	~SDMMC()
	{
	}


	/// @brief open
	bool Open()
	{
		//Init config
		InitConfig();

		//Initialize sdio
		if (Sdio::MSD_OK == sdio.Initialize(config))
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


	/// @brief SDMMC io ctrl
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
REGISTER_DRIVER(new SDMMC(), DriverID::_block, disk0);
