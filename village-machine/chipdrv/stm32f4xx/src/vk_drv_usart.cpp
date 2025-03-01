//###########################################################################
// vk_drv_usart.cpp
// Hardware layer class that manages a USART/Serial module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_usart.h"


/// @brief Constructor
Usart::Usart()
    : UARTx(NULL),
    channel(_Usart1)
{
}


/// @brief Initializes the serial module
/// @param channel 
void Usart::Initialize(Channel channel)
{
    //Get uart channel
    this->channel = channel;

    //Assign the UARTx pointer and enable the peripheral clock
    if (_Usart1 == channel)
    {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
        UARTx = USART1;
    }
    else if (_Usart2 == channel)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
        UARTx = USART2;
    }
    else if (_Usart3 == channel)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
        UARTx = USART3;
    }

    //Enable Receiver and Transmitter
    LL_USART_SetTransferDirection(UARTx, LL_USART_DIRECTION_TX_RX);
    LL_USART_Enable(UARTx);
}


/// @brief Configures basic port settings
/// @param dataBits 
/// @param parity 
/// @param stopBits 
void Usart::ConfigPortSettings(DataBits dataBits, Parity parity, StopBits stopBits)
{
    //Configure word size
    LL_USART_SetDataWidth(UARTx, dataBits);

    //Configure parity
    LL_USART_SetParity(UARTx, parity);

    //Configure stop bits
    LL_USART_SetStopBitsLength(UARTx, stopBits);
}


/// @brief Sets the baud rate of the serial bus
/// @param baudRate 
/// @param over8 
void Usart::SetBaudRate(uint32_t baudRate, bool over8)
{
    //Calculate the pclk1 frequency
    uint32_t PCLKFreq = 0;

    if (_Usart1 == channel || 6 == channel)
    {
        PCLKFreq = SystemCoreClock >> (APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos]);
    }
    else
    {
        PCLKFreq = SystemCoreClock >> (APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos]);
    }

    //Set baud rate
    if (over8)
    {
        LL_USART_SetOverSampling(UARTx, LL_USART_OVERSAMPLING_8);
        UARTx->BRR = (PCLKFreq * 2 + baudRate / 2) / baudRate;
    }
    else
    {
        LL_USART_SetOverSampling(UARTx, LL_USART_OVERSAMPLING_16);
        UARTx->BRR = (PCLKFreq + baudRate / 2) / baudRate;
    }
}


/// @brief Configure RS485 driver enable mode
/// @param usingDEM 
/// @param polarity 
void Usart::ConfigDriverEnableMode(bool usingDEM, bool polarity)
{
    //Unsupported
}


/// @brief Configure receiver timeout
/// @param enable 
/// @param rto 
/// @param blen 
void Usart::ConfigReceiverTimeout(bool enable, uint32_t rto, uint8_t blen)
{
    //Unsupported
}


/// @brief Enables or disables DMA transmitter / DMA receiver
/// @param dmaTxEnable 
/// @param dmaRxEnable 
void Usart::ConfigDma(bool dmaTxEnable, bool dmaRxEnable)
{
    if (dmaTxEnable)
        LL_USART_EnableDMAReq_TX(UARTx);
    else
        LL_USART_DisableDMAReq_TX(UARTx);

    if (dmaRxEnable)
        LL_USART_EnableDMAReq_RX(UARTx);
    else
        LL_USART_DisableDMAReq_RX(UARTx);
}


/// @brief Write data to usart
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int Usart::Write(uint8_t* data, uint32_t size, uint32_t offset)
{
    uint16_t loop = size;

    data += offset;

    while (loop)
    {
        if (IsTxRegisterEmpty())
        {
            LL_USART_TransmitData8(UARTx, *data++);
            loop--;
        }
    }

    return size;
}


/// @brief Read data from usart
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int Usart::Read(uint8_t* data, uint32_t size, uint32_t offset)
{
    uint32_t length = 0;

    data += offset;

    while (IsReadDataRegNotEmpty())
    {
        *data++ = LL_USART_ReceiveData8(UARTx);
        if (++length >= size) break;
    }

    return length;
}


/// @brief Check error
void Usart::CheckError()
{
    if (LL_USART_IsActiveFlag_PE(UARTx) || LL_USART_IsActiveFlag_FE(UARTx) ||
        LL_USART_IsActiveFlag_NE(UARTx) || LL_USART_IsActiveFlag_ORE(UARTx))
    {
        LL_USART_ClearFlag_PE(UARTx);
        LL_USART_ClearFlag_FE(UARTx);
        LL_USART_ClearFlag_NE(UARTx);
        LL_USART_ClearFlag_ORE(UARTx);
    }
}
