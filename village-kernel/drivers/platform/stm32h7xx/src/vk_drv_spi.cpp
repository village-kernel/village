//###########################################################################
// vk_drv_spi.h
// Hardware Layer class that manages a single SPI module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_spi.h"


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
		RCC->APB1LENR |= RCC_APB1LENR_SPI2EN;
		base = SPI2;
	}
	else if (_Spi3 == channel)
	{
		RCC->APB1LENR |= RCC_APB1LENR_SPI3EN;
		base = SPI3;
	}
	else if (_Spi4 == channel)
	{
		RCC->APB2ENR |= RCC_APB2ENR_SPI4EN;
		base = SPI4;
	}
		else if (_Spi5 == channel)
	{
		RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;
		base = SPI5;
	}

	//Get the tx and rx register pointer
	txReg = (uint32_t)&(base->TXDR);
	rxReg = (uint32_t)&(base->RXDR);
}


/// @brief Performs basic configuration, selects Master/Slave mode
///        Selects CPOL and CPHA values.
/// @param MasterSelection 
/// @param cpolCphaMode 
void Spi::ConfigModeAndPins(MasterSel MasterSelection, Mode cpolCphaMode)
{
	if (_Master == MasterSelection)
	{
		//Enable software slave management
		base->CFG2 = (base->CFG2 & ~(SPI_CFG2_SSOM_Msk)) | SPI_CFG2_SSOM;

		//Enable software slave management
		base->CFG2 = (base->CFG2 & ~(SPI_CFG2_SSM_Msk)) | SPI_CFG2_SSM;

		//SET SSI bit
		base->CR1 = (base->CR1 & ~(SPI_CR1_SSI_Msk)) | SPI_CR1_SSI;
	}
	else
	{
		//Disable software slave management
		base->CFG2 = base->CFG2 & ~(SPI_CFG2_SSM_Msk);
	}

	//Set spi mode
	if (MasterSelection == MasterSel::_Master)
		base->CFG2 |= SPI_CFG2_MASTER;
	else
		base->CFG2 &= ~SPI_CFG2_MASTER;

	//Set cpol Cpha mode
	const uint32_t cpol_cpha_msk = SPI_CFG2_CPOL | SPI_CFG2_CPHA;
	base->CFG2 = (base->CFG2 & ~cpol_cpha_msk) | (cpolCphaMode << SPI_CFG2_CPHA_Pos);
}


/// @brief Configures the frame size and order (LSB or MSB first)
/// @param lsbfirst 
/// @param datasize 
void Spi::ConfigFrame(LsbFirst lsbfirst, DataSize datasize)
{
	if (LsbFirst::_LsbFirst == lsbfirst)
		base->CFG2 |= SPI_CFG2_LSBFRST;
	else
		base->CFG2 &= ~SPI_CFG2_LSBFRST;

	base->CFG1 = (base->CFG1 & ~SPI_CFG1_DSIZE) | (datasize << SPI_CFG1_DSIZE_Pos);
	
	base->CR2 = (base->CR2 & ~SPI_CR2_TSIZE) | (1 << SPI_CR2_TSIZE_Pos);
}


/// @brief Sets the baud rate of sclk during master mode
///        The baud rate of SPI2 SPI3 is based on APP1
///        The baud rate of SPI1 SPI4 is based on APP2
/// @param baud_rate 
void Spi::ConfigBaudRatePrescaler(BaudRate baud_rate)
{
	base->CFG1 = (base->CFG1 & ~SPI_CFG1_MBR_Msk) | (baud_rate << SPI_CFG1_MBR_Pos);
}


/// @brief Config 1-line or 2-line unidirectional data mode selected
/// @param commMode 
void Spi::ConfigCommMode(CommMode commMode)
{
	base->CFG2 = (base->CFG2 & ~(SPI_CFG2_COMM_Msk)) | (commMode << SPI_CFG2_COMM_Pos);
}


/// @brief Enable or disable hardware CRC calculation
/// @param isEnableCrc 
void Spi::ConfigCrc(bool isEnableCrc)
{
	base->CFG1 = (base->CFG1 & ~(SPI_CFG1_CRCEN_Msk)) | (isEnableCrc << SPI_CFG1_CRCEN_Pos);
}


/// @brief Configure the frame format to Motorola or TI mode
/// @param frf 
void Spi::ConfigFrameFormat(FrameFormat frf)
{
	base->CFG2 = (base->CFG2 & ~(SPI_CFG2_SP_Msk)) | (frf << SPI_CFG2_SP_Pos);
}


/// @brief Configures the threshold of the RXFIFO that triggers an RXNE event
/// @param SpiRxThresthreshold 
void Spi::ConfigFifoRecThreshold(RxFifoThres SpiRxThresthreshold)
{
	base->CFG1 = (base->CFG1 & ~(SPI_CFG1_FTHLV_Msk)) | (SpiRxThresthreshold << SPI_CFG1_FTHLV_Pos);
}


/// @brief Enable or disable the DMA function for SPI
/// @param isEnableTxDma 
/// @param isEnableRxDma 
void Spi::ConfigDma(bool isEnableTxDma, bool isEnableRxDma)
{
	base->CFG1 = (base->CFG1 & (~SPI_CFG1_TXDMAEN)) | (isEnableTxDma << SPI_CFG1_TXDMAEN_Pos);
	base->CFG1 = (base->CFG1 & (~SPI_CFG1_RXDMAEN)) | (isEnableRxDma << SPI_CFG1_RXDMAEN_Pos);
}


/// @brief Wait for tx reg empty
/// @return 
inline bool Spi::WaitForTxEmpty()
{
	volatile uint32_t counter = 0;

	while ((base->SR & SPI_SR_TXP) != SPI_SR_TXP)
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

	while (!(base->SR & (SPI_SR_RXWNE | SPI_SR_RXPLVL)))
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

	while ((base->SR & SPI_SR_EOT) != SPI_SR_EOT)
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
	base->CR1 |= SPI_CR1_CSTART;

	//Send one byte
	if (!WaitForTxEmpty()) return 0xff;
	WriteOneByte(txData);

	//Get one byte
	if (!WaitForRxNotEmpty()) return 0xff;
	uint8_t byte = ReadOneByte();

	//Wait for transfer completed
	if (!WaitForTxCompleted()) return 0xff;
	base->IFCR |= SPI_IFCR_EOTC;
	base->IFCR |= SPI_IFCR_TXTFC;

	return byte;
}


/// @brief Send two bytes data and receive two bytes data 
/// @param txData 
/// @return 
uint16_t Spi::WriteAndReadTwoByte(uint16_t txData)
{
	//Start transfer
	base->CR1 |= SPI_CR1_CSTART;

	//Send one byte
	if (!WaitForTxEmpty()) return 0xff;
	WriteTwoByte(txData);

	if (!WaitForRxNotEmpty()) return 0xff;
	uint16_t word = ReadTwoByte();

	//Wait for transfer completed
	if (!WaitForTxCompleted()) return 0xff;
	base->IFCR |= SPI_IFCR_EOTC;
	base->IFCR |= SPI_IFCR_TXTFC;

	return word;
}
