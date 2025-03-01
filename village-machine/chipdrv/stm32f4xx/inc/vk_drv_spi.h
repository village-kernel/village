//###########################################################################
// vk_drv_spi.h
// Hardware Layer class that manages a single SPI module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_SPI_H__
#define __VK_DRV_SPI_H__

#include "stm32f4xx_ll_spi.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"

/// @brief Spi
class Spi
{
public:
    //Enumerations
    enum Channel
    {
        _Spi1 = 0,
        _Spi2 = 1,
        _Spi3 = 2,
    };

	enum Mode
	{
		_Cpol0Cpha0 = 0b00,
		_Cpol0Cpha1 = 0b01,
		_Cpol1Cpha0 = 0b10,
		_Cpol1Cpha1 = 0b11,
	};

    enum BaudRate
    {
        _Fpclk2   = LL_SPI_BAUDRATEPRESCALER_DIV2,
        _Fpclk4   = LL_SPI_BAUDRATEPRESCALER_DIV4,
        _Fpclk8   = LL_SPI_BAUDRATEPRESCALER_DIV8,
        _Fpclk16  = LL_SPI_BAUDRATEPRESCALER_DIV16,
        _Fpclk32  = LL_SPI_BAUDRATEPRESCALER_DIV32,
        _Fpclk64  = LL_SPI_BAUDRATEPRESCALER_DIV64,
        _Fpclk128 = LL_SPI_BAUDRATEPRESCALER_DIV128,
        _Fpclk256 = LL_SPI_BAUDRATEPRESCALER_DIV256,
    };

    enum MasterSel
    {
        _Slave  = LL_SPI_MODE_SLAVE,
        _Master = LL_SPI_MODE_MASTER,
    };

    enum DataSize
    {
        _8Bit  = LL_SPI_DATAWIDTH_8BIT,
        _16Bit = LL_SPI_DATAWIDTH_16BIT,
    };

    enum LsbFirst
    {
        _MsbFirst = SPI_FIRSTBIT_MSB,
        _LsbFirst = SPI_FIRSTBIT_LSB,
    };
private:
    //Static constant
    static const uint32_t timeout_cnt = 500000;

    //Members
    SPI_TypeDef *SPIx;

    //Methods
    bool WaitForTxEmpty();
    bool WaitForRxNotEmpty();
    bool WaitForTxCompleted();
public:
    //Methods
    Spi();
    void Initialize(Channel channel);
    void ConfigModeAndPins(MasterSel MasterSelection, Mode cpolCphaMode);
    void ConfigFrame(LsbFirst lsbfirst, DataSize datasize);
    void ConfigBaudRatePrescaler(BaudRate baud_rate);
    uint8_t WriteAndReadOneByte(uint8_t txData);
    uint16_t WriteAndReadTwoByte(uint16_t txData);

    ///Enable spi
    inline void Enable() { LL_SPI_Enable(SPIx); }
    
    ///Disable spi
    inline void Disable() { LL_SPI_Disable(SPIx); }

    ///Write one byte data
    inline void WriteOneByte(uint8_t txData) { LL_SPI_TransmitData8(SPIx, txData); }
    
    ///Read one byte data
    inline uint8_t ReadOneByte() { return LL_SPI_ReceiveData8(SPIx); }

    ///Write two byte data
    inline void WriteTwoByte(uint16_t txData) { LL_SPI_TransmitData16(SPIx, txData); }

    ///Read two byte data
    inline uint16_t ReadTwoByte() { return LL_SPI_ReceiveData16(SPIx); }
};

#endif // !__VK_DRV_SPI_H__
