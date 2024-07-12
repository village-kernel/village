//###########################################################################
// stm32h7xx_drv_spi.h
// Hardware Layer class that manages a single SPI module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stm32h7xx_drv_spi.h"


///Constructor
Spi::Spi()
	: base(NULL)
{
}


///Initializes the internal members for the SPI object.
///does not actually perform any configuration
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

	//Get the tx and rx register pointer
	txReg = (uint32_t)&(base->TXDR);
	rxReg = (uint32_t)&(base->RXDR);
}


///Performs basic configuration, selects Master/Slave mode
///Selects CPOL and CPHA values.
///Configures GPIO pins for SPI use
void Spi::ConfigModeAndPins(MasterSel MasterSelection, Mode cpolCphaMode, PinConfig pinConfig)
{
	Gpio misoPin;
	Gpio mosiPin;
	Gpio sckPin;

	sckPin.Initialize(pinConfig.sckCh, pinConfig.sckPin);
	sckPin.ConfigMode(Gpio::_Alt);
	sckPin.ConfigAltFunc(pinConfig.sckAltNum);
	sckPin.ConfigSpeed(Gpio::_HighSpeed);

	mosiPin.Initialize(pinConfig.mosiCh, pinConfig.mosiPin);
	mosiPin.ConfigMode(Gpio::_Alt);
	mosiPin.ConfigAltFunc(pinConfig.mosiAltNum);
	mosiPin.ConfigSpeed(Gpio::_HighSpeed);

	misoPin.Initialize(pinConfig.misoCh, pinConfig.misoPin);
	misoPin.ConfigMode(Gpio::_Alt);
	misoPin.ConfigAltFunc(pinConfig.misoAltNum);
	misoPin.ConfigSpeed(Gpio::_HighSpeed);

	if (_Master == MasterSelection)
	{
		misoPin.ConfigOutputType(Gpio::_PushPull);
		mosiPin.ConfigOutputType(Gpio::_PushPull);
		sckPin.ConfigOutputType(Gpio::_PushPull);

		misoPin.ConfigInputType(Gpio::_PullUp);
		mosiPin.ConfigInputType(Gpio::_PullUp);
		sckPin.ConfigInputType(Gpio::_PullUp);

		//Enable software slave management
		base->CFG2 = (base->CFG2 & ~(SPI_CFG2_SSOM_Msk)) | SPI_CFG2_SSOM;

		//Enable software slave management
		base->CFG2 = (base->CFG2 & ~(SPI_CFG2_SSM_Msk)) | SPI_CFG2_SSM;

		//SET SSI bit
		base->CR1 = (base->CR1 & ~(SPI_CR1_SSI_Msk)) | SPI_CR1_SSI;
	}
	else
	{
		misoPin.ConfigOutputType(Gpio::_PushPull);
		mosiPin.ConfigInputType(Gpio::_PullUp);
		sckPin.ConfigInputType(Gpio::_NoPull);

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


///Configures the frame size and order (LSB or MSB first)
void Spi::ConfigFrame(LsbFirst lsbfirst, DataSize datasize)
{
	if (LsbFirst::_LsbFirst == lsbfirst)
		base->CFG2 |= SPI_CFG2_LSBFRST;
	else
		base->CFG2 &= ~SPI_CFG2_LSBFRST;

	base->CFG1 = (base->CFG1 & ~SPI_CFG1_DSIZE) | (datasize << SPI_CFG1_DSIZE_Pos);
	
	base->CR2 = (base->CR2 & ~SPI_CR2_TSIZE) | (1 << SPI_CR2_TSIZE_Pos);
}


///Sets the baud rate of sclk during master mode
///The baud rate of SPI2 SPI3 is based on APP1
///The baud rate of SPI1 SPI4 is based on APP2
void Spi::ConfigBaudRatePrescaler(BaudRate baud_rate)
{
	base->CFG1 = (base->CFG1 & ~SPI_CFG1_MBR_Msk) | (baud_rate << SPI_CFG1_MBR_Pos);
}


///Config 1-line or 2-line unidirectional data mode selected
void Spi::ConfigCommMode(CommMode commMode)
{
	base->CFG2 = (base->CFG2 & ~(SPI_CFG2_COMM_Msk)) | (commMode << SPI_CFG2_COMM_Pos);
}


///Enable or disable hardware CRC calculation
void Spi::ConfigCrc(bool isEnableCrc)
{
	base->CFG1 = (base->CFG1 & ~(SPI_CFG1_CRCEN_Msk)) | (isEnableCrc << SPI_CFG1_CRCEN_Pos);
}


///Configure the frame format to Motorola or TI mode
void Spi::ConfigFrameFormat(FrameFormat frf)
{
	base->CFG2 = (base->CFG2 & ~(SPI_CFG2_SP_Msk)) | (frf << SPI_CFG2_SP_Pos);
}


///Configures the threshold of the RXFIFO that triggers an RXNE event
void Spi::ConfigFifoRecThreshold(RxFifoThres SpiRxThresthreshold)
{
	base->CFG1 = (base->CFG1 & ~(SPI_CFG1_FTHLV_Msk)) | (SpiRxThresthreshold << SPI_CFG1_FTHLV_Pos);
}


///Enable or disable the DMA function for SPI
void Spi::ConfigDma(bool isEnableTxDma, bool isEnableRxDma)
{
	base->CFG1 = (base->CFG1 & (~SPI_CFG1_TXDMAEN)) | (isEnableTxDma << SPI_CFG1_TXDMAEN_Pos);
	base->CFG1 = (base->CFG1 & (~SPI_CFG1_RXDMAEN)) | (isEnableRxDma << SPI_CFG1_RXDMAEN_Pos);
}


///Wait for tx reg empty
inline bool Spi::WaitForTxEmpty()
{
	volatile uint32_t counter = 0;

	while ((base->SR & SPI_SR_TXP) != SPI_SR_TXP)
	{
		if (++counter >= timeout_cnt) return false;
	}

	return true;
}


///Wait for rx reg not empty
inline bool Spi::WaitForRxNotEmpty()
{
	volatile uint32_t counter = 0;

	while (!(base->SR & (SPI_SR_RXWNE | SPI_SR_RXPLVL)))
	{
		if (++counter >= timeout_cnt) return false;
	}

	return true;
}


///Wait for tx completed
inline bool Spi::WaitForTxCompleted()
{
	volatile uint32_t counter = 0;

	while ((base->SR & SPI_SR_EOT) != SPI_SR_EOT)
	{
		if (++counter >= timeout_cnt) return false;
	}

	return true;
}


///Send one byte data and receive one byte data 
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


///Send two bytes data and receive two bytes data 
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
