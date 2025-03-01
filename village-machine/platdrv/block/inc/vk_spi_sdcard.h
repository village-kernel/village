//###########################################################################
// vk_spi_sdcard.h
// Declarations of the functions that manage spi sdcard
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_SPI_SD_CARD_H__
#define __VK_SPI_SD_CARD_H__

#include "vk_hardware.h"
#include "vk_driver.h"
#include "vk_drv_gpio.h"
#include "vk_drv_spi.h"


/// @brief SpiSdCard
class SpiSdCard : public BlockDriver
{
public:
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
private:
    //Members
    Spi        spi;
    Gpio       csGpio;
    Gpio       dtGpio;
    Config     config;
    SdCardType sdcardType;
    uint32_t   sectorSize;

    /// @brief Methods
    void PinConfig();
    void WriteOneByte(uint8_t data);
    uint8_t ReadOneByte();
    uint8_t WaitReady();
    uint8_t GetAck(uint8_t reponse);
    uint8_t SelectCard();
    uint8_t UnselectCard();
    uint8_t WriteCmd(uint8_t cmd, uint32_t arg, uint8_t crc);
    uint8_t SendData(uint8_t *txData, uint16_t size, uint8_t cmd);
    uint8_t RecvData(uint8_t *rxData, uint16_t size);
public:
    /// @brief Methods    
    uint8_t SdCardInit();
    int GetOCR(uint8_t* ocrData);
    int GetCID(uint8_t* cidData);
    int GetCSD(uint8_t* csdData);
    uint32_t GetSectorCount();
    int Sync();
public:
    /// @brief Methods
    SpiSdCard();
    ~SpiSdCard();

    /// @brief Plat Methods
    void SetData(void* data);

    /// @brief Fopts Methods
    bool Open();
    int Write(uint8_t *txData, uint32_t blkSize, uint32_t blk);
    int Read(uint8_t* rxData, uint32_t blkSize, uint32_t blk);
    int IOCtrl(uint8_t cmd, void* data);
    void Close();
};


/// @brief SpiSdCardDrv
class SpiSdCardDrv : public PlatDriver
{
public:
    /// @brief Plat Methods
    bool Probe(PlatDevice* device);
    bool Remove(PlatDevice* device);
};

#endif //!__VK_SPI_SD_CARD_H__
