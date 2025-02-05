//###########################################################################
// vk_drv_usart.cpp
// Hardware layer class that manages a USART/Serial module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_usart.h"

/// @brief Constructor
Usart::Usart()
    : UARTx(NULL)
{
}


/// @brief Initializes the serial module
/// @param channel 
void Usart::Initialize(Channel channel)
{
    //Enable the peripheral clock and assign the UARTx pointer
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
    else if (_Usart4 == channel)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
        UARTx = UART4;
    }
    else if (_Usart5 == channel)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
        UARTx = UART5;
    }

    //Enable FIFO mode
    LL_USART_EnableFIFO(UARTx);

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
	if (0 != baudRate)
	{
		//Calculate the pclk1 frequency
		uint32_t tmp = (D1CorePrescTable[(RCC->D2CFGR & RCC_D2CFGR_D2PPRE1) >> RCC_D2CFGR_D2PPRE1_Pos]) & 0x1FU;
		uint32_t PCLK1Freq = SystemD2Clock >> tmp;

		//Calculate the baudrate of 8x Oversampling
		if (over8)
		{
			UARTx->CR1 |= USART_CR1_OVER8;
			UARTx->BRR = (PCLK1Freq * 2 + baudRate / 2) / baudRate;
		}
		//Calculate the baudrate of 16x Oversampling 
		else
		{
			UARTx->CR1 &= ~USART_CR1_OVER8;
			UARTx->BRR = (PCLK1Freq + baudRate / 2) / baudRate;
		}
	}
	else
	{
		//Measurement of the start bit is used to detect the baud rate
		UARTx->CR2 = (UARTx->CR2 & ~USART_CR2_ABRMODE_Msk);

		//Auto baud rate enable
		UARTx->CR2 |= USART_CR2_ABREN;
	}
}


/// @brief Configure RS485 driver enable mode
/// @param usingDEM 
/// @param polarity 
void Usart::ConfigDriverEnableMode(bool usingDEM, bool polarity)
{
    if (usingDEM)
        LL_USART_EnableDEMode(UARTx);
    else
        LL_USART_DisableDEMode(UARTx);

    LL_USART_SetDESignalPolarity(UARTx, polarity ? LL_USART_DE_POLARITY_HIGH : LL_USART_DE_POLARITY_LOW);
}


/// @brief Configure receiver timeout
/// @param enable 
/// @param rto 
/// @param blen 
void Usart::ConfigReceiverTimeout(bool enable, uint32_t rto, uint8_t blen)
{
    if (enable)
        LL_USART_EnableRxTimeout(UARTx);
    else
        LL_USART_DisableRxTimeout(UARTx);
        
    LL_USART_SetRxTimeout(UARTx, rto);
    LL_USART_SetBlockLength(UARTx, blen);
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
