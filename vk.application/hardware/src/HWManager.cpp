//###########################################################################
// HWManager.cpp
// Definitions of the functions that manage hardware device
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "HWManager.h"
#include "HwConfig.h"
#include "Kernel.h"


///Initialize the singleton instance of HWManager
HWManager HWManager::instance;


///Initialize the fatfs flash and sd card
SpiFlash* fatfsFlash = &(HWManager::Instance()->spiFlash);
SdCard* fatfsSdCard = &(HWManager::Instance()->sdcard);


///Constructor
HWManager::HWManager()
{
}


///Hardware initialize
void HWManager::Initialize()
{
	SerialInitialize();
	ILI9488Initialize();
	FlashInitialize();
	SdCardInitialize();
	UsbInitialize();
}


///Hardware update params
void HWManager::UpdateParams()
{

}


///Hardware fail safe
void HWManager::FailSafe(int arg)
{

}


///Initialize serial
inline void HWManager::SerialInitialize()
{
	UartSerial::Config config;

	//Config uart serial
	config.usartCh = UART_SERIAL_CHANNEL;
	config.usartBaudrate = UART_SERIAL_BAUD_RATE;

	//Config uart rx pin
	config.usartRxPin.ch = UART_SERIAL_RX_CH;
	config.usartRxPin.pin = UART_SERIAL_RX_PIN;
	config.usartRxPin.alt = UART_SERIAL_RX_AF_NUM;

	//Config uart tx pin
	config.usartTxPin.ch = UART_SERIAL_TX_CH;
	config.usartTxPin.pin = UART_SERIAL_TX_PIN;
	config.usartTxPin.alt = UART_SERIAL_TX_AF_NUM;

	//Config uart rx dma
	config.usartRxDmaGroup = UART_SERIAL_RX_DMA_GROUP;
	config.usartRxDmaCh = UART_SERIAL_RX_DMA_CHANNEL;
	config.usartRxDmaReq = UART_SERIAL_RX_DMA_REQUEST;

	//Config uart tx dma
	config.usartTxDmaGroup = UART_SERIAL_TX_DMA_GROUP;
	config.usartTxDmaCh = UART_SERIAL_TX_DMA_CHANNEL;
	config.usartTxDmaReq = UART_SERIAL_TX_DMA_REQUEST;

	//Initialize uart serial
	uartSerial.Initialize(config);
}


///Initialize ILI9488
inline void HWManager::ILI9488Initialize()
{
	ILI9488::Config config;
	
	config.backLightCh = LCD_BACK_LIGHT_CH;
	config.backLightPin = LCD_BACK_LIGHT_PIN;

	config.fsmcConfig.csCh = LCD_CS_CH;
	config.fsmcConfig.csPin = LCD_CS_PIN;
	config.fsmcConfig.rsCh = LCD_RS_CH;
	config.fsmcConfig.rsPin = LCD_RS_PIN;
	config.fsmcConfig.wrCh = LCD_WR_CH;
	config.fsmcConfig.wrPin = LCD_WR_PIN;
	config.fsmcConfig.rdCh = LCD_RD_CH;
	config.fsmcConfig.rdPin = LCD_RD_PIN;

	config.fsmcConfig.db0Ch = LCD_DB0_CH;
	config.fsmcConfig.db0Pin = LCD_DB0_PIN;
	config.fsmcConfig.db1Ch = LCD_DB1_CH;
	config.fsmcConfig.db1Pin = LCD_DB1_PIN;
	config.fsmcConfig.db2Ch = LCD_DB2_CH;
	config.fsmcConfig.db2Pin = LCD_DB2_PIN;
	config.fsmcConfig.db3Ch = LCD_DB3_CH;
	config.fsmcConfig.db3Pin = LCD_DB3_PIN;
	config.fsmcConfig.db4Ch = LCD_DB4_CH;
	config.fsmcConfig.db4Pin = LCD_DB4_PIN;
	config.fsmcConfig.db5Ch = LCD_DB5_CH;
	config.fsmcConfig.db5Pin = LCD_DB5_PIN;
	config.fsmcConfig.db6Ch = LCD_DB6_CH;
	config.fsmcConfig.db6Pin = LCD_DB6_PIN;
	config.fsmcConfig.db7Ch = LCD_DB7_CH;
	config.fsmcConfig.db7Pin = LCD_DB7_PIN;
	config.fsmcConfig.db8Ch = LCD_DB8_CH;
	config.fsmcConfig.db8Pin = LCD_DB8_PIN;
	config.fsmcConfig.db9Ch = LCD_DB9_CH;
	config.fsmcConfig.db9Pin = LCD_DB9_PIN;
	config.fsmcConfig.db10Ch = LCD_DB10_CH;
	config.fsmcConfig.db10Pin = LCD_DB10_PIN;
	config.fsmcConfig.db11Ch = LCD_DB11_CH;
	config.fsmcConfig.db11Pin = LCD_DB11_PIN;
	config.fsmcConfig.db12Ch = LCD_DB12_CH;
	config.fsmcConfig.db12Pin = LCD_DB12_PIN;
	config.fsmcConfig.db13Ch = LCD_DB13_CH;
	config.fsmcConfig.db13Pin = LCD_DB13_PIN;
	config.fsmcConfig.db14Ch = LCD_DB14_CH;
	config.fsmcConfig.db14Pin = LCD_DB14_PIN;
	config.fsmcConfig.db15Ch = LCD_DB15_CH;
	config.fsmcConfig.db15Pin = LCD_DB15_PIN;

	ili9488.Initialize(config);
}


