//###########################################################################
// ILI9488.cpp
//
// $Copyright: Copyright (C)
//###########################################################################
#include "ILI9488.h"
#include "Kernel.h"
#include "HwConfig.h"
#include "System.h"
#include "math.h"


///Constructor
ILI9488::ILI9488()
{
}


///ILI9488 initialize
void ILI9488::Initialize()
{
	InitConfig();

	backLight.Initialize(config.backLightCh, config.backLightPin, Gpio::_Low);

	fsmc.Initialize(config.fsmcConfig);

	System::DelayMs(50);

	DeviceConfig();

	if (device.id == ReadID())
	{
		DisplayConfig();
		Clear();
		BackLightOn();
	}
}


///Init config
void ILI9488::InitConfig()
{
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
}


///Config lcd info
void ILI9488::DeviceConfig()
{
	device.id = 0x548066;
	device.dir = Down;
	device.height = 480;
	device.width = 320;
	device.setXCmd = 0x2A;
	device.setYCmd = 0x2B;
	device.wRamCmd = 0X2C;
	device.rRamCmd = 0x2E;
}


///ILI9488 display config
void ILI9488::DisplayConfig()
{
	// PGAMCTRL (Positive Gamma Control) (E0h)
	WriteCmd(0xE0);
	WriteData(0x00);
	WriteData(0x07);
	WriteData(0x10);
	WriteData(0x09);
	WriteData(0x17);
	WriteData(0x0B);
	WriteData(0x41);
	WriteData(0x89);
	WriteData(0x4B);
	WriteData(0x0A);
	WriteData(0x0C);
	WriteData(0x0E);
	WriteData(0x18);
	WriteData(0x1B);
	WriteData(0x0F);

	// NGAMCTRL (Negative Gamma Control) (E1h)
	WriteCmd(0XE1);
	WriteData(0x00);
	WriteData(0x17);
	WriteData(0x1A);
	WriteData(0x04);
	WriteData(0x0E);
	WriteData(0x06);
	WriteData(0x2F);
	WriteData(0x45);
	WriteData(0x43);
	WriteData(0x02);
	WriteData(0x0A);
	WriteData(0x09);
	WriteData(0x32);
	WriteData(0x36);
	WriteData(0x0F);

	// Adjust Control 3 (F7h)
	WriteCmd(0XF7);
	WriteData(0xA9);
	WriteData(0x51);
	WriteData(0x2C);
	WriteData(0x82);/* DSI write DCS command, use loose packet RGB 666 */

	// Power Control 1 (C0h)
	WriteCmd(0xC0);
	WriteData(0x11);
	WriteData(0x09);

	// Power Control 2 (C1h)
	WriteCmd(0xC1);
	WriteData(0x41);

	// VCOM Control (C5h)
	WriteCmd(0XC5);
	WriteData(0x00);
	WriteData(0x0A);
	WriteData(0x80);

	// Frame Rate Control (In Normal Mode/Full Colors) (B1h)
	WriteCmd(0xB1);
	WriteData(0xB0);
	WriteData(0x11);

	// Display Inversion Control (B4h)
	WriteCmd(0xB4);
	WriteData(0x02);

	// Display Function Control (B6h)
	WriteCmd(0xB6);
	WriteData(0x02);
	WriteData(0x22);

	// Entry Mode Set (B7h)
	WriteCmd(0xB7);
	WriteData(0xc6);

	// HS Lanes Control (BEh)
	WriteCmd(0xBE);
	WriteData(0x00);
	WriteData(0x04);

	// Set Image Function (E9h)
	WriteCmd(0xE9);
	WriteData(0x00);

	// Set direction
	SetDirection(device.dir);

	// Interface Pixel Format (3Ah)
	WriteCmd(0x3A);
	WriteData(0x55);/* 0x55 : 16 bits/pixel  */

	// Sleep Out (11h)
	WriteCmd(0x11);
	System::DelayMs(120);

	// Display On
	WriteCmd(0x29);
}


///ILI9488 read id
uint32_t ILI9488::ReadID()
{
	WriteCmd(0x04);
      
	//The first pack we don't need
	uint32_t lcdID = ReadData();

	lcdID = (ReadData() & 0x00ff) << 16;
	lcdID += (ReadData() & 0x00ff) << 8;
	lcdID += (ReadData() & 0x00ff);

	return lcdID;
}


///ILI9488 write reg
void ILI9488::WriteCmd(uint16_t reg)
{
	lcdmap->reg = reg;
}


