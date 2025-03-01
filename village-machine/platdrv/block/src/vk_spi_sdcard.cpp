//###########################################################################
// vk_spi_sdcard.cpp
// Definitions of the functions that manage spi sdcard disk
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_spi_sdcard.h"
#include "vk_kernel.h"


/// @brief Constructor
SpiSdCard::SpiSdCard()
{
}


/// @brief Destructor
SpiSdCard::~SpiSdCard()
{
}


/// @brief Set data
void SpiSdCard::SetData(void* data)
{
    config = *((Config*)data);
    sectorSize = 512;
}


/// @brief Pin config
void SpiSdCard::PinConfig()
{
    Gpio gpio;
    gpio.Initialize(config.sckGpio);
    gpio.Initialize(config.mosiGpio);
    gpio.Initialize(config.misoGpio);
    csGpio.Initialize(config.csGpio);
    dtGpio.Initialize(config.dtGpio);
}


/// @brief Spi sd card write one byte writeData
/// @param data 
inline void SpiSdCard::WriteOneByte(uint8_t data)
{
    spi.WriteAndReadOneByte(data);
}


/// @brief Spi sd card read one byte writeData
/// @return 
inline uint8_t SpiSdCard::ReadOneByte()
{
    return spi.WriteAndReadOneByte(0xff);
}


/// @brief Spi sd card wait ready
/// @return 
inline uint8_t SpiSdCard::WaitReady()
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
inline uint8_t SpiSdCard::GetAck(uint8_t reponse)
{
    for (uint32_t cnt = 0; cnt < 0xffff; cnt++)
    {
        if (ReadOneByte() == reponse) return _ResponseNoErr;
    }
    return _ResponseFailure;
}


/// @brief Spi select sd card
/// @return 
inline uint8_t SpiSdCard::SelectCard()
{
    csGpio.Clear();
    if (0 == WaitReady()) return 0;
    UnselectCard();
    return 1;
}


/// @brief Spi unselect sd card
/// @return 
inline uint8_t SpiSdCard::UnselectCard()
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
inline uint8_t SpiSdCard::WriteCmd(uint8_t cmd, uint32_t arg, uint8_t crc)
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
inline uint8_t SpiSdCard::SendData(uint8_t *txData, uint16_t size, uint8_t cmd)
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
inline uint8_t SpiSdCard::RecvData(uint8_t *rxData, uint16_t size)
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
uint8_t SpiSdCard::SdCardInit()
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
int SpiSdCard::GetOCR(uint8_t* ocrData)
{
    uint8_t    res = WriteCmd(_ReadOCR, 0, 0x01);

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
int SpiSdCard::GetCID(uint8_t* cidData)
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
int SpiSdCard::GetCSD(uint8_t* csdData)
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
uint32_t SpiSdCard::GetSectorCount()
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
int SpiSdCard::Sync()
{
    uint8_t res = 1;
    csGpio.Clear();
    if (0 == WaitReady()) res = 0;
    csGpio.Set();
    return res;
}


/// @brief Sd card initialize
/// @return 
bool SpiSdCard::Open()
{
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
/// @param blk 
/// @return 
int SpiSdCard::Write(uint8_t *txData, uint32_t blkSize, uint32_t blk)
{
    uint8_t  res = 0;
    uint32_t sector = blk;

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

    return (res == _ResponseNoErr) ? blkSize : 0;
}


/// @brief Spi sd card read data
/// @param rxData 
/// @param blkSize 
/// @param blk 
/// @return 
int SpiSdCard::Read(uint8_t* rxData, uint32_t blkSize, uint32_t blk)
{
    uint8_t  res = 0;
    uint32_t sector = blk;

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

    return (res == _ResponseNoErr) ? blkSize : 0;
}


/// @brief Spi sd card io ctrl
/// @param cmd 
/// @param data 
/// @return 
int SpiSdCard::IOCtrl(uint8_t cmd, void* data)
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
void SpiSdCard::Close()
{

}


/// @brief Probe
/// @param device 
/// @return 
bool SpiSdCardDrv::Probe(PlatDevice* device)
{
    device->Attach(new SpiSdCard());
    kernel->device.RegisterBlockDevice((BlockDriver*)device->GetDriver());
    return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool SpiSdCardDrv::Remove(PlatDevice* device)
{
    kernel->device.UnregisterBlockDevice((BlockDriver*)device->GetDriver());
    delete (SpiSdCard*)device->GetDriver();
    device->Detach();
    return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new SpiSdCardDrv(), spiSdCard, spiSdCardDrv);
