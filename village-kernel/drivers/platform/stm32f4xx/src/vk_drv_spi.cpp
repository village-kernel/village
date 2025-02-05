//###########################################################################
// vk_drv_spi.cpp
// Hardware Layer class that manages a single SPI module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_spi.h"


/// @brief Constructor
Spi::Spi()
    : SPIx(NULL)
{
}


/// @brief Initializes the internal members for the SPI object.
///        does not actually perform any configuration
/// @param channel 
void Spi::Initialize(Channel channel)
{
    //Enable clock
    if (_Spi1 == channel)
    {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
        SPIx = SPI1;
    }
    else if(_Spi2 == channel)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
        SPIx = SPI2;
    }
    else if (_Spi3 == channel)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
        SPIx = SPI3;
    }
}


/// @brief Performs basic configuration, selects Master/Slave mode
///        Selects CPOL and CPHA values.
///        Configures GPIO pins for SPI use
/// @param MasterSelection 
/// @param cpolCphaMode 
void Spi::ConfigModeAndPins(MasterSel MasterSelection, Mode cpolCphaMode)
{
    // Set master/slave mode
    LL_SPI_SetMode(SPIx, MasterSelection);

    // Set CPOL and CPHA
    LL_SPI_SetClockPolarity(SPIx, (cpolCphaMode & 0x02) ? LL_SPI_POLARITY_HIGH : LL_SPI_POLARITY_LOW);
    LL_SPI_SetClockPhase(SPIx, (cpolCphaMode & 0x01) ? LL_SPI_PHASE_2EDGE : LL_SPI_PHASE_1EDGE);

    // Enable software slave management for master mode
    if (MasterSelection == _Master)
    {
        LL_SPI_SetNSSMode(SPIx, LL_SPI_NSS_SOFT);
        //LL_SPI_SetInternalSSLevel(SPIx, LL_SPI_SS_ACTIVE_LOW);
    }
}


/// @brief Configures the frame size and order (LSB or MSB first)
/// @param lsbfirst 
/// @param datasize 
void Spi::ConfigFrame(LsbFirst lsbfirst, DataSize datasize)
{
    LL_SPI_SetDataWidth(SPIx, datasize);
    LL_SPI_SetTransferBitOrder(SPIx, lsbfirst);
}


/// @brief Sets the baud rate of sclk during master mode
/// @param baud_rate 
void Spi::ConfigBaudRatePrescaler(BaudRate baud_rate)
{
    LL_SPI_SetBaudRatePrescaler(SPIx, baud_rate);
}


/// @brief Wait for tx reg empty
/// @return 
inline bool Spi::WaitForTxEmpty()
{
    volatile uint32_t counter = 0;

    while (!LL_SPI_IsActiveFlag_TXE(SPIx))
    {
        if (++counter >= timeout_cnt) return false;
    }

    return true;
}


/// @brief Wait for rx reg not empty
/// @return 
inline bool Spi::WaitForRxNotEmpty()
{
    volatile uint32_t counter = 0;

    while (!LL_SPI_IsActiveFlag_RXNE(SPIx))
    {
        if (++counter >= timeout_cnt) return false;
    }

    return true;
}


/// @brief Wait for tx completed
/// @return 
inline bool Spi::WaitForTxCompleted()
{
    volatile uint32_t counter = 0;

    while (LL_SPI_IsActiveFlag_BSY(SPIx))
    {
        if (++counter >= timeout_cnt) return false;
    }

    return true;
}


/// @brief Send one byte data and receive one byte data 
/// @param txData 
/// @return 
uint8_t Spi::WriteAndReadOneByte(uint8_t txData)
{
    //Start transfer
    LL_SPI_SetMode(SPIx, LL_SPI_MODE_MASTER);

    //Send one byte
    if (!WaitForTxEmpty()) return 0xff;
    WriteOneByte(txData);

    //Get one byte
    if (!WaitForRxNotEmpty()) return 0xff;
    uint8_t byte = ReadOneByte();

    //Wait for transfer completed
    if (!WaitForTxCompleted()) return 0xff;

    return byte;
}


/// @brief Send two bytes data and receive two bytes data 
/// @param txData 
/// @return 
uint16_t Spi::WriteAndReadTwoByte(uint16_t txData)
{
    //Start transfer
    LL_SPI_SetMode(SPIx, LL_SPI_MODE_MASTER);

    //Send one byte
    if (!WaitForTxEmpty()) return 0xff;
    WriteTwoByte(txData);

    if (!WaitForRxNotEmpty()) return 0xff;
    uint16_t word = ReadTwoByte();

    //Wait for transfer completed
    if (!WaitForTxCompleted()) return 0xff;

    return word;
}
