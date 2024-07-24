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
private:
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
		sdio.Initialize(config);

		return true;
	}


	/// @brief close
	void Close()
	{

	}


	/// @brief Write data
	/// @param data 
	/// @param count 
	/// @param blk 
	/// @return 
	int Write(uint8_t* data, uint32_t count = 0, uint32_t blk = 0)
	{
		return sdio.Write(data, count, blk);
	}


	/// @brief Read data
	/// @param data 
	/// @param count 
	/// @param blk 
	/// @return 
	int Read(uint8_t* data, uint32_t count = 0, uint32_t blk = 0)
	{
		return sdio.Read(data, count, blk);
	}
};


///Register driver
REGISTER_DRIVER(new SDMMC(), DriverID::_block, disk0);
