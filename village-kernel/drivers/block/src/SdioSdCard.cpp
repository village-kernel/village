//###########################################################################
// SdioSdCard.cpp
// Definitions of the functions that manage sdio sdcard disk
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "SdioSdCard.h"
#include "Kernel.h"


/// @brief Constructor
SdioSdCard::SdioSdCard()
{
}


/// @brief Destructor
SdioSdCard::~SdioSdCard()
{
}


/// @brief SetData
void SdioSdCard::SetData(void* data)
{
	config = *((Config*)data);
}


/// @brief Pin configure
/// @param config 
void SdioSdCard::PinConfig()
{
	Gpio pin;
	pin.Initialize(config.d0Gpio);
	pin.Initialize(config.d1Gpio);
	pin.Initialize(config.d2Gpio);
	pin.Initialize(config.d3Gpio);
	pin.Initialize(config.ckGpio);
	pin.Initialize(config.cmdGpio);
}


/// @brief GetTicks
/// @return 
uint32_t SdioSdCard::GetTicks()
{
	return kernel->system.GetSysClkCounts();
}


/// @brief CheckStatus
/// @return 
bool SdioSdCard::CheckStatus()
{
	return (sdio.GetCardState() == Sdio::MSD_OK);
}


/// @brief CheckStatusWithTimeout
/// @param timeout 
/// @return 
bool SdioSdCard::CheckStatusWithTimeout(uint32_t timeout)
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


/// @brief open
bool SdioSdCard::Open()
{
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
int SdioSdCard::Write(uint8_t* data, uint32_t blkSize, uint32_t blk)
{
	uint32_t sector  = blk;
	uint32_t count   = 0;
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
int SdioSdCard::Read(uint8_t* data, uint32_t blkSize, uint32_t blk)
{
	uint32_t sector  = blk;
	uint32_t count   = 0;
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
int SdioSdCard::IOCtrl(uint8_t cmd, void *data)
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
void SdioSdCard::Close()
{
	sdio.Uninitialize();
}


/// @brief Probe
/// @param device 
/// @return 
bool SdioSdCardDrv::Probe(PlatDevice* device)
{
	SdioSdCard* sdioSdCard = new SdioSdCard(); 
	sdioSdCard->SetID(DriverID::_block);
	sdioSdCard->SetName(device->GetDriverName());
	sdioSdCard->SetData(device->GetDriverData());
	device->SetDriver(sdioSdCard);
	kernel->device.RegisterBlockDevice((BlockDriver*)device->GetDriver());
	return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool SdioSdCardDrv::Remove(PlatDevice* device)
{
	kernel->device.UnregisterBlockDevice((BlockDriver*)device->GetDriver());
	delete (SdioSdCard*)device->GetDriver();
	device->SetDriver(NULL);
	return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new SdioSdCardDrv(), sdioSdCard, sdioSdCardDrv);