///ILI9488 write data
void ILI9488::WriteData(uint16_t data)
{
	lcdmap->ram = data;
}


///ILI9488 read data
uint16_t ILI9488::ReadData()
{
	return uint16_t(lcdmap->ram);
}


///ILI9488 write reg
void ILI9488::WriteReg(uint16_t reg, uint16_t value)
{
	lcdmap->reg = reg;
	lcdmap->ram = value;
}


///ILI9488 read reg
uint16_t ILI9488::ReadRegData(uint16_t reg)
{
	WriteCmd(reg);
	return ReadData();
}


///ILI9488 prepare write gram
void ILI9488::PrepareWriteRAM()
{
	lcdmap->reg = device.wRamCmd;
}


///ILI9488 write gram
void ILI9488::WriteRAM(uint16_t rgbVal)
{
	lcdmap->ram = rgbVal;
}


///ILI9488 display on
void ILI9488::BackLightOn()
{
	backLight.Set();
}


///ILI9488 display off
void ILI9488::BackLightOff()
{
	backLight.Clear();
}


///ILI9488 display on
void ILI9488::DisplayOn()
{
	WriteCmd(0x29);
}


///ILI9488 display off
void ILI9488::DisplayOff()
{
	WriteCmd(0x28);
}


///ILI9488 set direction
void ILI9488::SetDirection(Dir dir)
{
	switch (dir)
	{
	case Up:
		WriteCmd(0x36);
		WriteData(0x08);
		break;

	case Right:
		WriteCmd(0x36);
		WriteData(0x68);
		break;

	case Down:
		WriteCmd(0x36);
		WriteData(0xC8);
		break;

	case Left:
		WriteCmd(0x36);
		WriteData(0xA8);
		break;
	}

	WriteCmd(device.setXCmd);
	// x start
	WriteData(0x00);
	WriteData(0x00);
	// x end
	WriteData((device.width - 1) >> 8);
	WriteData((device.width - 1) & 0xff);

	WriteCmd(device.setYCmd);
	// y start
	WriteData(0x00);
	WriteData(0x00);
	// y end
	WriteData((device.height - 1) >> 8);
	WriteData((device.height - 1) & 0xff);
}


///ILI9488 open window
void ILI9488::OpenWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	WriteCmd(device.setXCmd);
	WriteData(x >> 8);
	WriteData(x & 0XFF);
	WriteData((x + width - 1) >> 8);
	WriteData((x + width - 1) & 0xff);

	WriteCmd(device.setYCmd);
	WriteData(y >> 8);
	WriteData(y & 0XFF);
	WriteData((y + height - 1) >> 8);
	WriteData((y + height - 1) & 0xff);
}


///ILI9488 set cursor
void ILI9488::SetCursor(uint16_t x, uint16_t y)
{
	OpenWindow(x, y, 1, 1);
}


///ILI9488 draw point
void ILI9488::DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	SetCursor(x, y);
	WriteReg(device.wRamCmd, color);
}


///ILI9488 read point
uint16_t ILI9488::ReadPoint()
{
	uint16_t usR = 0, usG = 0, usB = 0;

	WriteCmd(device.rRamCmd);

	usR = ReadData();
	usR = ReadData();
	usB = ReadData();
	usG = ReadData();

	return (((usR >> 11) << 11) | ((usG >> 10) << 5) | (usB >> 11));
}


///ILI9488 read point
uint16_t ILI9488::ReadPoint(uint16_t x, uint16_t y)
{
	uint16_t usPixelData;

	SetCursor(x, y);

	usPixelData = ReadPoint();

	return usPixelData;
}


///ILI9488 fill color
void ILI9488::Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	uint16_t width = abs(x0 - x1) + 1;
	uint16_t height = abs(y0 - y1) + 1;
	OpenWindow(x0, y0, width, height);
	Fill(width * height, color);
}


///ILI9488 fill color
void ILI9488::Fill(uint32_t pointSizes, uint16_t color)
{
	PrepareWriteRAM();

	for (uint32_t i = 0; i < pointSizes; i++)
	{
		WriteData(color);
	}
}


///ILI9488 clear
void ILI9488::Clear(uint16_t color)
{
	OpenWindow(0, 0, device.width, device.height);
	uint32_t totalpoint = device.width * device.height;
	Fill(totalpoint, color);
}


///Register driver
REGISTER_DRIVER(new ILI9488(), DriverID::_display, display);
