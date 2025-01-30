//###########################################################################
// vk_drv_spi.h
// Hardware Layer class that manages a single SPI module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_SPI_H__
#define __VK_DRV_SPI_H__

#include "vk_hardware.h"
#include "vk_drv_gpio.h"


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
		_Spi4 = 4,
		_Spi5 = 5,
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
		_Fpclk2   = 0b000,  //SPI clock = Fpclk / 2
		_Fpclk4   = 0b001,  //SPI clock = Fpclk / 4
		_Fpclk8   = 0b010,  //SPI clock = Fpclk / 8
		_Fpclk16  = 0b011,  //SPI clock = Fpclk / 16
		_Fpclk32  = 0b100,  //SPI clock = Fpclk / 32
		_Fpclk64  = 0b101,  //SPI clock = Fpclk / 64
		_Fpclk128 = 0b110,  //SPI clock = Fpclk / 128
		_Fpclk256 = 0b111,  //SPI clock = Fpclk / 256
	};

	enum MasterSel
	{
		_Slave  = 0,
		_Master = 1,
	};

	enum CommMode
	{
		_FullDuplex = 0,
		_SimplexTransmitter = 1,
		_SimplexReceiver = 2,
		_salfDuplex = 3,
	};

	enum DataSize
	{
		_4Bit  = 0b0011,
		_5Bit  = 0b0100,
		_6Bit  = 0b0101,
		_7Bit  = 0b0110,
		_8Bit  = 0b0111,
		_9Bit  = 0b1000,
		_10Bit = 0b1001,
		_11Bit = 0b1010,
		_12Bit = 0b1011,
		_13Bit = 0b1100,
		_14Bit = 0b1101,
		_15Bit = 0b1110,
		_16Bit = 0b1111,
	};

	enum RxFifoThres
	{
		_2Byte = 0,
		_1Byte = 1,
	};

	enum LsbFirst
	{
		_MsbFirst = 0,
		_LsbFirst = 1,
	};

	enum FrameFormat
	{
		_MotorolaMode = 0,
		_TiMode       = 1,
	};
private:
	//Static constant
	static const uint32_t timeout_cnt = 500000;

	//Members
	volatile SPI_TypeDef *base;
	volatile uint32_t txReg;
	volatile uint32_t rxReg;

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
	void ConfigCommMode(CommMode commMode);
	void ConfigCrc(bool isEnableCrc);
	void ConfigFrameFormat(FrameFormat frf);
	void ConfigFifoRecThreshold(RxFifoThres status);
	void ConfigDma(bool isEnableTxDma, bool isEnableRxDma);
	uint8_t WriteAndReadOneByte(uint8_t txData);
	uint16_t WriteAndReadTwoByte(uint16_t txData);

	///Enable spi
	inline void Enable() { base->CR1 |= SPI_CR1_SPE; }
	
	///Disable spi
	inline void Disable() { base->CR1 &= ~SPI_CR1_SPE; }

	///Write one byte data
	inline void WriteOneByte(uint8_t txData) { *(__IO uint8_t *)txReg = txData; }
	
	///Read one byte data
	inline uint8_t ReadOneByte() { return *(__IO uint8_t *)rxReg; }

	///Write two byte data
	inline void WriteTwoByte(uint8_t txData) { *(__IO uint16_t *)txReg = txData; }

	///Read two byte data
	inline uint16_t ReadTwoByte() { return *(__IO uint16_t *)rxReg; }
};

#endif // !__VK_DRV_SPI_H__
