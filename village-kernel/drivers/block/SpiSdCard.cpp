//###########################################################################
// SpiSdCard.cpp
// Definitions of the functions that manage spi sdcard disk
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "HwConfig.h"
#include "Hardware.h"
#include "Driver.h"
#include "Kernel.h"


/// @brief SpiSdCard
class SpiSdCard : public Driver
{
public:
	//Enumerations
	enum SdCardType
	{
		_NONE = 0x00,
		_MMC  = 0x01,
		_V1   = 0x02,
		_V2   = 0x04,
		_V2HC = 0x06,
	};

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

	//Structures
	struct Config
	{
		Spi::Channel spiCh;
		Gpio::Config sckGpio;
		Gpio::Config misoGpio;
		Gpio::Config mosiGpio;
		Gpio::Config csGpio;
		Gpio::Config dtGpio;
	};
private:
	enum SdCardCmd
	{
		_Reset              = 0,
		_GetOCR             = 1,
		_SendIfCond         = 8,
		_SendCSD            = 9,
		_SendCID            = 10,
		_StopTrans          = 12,
		_SetBlockLen        = 16,
		_ReadSingleBlock    = 17,
		_ReadMultipleBlock  = 18,
		_SetWrBlkEraseCount = 23,
		_WriteBlock         = 24,
		_WriteMultipleBlock = 25,
		_SdSendOpCond       = 41,
		_AppCmd             = 55,
		_ReadOCR            = 58,
		_CRCOnOff           = 59,
	};

	enum DataResponse
	{
		_DataOk             = 0x05,
		_DataCrcErr         = 0x0b,
		_DataWriteErr       = 0x0d,
		_DataOtherErr       = 0xff,
	};

	enum CommResponese
	{
		_ResponseNoErr      = 0x00,
		_InIdleState        = 0x01,
		_EraseReset         = 0x02,
		_IllegalCmd         = 0x04,
		_ComCrcErr          = 0x08,
		_EraseSequenceErr   = 0x10,
		_AddressErr         = 0x20,
		_ParameterErr       = 0x40,
		_ResponseFailure    = 0xff,
	};

	//Members
	Spi spi;
	Gpio csGpio;
	Gpio dtGpio;
	Config config;
	SdCardType sdcardType;
	uint32_t sectorSize;
private:
	/// @brief Init config
	inline void InitConfig()
	{
		config = SPI_SDCARD_CONFIG;
		sectorSize = 512;
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
		dtGpio.Initialize(config.dtGpio);
	}
private:
	/// @brief Spi sd card write one byte writeData
	/// @param data 
	inline void WriteOneByte(uint8_t data)
	{
		spi.WriteAndReadOneByte(data);
	}


	/// @brief Spi sd card read one byte writeData
	/// @return 
	inline uint8_t ReadOneByte()
	{
		return spi.WriteAndReadOneByte(0xff);
	}


	/// @brief Spi sd card wait ready
	/// @return 
	inline uint8_t WaitReady()
	{
		for (uint16_t cnt = 0; cnt < 0xffff; cnt++)
		{
			if (0xff == ReadOneByte()) return 0;
		}
		return 1;
	}


	/// @brief Get sd card ack
	/// @param reponse 
	/// @return 
	inline uint8_t GetAck(uint8_t reponse)
	{
		for (uint32_t cnt = 0; cnt < 0xffff; cnt++)
		{
			if (ReadOneByte() == reponse) return _ResponseNoErr;
		}
		return _ResponseFailure;
	}


	/// @brief Spi select sd card
	/// @return 
	inline uint8_t SelectCard()
	{
		csGpio.Clear();
		if (0 == WaitReady()) return 0;
		UnselectCard();
		return 1;
	}


	/// @brief Spi unselect sd card
	/// @return 
	inline uint8_t UnselectCard()
	{
		csGpio.Set();
		ReadOneByte(); //Provide additional 8 clocks
		return 0;
	}


	/// @brief Spi sd card write cmd
	/// @param cmd 
	/// @param arg 
	/// @param crc 
	/// @return 
	inline uint8_t WriteCmd(uint8_t cmd, uint32_t arg, uint8_t crc)
	{
		const uint8_t write_separately = 0x40;

		//Release bus and select sd card
		UnselectCard();
		if (SelectCard()) return 0xff;

		//Send cmd, arg and crc
		WriteOneByte(cmd | write_separately);
		WriteOneByte((uint8_t)(arg >> 24));
		WriteOneByte((uint8_t)(arg >> 16));
		WriteOneByte((uint8_t)(arg >> 8));
		WriteOneByte((uint8_t)(arg));
		WriteOneByte(crc);

		//Wait response
		if (_StopTrans == cmd) ReadOneByte();

		uint8_t res = 0;

		for (uint8_t cnt = 0; cnt < 0x1f; cnt++)
		{
			res = ReadOneByte();
			if (0 == (res & _ComCrcErr)) return res; 
		}

		return res;
	}


