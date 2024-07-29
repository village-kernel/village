//###########################################################################
// stm32f4xx_drv_spi.h
// Hardware Layer class that manages a single SPI module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stm32f4xx_drv_spi.h"


/// @brief Constructor
Spi::Spi()
	: base(NULL)
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
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
		base = SPI1;
	}
	else if(_Spi2 == channel)
	{
		RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
		base = SPI2;
	}
	else if (_Spi3 == channel)
	{
		RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
		base = SPI3;
	}

	//Get the tx and rx register pointer
	txReg = (uint32_t)&(base->DR);
	rxReg = (uint32_t)&(base->DR);
}


/// @brief Performs basic configuration, selects Master/Slave mode
///        Selects CPOL and CPHA values.
///        Configures GPIO pins for SPI use
/// @param MasterSelection 
/// @param cpolCphaMode 
/// @param pinConfig 
void Spi::ConfigModeAndPins(MasterSel MasterSelection, Mode cpolCphaMode)
{
	if (_Master == MasterSelection)
	{
		//Enable software slave management
		base->CR1 = (base->CR1 & ~(SPI_CR1_SSM_Msk)) | SPI_CR1_SSM;

		//SET SSI bit
		base->CR1 = (base->CR1 & ~(SPI_CR1_SSI_Msk)) | SPI_CR1_SSI;
	}
	else
	{
		//Disable software slave management
		base->CR1 = base->CR1 & ~(SPI_CR1_SSM_Msk);
	}

	//Set spi mode
	if (MasterSelection == MasterSel::_Master)
		base->CR1 |= SPI_MODE_MASTER;
	else
		base->CR1 &= ~SPI_MODE_MASTER;

	//Set cpol Cpha mode
	const uint32_t cpol_cpha_msk = SPI_CR1_CPOL | SPI_CR1_CPHA;
	base->CR1 = (base->CR1 & ~cpol_cpha_msk) | (cpolCphaMode << SPI_CR1_CPHA_Pos);
}


/// @brief Configures the frame size and order (LSB or MSB first)
/// @param lsbfirst 
/// @param datasize 
void Spi::ConfigFrame(LsbFirst lsbfirst, DataSize datasize)
{
	if (LsbFirst::_LsbFirst == lsbfirst)
		base->CR1 |= SPI_CR1_LSBFIRST;
	else
		base->CR1 &= ~SPI_CR1_LSBFIRST;

	base->CR1 = (base->CR1 & ~SPI_CR1_DFF_Msk) | (datasize << SPI_CR1_DFF_Pos);
}


/// @brief Sets the baud rate of sclk during master mode
///        The baud rate of SPI2 SPI3 is based on APP1
///        The baud rate of SPI1 SPI4 is based on APP2
/// @param baud_rate 
void Spi::ConfigBaudRatePrescaler(BaudRate baud_rate)
{
	base->CR1 = (base->CR1 & ~SPI_CR1_BR_Msk) | (baud_rate << SPI_CR1_BR_Pos);
}


/// @brief Config 1-line or 2-line unidirectional data mode selected
/// @param bitmode 
void Spi::ConfigBitMode(SpiBitMode bitmode)
{
	base->CR1 = (base->CR1 & ~(SPI_CR1_BIDIMODE_Msk)) | (bitmode << SPI_CR1_BIDIMODE_Pos);
}


/// @brief Enable or disable hardware CRC calculation
/// @param isEnableCrc 
void Spi::ConfigCrc(bool isEnableCrc)
{
	base->CR1 = (base->CR1 & ~(SPI_CR1_CRCEN_Msk)) | (isEnableCrc << SPI_CR1_CRCEN_Pos);
}


/// @brief Configure the frame format to Motorola or TI mode
/// @param frf 
void Spi::ConfigFrameFormat(FrameFormat frf)
{
	base->CR2 = (base->CR2 & ~(SPI_CR2_FRF_Msk)) | (frf << SPI_CR2_FRF_Pos);
}


/// @brief Configures the threshold of the RXFIFO that triggers an RXNE event
/// @param SpiRxThresthreshold 
void Spi::ConfigFifoRecThreshold(RxFifoThres SpiRxThresthreshold)
{
	//STM32F4xx not support this function
}


/// @brief Enable or disable the DMA function for SPI
/// @param isEnableTxDma 
/// @param isEnableRxDma 
void Spi::ConfigDma(bool isEnableTxDma, bool isEnableRxDma)
{
	base->CR2 = (base->CR2 & (~SPI_CR2_TXDMAEN)) | (isEnableTxDma << SPI_CR2_TXDMAEN_Pos);
	base->CR2 = (base->CR2 & (~SPI_CR2_RXDMAEN)) | (isEnableRxDma << SPI_CR2_RXDMAEN_Pos);
}


/// @brief Wait for tx reg empty
/// @return 
inline bool Spi::WaitForTxEmpty()
{
	volatile uint32_t counter = 0;

	while ((base->SR & SPI_SR_TXE) != SPI_SR_TXE)
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

	while ((base->SR & SPI_SR_RXNE) != SPI_SR_RXNE)
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

	while (base->SR & SPI_SR_BSY)
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
	base->CR1 |= SPI_CR1_MSTR;

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
	base->CR1 |= SPI_CR1_MSTR;

	//Send one byte
	if (!WaitForTxEmpty()) return 0xff;
	WriteTwoByte(txData);

	if (!WaitForRxNotEmpty()) return 0xff;
	uint16_t word = ReadTwoByte();

	//Wait for transfer completed
	if (!WaitForTxCompleted()) return 0xff;

	return word;
}
