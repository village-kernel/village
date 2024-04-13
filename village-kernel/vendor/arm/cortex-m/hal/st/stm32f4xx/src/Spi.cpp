//###########################################################################
// Spi.h
// Hardware Layer class that manages a single SPI module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Spi.h"


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
		base->CR1 = (base->CR1 & ~(SPI_CR1_SSM_Msk)) | SPI_CR1_SSM;

		//SET SSI bit
		base->CR1 = (base->CR1 & ~(SPI_CR1_SSI_Msk)) | SPI_CR1_SSI;
	}
	else
	{
		misoPin.ConfigOutputType(Gpio::_PushPull);
		mosiPin.ConfigInputType(Gpio::_PullUp);
		sckPin.ConfigInputType(Gpio::_NoPull);

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


///Configures the frame size and order (LSB or MSB first)
void Spi::ConfigFrame(LsbFirst lsbfirst, DataSize datasize)
{
	if (LsbFirst::_LsbFirst == lsbfirst)
		base->CR1 |= SPI_CR1_LSBFIRST;
	else
		base->CR1 &= ~SPI_CR1_LSBFIRST;

	base->CR1 = (base->CR1 & ~SPI_CR1_DFF_Msk) | (datasize << SPI_CR1_DFF_Pos);
}


///Sets the baud rate of sclk during master mode
///The baud rate of SPI2 SPI3 is based on APP1
///The baud rate of SPI1 SPI4 is based on APP2
void Spi::ConfigBaudRatePrescaler(BaudRate baud_rate)
{
	base->CR1 = (base->CR1 & ~SPI_CR1_BR_Msk) | (baud_rate << SPI_CR1_BR_Pos);
}


///Config 1-line or 2-line unidirectional data mode selected
void Spi::ConfigBitMode(SpiBitMode bitmode)
{
	base->CR1 = (base->CR1 & ~(SPI_CR1_BIDIMODE_Msk)) | (bitmode << SPI_CR1_BIDIMODE_Pos);
}


///Enable or disable hardware CRC calculation
void Spi::ConfigCrc(bool isEnableCrc)
{
	base->CR1 = (base->CR1 & ~(SPI_CR1_CRCEN_Msk)) | (isEnableCrc << SPI_CR1_CRCEN_Pos);
}


///Configure the frame format to Motorola or TI mode
void Spi::ConfigFrameFormat(FrameFormat frf)
{
	base->CR2 = (base->CR2 & ~(SPI_CR2_FRF_Msk)) | (frf << SPI_CR2_FRF_Pos);
}


///Configures the threshold of the RXFIFO that triggers an RXNE event
void Spi::ConfigFifoRecThreshold(RxFifoThres SpiRxThresthreshold)
{
	//STM32F4xx not support this function
}


///Enable or disable the DMA function for SPI
void Spi::ConfigDma(bool isEnableTxDma, bool isEnableRxDma)
{
	base->CR2 = (base->CR2 & (~SPI_CR2_TXDMAEN)) | (isEnableTxDma << SPI_CR2_TXDMAEN_Pos);
	base->CR2 = (base->CR2 & (~SPI_CR2_RXDMAEN)) | (isEnableRxDma << SPI_CR2_RXDMAEN_Pos);
}


///Wait for tx reg empty
inline bool Spi::WaitForTxEmpty()
{
	volatile uint32_t counter = 0;

	while ((base->SR & SPI_SR_TXE) != SPI_SR_TXE)
	{
		if (++counter >= timeout_cnt) return false;
	}

	return true;
}


///Wait for rx reg not empty
inline bool Spi::WaitForRxNotEmpty()
{
	volatile uint32_t counter = 0;

	while ((base->SR & SPI_SR_RXNE) != SPI_SR_RXNE)
	{
		if (++counter >= timeout_cnt) return false;
	}

	return true;
}


///Wait for tx completed
inline bool Spi::WaitForTxCompleted()
{
	volatile uint32_t counter = 0;

	while (base->SR & SPI_SR_BSY)
	{
		if (++counter >= timeout_cnt) return false;
	}

	return true;
}


///Send one byte data and receive one byte data 
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


///Send two bytes data and receive two bytes data 
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