///Initialize flash
inline void HWManager::FlashInitialize()
{
	//Config spi flash
	SpiFlash::Config config;
	config.SpiCh = SPI_FLASH_CHANNEL;
	config.SpiConfig.sckCh = SPI_FLASH_SCK_CH;
	config.SpiConfig.sckPin = SPI_FLASH_SCK_PIN;
	config.SpiConfig.sckAltNum = SPI_FLASH_SCK_AF_NUM;
	config.SpiConfig.misoCh = SPI_FLASH_MISO_CH;
	config.SpiConfig.misoPin = SPI_FLASH_MISO_PIN;
	config.SpiConfig.misoAltNum = SPI_FLAHS_MISO_AF_NUM;
	config.SpiConfig.mosiCh = SPI_FLASH_MOSI_CH;	
	config.SpiConfig.mosiPin = SPI_FLASH_MOSI_PIN;
	config.SpiConfig.mosiAltNum = SPI_FLASH_MOSI_AF_NUM;
	config.flashcsCh = SPI_FLASH_CS_CH;
	config.flashcsPin = SPI_FLASH_CS_PIN;
	config.flashwpCh = SPI_FLASH_WP_CH;
	config.flashwpPin = SPI_FLASH_WP_PIN;

	//Initialize spi flash
	spiFlash.Initialize(config);
}


///Initialize sd card
inline void HWManager::SdCardInitialize()
{
	//Config sd card
	SdCard::Config config;
	config.SpiCh = SPI_SD_CHANNEL;
	config.SpiConfig.sckCh = SPI_SD_SCK_CH;
	config.SpiConfig.sckPin = SPI_SD_SCK_PIN;
	config.SpiConfig.sckAltNum = SPI_SD_SCK_AF_NUM;
	config.SpiConfig.misoCh = SPI_SD_MISO_CH;
	config.SpiConfig.misoPin = SPI_SD_MISO_PIN;
	config.SpiConfig.misoAltNum = SPI_SD_MISO_AF_NUM;
	config.SpiConfig.mosiCh = SPI_SD_MOSI_CH;	
	config.SpiConfig.mosiPin = SPI_SD_MOSI_PIN;
	config.SpiConfig.mosiAltNum = SPI_SD_MOSI_AF_NUM;
	config.sdcsCh = SPI_SD_CS_CH;
	config.sdcsPin = SPI_SD_CS_PIN;
	config.detectCh = SPI_SD_DETECT_CH;
	config.detectPin = SPI_SD_DETECT_PIN;

	//Initialize sd card
	sdcard.Initialize(config);
}


///Initialize usb storage
inline void HWManager::UsbInitialize()
{
	usbStorage.Initialize();
	usbStorage.Mount();
}


///Register module
REGISTER_MODULE(HWManager::Instance(), HARDWARE_ID(0), hardware);
