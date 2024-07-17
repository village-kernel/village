//###########################################################################
// SpiSdCard.h
//
// Communicates with sd card using the SPI bus
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SPI_SD_CARD_H__
#define __SPI_SD_CARD_H__

#include "Hardware.h"
#include "Driver.h"


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
		Spi::Channel SpiCh;
		Spi::PinConfig SpiConfig;
		Gpio::GpioChannel sdcsCh;
		uint16_t sdcsPin;
		Gpio::GpioChannel detectCh;
		uint16_t detectPin;
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
	Gpo csPin;
	Gpi detectPin;
	SdCardType sdcardType;
	Config config;

	//Methods
	void InitConfig();
	void WriteOneByte(uint8_t data);
	uint8_t ReadOneByte();
	uint8_t WaitReady();
	uint8_t GetAck(uint8_t reponse);
	uint8_t SelectCard();
	uint8_t UnselectCard();
	uint8_t WriteCmd(uint8_t cmd, uint32_t arg, uint8_t crc);
	uint8_t SendData(uint8_t *txData, uint16_t size, uint8_t cmd);
	uint8_t RecvData(uint8_t *rxData, uint16_t size);
	uint8_t SdCardInit();
	uint32_t GetSectorCount();
	int GetOCR(uint8_t* ocrData);
	int GetCID(uint8_t* cidData);
	int GetCSD(uint8_t* csdData);
	int Sync();
public:
	//Methods
	bool Open();
	int Write(uint8_t *txData, uint32_t blkSize, uint32_t sector);
	int Read(uint8_t* rxData, uint32_t blkSize, uint32_t sector);
	int IOCtrl(uint8_t cmd, void* data);
	void Close();
};

#endif //!__SPI_SD_CARD_H__
