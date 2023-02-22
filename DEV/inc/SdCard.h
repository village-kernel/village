//###########################################################################
// SdCard.h
//
// Communicates with sd card using the SPI bus
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SD_CARD_H__
#define __SD_CARD_H__

#include "HalHeaders.h"
#include "Spi.h"
#include "Gpo.h"
#include "Gpi.h"

///SdCard
class SdCard
{
public:
	enum SdCardType
	{
		_NONE = 0x00,
		_MMC  = 0x01,
		_V1   = 0x02,
		_V2   = 0x04,
		_V2HC = 0x06,
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
		_data_ok            = 0x05,
		_data_CRC_err       = 0x0b,
		_data_write_err     = 0x0d,
		_data_other_err     = 0xff,
	};

	enum CommResponese
	{
		_response_no_err    = 0x00,
		_in_idle_state      = 0x01,
		_erase_reset        = 0x02,
		_illegal_cmd        = 0x04,
		_com_crc_err        = 0x08,
		_erase_sequence_err = 0x10,
		_address_err        = 0x20,
		_parameter_err      = 0x40,
		_response_failure   = 0xff,
	};

	//Members
	Spi spi;
	Gpo csPin;
	Gpi detectPin;
	SdCardType sdcardType;

	//Methods
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
public:
	//Methods
	void Initialize(Config config);
	int Write(uint8_t *txData, uint32_t blkSize, uint32_t sector);
	int Read(uint8_t* rxData, uint32_t blkSize, uint32_t sector);
	int GetCID(uint8_t* cidData);
	int GetCSD(uint8_t* csdData);
	uint32_t GetSectorCount();
};

#endif //!__SD_CARD_H__