	/// @brief Sd card send data
	/// @param txData 
	/// @param size 
	/// @param cmd 
	/// @return 
	inline uint8_t SendData(uint8_t *txData, uint16_t size, uint8_t cmd)
	{
		if (WaitReady()) return 1;

		WriteOneByte(cmd);

		if (0xfd != cmd)
		{
			for (uint16_t cnt = 0; cnt < sectorSize; cnt++)
			{
				if (cnt < size)
				{
					WriteOneByte(txData[cnt]);
				}
				else
				{
					WriteOneByte(0xff);
				}
			}
			//ignore crc
			WriteOneByte(0xff);
			WriteOneByte(0xff);
			
			//Get response
			uint8_t res = ReadOneByte();
			if (_DataOk != (res & 0x1f)) return 2;
		}
		return 0;
	}


	/// @brief Sd card receive data
	/// @param rxData 
	/// @param size 
	/// @return 
	inline uint8_t RecvData(uint8_t *rxData, uint16_t size)
	{
		if (GetAck(0xfe)) return 1;

		for (uint16_t cnt = 0; cnt < size; cnt++)
		{
			rxData[cnt] = ReadOneByte();
		}

		//ignore crc
		WriteOneByte(0xff);
		WriteOneByte(0xff);
		return 0;
	}


	/// @brief Spi sd card initialize
	/// @return 
	uint8_t SdCardInit()
	{
		uint8_t res;
		uint8_t data[4];

		//Release bus
		for(uint8_t i = 0; i < 10; i++)
		{
			WriteOneByte(0xff);
		}

		//Go to idle status
		for (uint8_t i = 0; i < 20; i++)
		{
			res = WriteCmd(_Reset, 0, 0x95);
			if (_InIdleState == res) break;
		}

		//Set sd card type
		sdcardType = _NONE;

		if (_InIdleState == res)
		{
			if (1 == WriteCmd(_SendIfCond, 0x1aa, 0x87)) //sd v2.0
			{
				for (uint8_t i = 0; i < 4; i++)
				{
					data[i] = ReadOneByte();
				}

				if ((0x01 == data[2]) && (0xaa == data[3])) //card support 2.7v~3.6v
				{
					for (uint16_t i = 0; i < 0xffff; i++)
					{
						res = WriteCmd(_AppCmd, 0, 0x01);
						res = WriteCmd(_SdSendOpCond, 0x40000000, 0x01);

						if (_ResponseNoErr == res) break;
					}

					if (_ResponseNoErr == res)
					{
						res = WriteCmd(_ReadOCR, 0, 0x01);

						if (_ResponseNoErr == res)
						{
							for (uint8_t i = 0; i < 4; i++)
							{
								data[i] = ReadOneByte();
							}
			
							sdcardType = (data[0] & 0x40) ? _V2HC : _V2;
						}
					}
				}
			}
			else //SD v1.x /mmc v3
			{
				uint16_t i = 0;

				res = WriteCmd(_AppCmd, 0, 0x01);
				res = WriteCmd(_SdSendOpCond, 0, 0x01);

				if (res <= 1)
				{
					sdcardType = _V1;
					for (i = 0; i < 0xffff; i++)
					{
						res = WriteCmd(_AppCmd, 0, 0x01);
						res = WriteCmd(_SdSendOpCond, 0, 0x01);

						if (_ResponseNoErr == res) break;
					}
				}
				else
				{
					sdcardType = _MMC;
					for (i = 0; i < 0xffff; i++)
					{
						res = WriteCmd(_GetOCR, 0, 0x01);
						if (_ResponseNoErr == res) break;
					}
				}

				if ((0xffff == i) || (_ResponseNoErr != WriteCmd(_SetBlockLen, sectorSize, 0x01)))
				{
					sdcardType = _NONE;
				}
			}
		}

		//Calculate the sector size
		sectorSize = (SdCardType::_V2HC != sdcardType) ? sectorSize : 1;

		UnselectCard();

		return (_NONE != sdcardType) ? 0 : res;
	}


	/// @brief Spi sd card get ocr data
	/// @param ocrData 
	/// @return 
	int GetOCR(uint8_t* ocrData)
	{
		uint8_t	res = WriteCmd(_ReadOCR, 0, 0x01);

		if (_ResponseNoErr == res)
		{
			for (uint8_t i = 0; i < 4; i++)
			{
				ocrData[i] = ReadOneByte();
			}
		}

		return res ? 1 : 0;
	}


	/// @brief Spi sd card get cid data
	/// @param cidData 
	/// @return 
	int GetCID(uint8_t* cidData)
	{
		uint8_t res = WriteCmd(_SendCID, 0, 0x01);
		
		if (_ResponseNoErr == res)
		{
			res = RecvData(cidData, 16);
		}
		
		UnselectCard();

		return res ? 1 : 0;
	}


	/// @brief Spi sd card get csd data
	/// @param csdData 
	/// @return 
	int GetCSD(uint8_t* csdData)
	{
		uint8_t res = WriteCmd(_SendCSD, 0, 0x01);
		
		if (_ResponseNoErr == res)
		{
			res = RecvData(csdData, 16);
		}
		
		UnselectCard();

		return res ? 1 : 0;
	}


	/// @brief Spi sd card get sector count
	/// @return 
	uint32_t GetSectorCount()
	{
		uint8_t csd[16];
		
		if (0 != GetCSD(csd)) return 0;

		//V2.00 card, sdhc
		if (0x40 == (csd[0]& 0xc0))
		{
			uint16_t size = csd[9] + ((uint16_t)csd[8] << 8) + 1;
			return (uint32_t)size << 10;
		}
		//V1.xx card
		else
		{
			uint8_t num = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
			uint16_t size = (csd[8] >> 6) + ((uint16_t)csd[7] << 2) + ((uint16_t)(csd[6] & 3) << 10) + 1;
			return (uint32_t)size << (num - 9);
		}
		return 0;
	}


	/// @brief Spi sd card Sync
	/// @return 
	int Sync()
	{
		uint8_t res = 1;
		csGpio.Clear();
		if (0 == WaitReady()) res = 0;
		csGpio.Set();
		return res;
	}
public:
	/// @brief Sd card initialize
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
		spi.ConfigBaudRatePrescaler(Spi::_Fpclk2);
		spi.ConfigFrame(Spi::_MsbFirst, Spi::_8Bit);
		spi.Enable();

		//Initialize sd card
		SdCardInit();

		return true;
	}


	/// @brief Spi sd card write data
	/// @param txData 
	/// @param blkSize 
	/// @param sector 
	/// @return 
	int Write(uint8_t *txData, uint32_t blkSize, uint32_t sector)
	{
		uint8_t res = 0;

		if (SdCardType::_V2HC != sdcardType) sector = sector * sectorSize;

		if (1 == blkSize)
		{
			res = WriteCmd(_WriteBlock, sector, 0x01);

			if (_ResponseNoErr == res)
			{
				res = SendData(txData, sectorSize, 0xfe);
			}
		}
		else
		{
			if (SdCardType::_MMC != sdcardType)
			{
				WriteCmd(_AppCmd, 0, 0x01);
				WriteCmd(_SetWrBlkEraseCount, blkSize, 0x01);
			}

			res = WriteCmd(_WriteMultipleBlock, sector, 0x01);

			if (_ResponseNoErr == res)
			{
				for (uint32_t cnt = 0; cnt < blkSize; cnt++)
				{
					res = SendData(txData, sectorSize, 0xfc);

					if (_ResponseNoErr != res) break;

					txData += sectorSize;
				}

				res = SendData(0, sectorSize, 0xfd);
			}
		}

		UnselectCard();

		return res;
	}


	/// @brief Spi sd card read data
	/// @param rxData 
	/// @param blkSize 
	/// @param sector 
	/// @return 
	int Read(uint8_t* rxData, uint32_t blkSize, uint32_t sector)
	{
		uint8_t res = 0;

		if (SdCardType::_V2HC != sdcardType) sector = sector << 9;

		if (1 == blkSize)
		{
			res = WriteCmd(_ReadSingleBlock, sector, 0x01);

			if (_ResponseNoErr == res)
			{
				res = RecvData(rxData, sectorSize);
			}
		}
		else
		{
			res = WriteCmd(_ReadMultipleBlock, sector, 0x01);

			if (_ResponseNoErr == res)
			{
				for (uint32_t cnt = 0; cnt < blkSize; cnt++)
				{
					res = RecvData(rxData, sectorSize);

					if (_ResponseNoErr != res) break;

					rxData += sectorSize;
				}
				WriteCmd(_StopTrans, 0, 0x01);
			}
		}

		UnselectCard();

		return res;
	}


	/// @brief Spi sd card io ctrl
	/// @param cmd 
	/// @param data 
	/// @return 
	int IOCtrl(uint8_t cmd, void* data)
	{
		switch (cmd)
		{
			case _CtrlSync: 
				Sync();
				break;
			case _GetSectorCount:
				*(uint32_t*)data = GetSectorCount();
				break;
			case _GetSectorSize:
				*(uint16_t *)data = sectorSize;
				break;
			case _GetBlockSzie:
				*(uint16_t *)data = 8;
				break;
			case _Ctrltrim:
				break;
			
			case _GetType:
				*(uint32_t *)data = 1;
				break;
			case _GetCSDData:
				GetCSD((uint8_t*)data);
				break;
			case _GetCIDData:
				GetCID((uint8_t*)data);
				break;
			case _GetOCRData:
				GetOCR((uint8_t*)data);
				break;
			case _GetSdstat:
				*(uint32_t *)data = 0;
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
REGISTER_DRIVER(new SpiSdCard(), DriverID::_block, spiSdCard);
