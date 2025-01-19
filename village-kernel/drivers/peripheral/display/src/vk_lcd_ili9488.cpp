//###########################################################################
// vk_lcd_ili9488.cpp
// Definitions of the functions that manage ili9488
//
// $Copyright: Copyright (C)
//###########################################################################
#include "vk_lcd_ili9488.h"
#include "vk_kernel.h"
#include "stdlib.h"


/// @brief Constructor
ILI9488::ILI9488()
{
}


/// @brief Destructor
ILI9488::~ILI9488()
{
}


/// @brief 
/// @param data 
void ILI9488::SetData(void* data)
{
	config = *((Config*)data);
}


/// @brief Pin config
inline void ILI9488::PinConfig()
{
	Gpio pin;
	pin.Initialize(config.csGpio);
	pin.Initialize(config.rsGpio);
	pin.Initialize(config.wrGpio);
	pin.Initialize(config.rdGpio);
	pin.Initialize(config.db0Gpio);
	pin.Initialize(config.db1Gpio);
	pin.Initialize(config.db2Gpio);
	pin.Initialize(config.db3Gpio);
	pin.Initialize(config.db4Gpio);
	pin.Initialize(config.db5Gpio);
	pin.Initialize(config.db6Gpio);
	pin.Initialize(config.db7Gpio);
	pin.Initialize(config.db8Gpio);
	pin.Initialize(config.db9Gpio);
	pin.Initialize(config.db10Gpio);
	pin.Initialize(config.db11Gpio);
	pin.Initialize(config.db12Gpio);
	pin.Initialize(config.db13Gpio);
	pin.Initialize(config.db14Gpio);
	pin.Initialize(config.db15Gpio);
	blGpio.Initialize(config.blGpio);
}


/// @brief ILI9488 fill color
/// @param pointSizes 
/// @param color 
inline void ILI9488::Fill(uint32_t pointSizes, uint32_t color)
{
	PrepareWriteRAM();

	for (uint32_t i = 0; i < pointSizes; i++)
	{
		WriteData(color);
	}
}


/// @brief ILI9488 read id
inline uint32_t ILI9488::ReadID()
{
	WriteCmd(0x04);
	
	//The first pack we don't need
	volatile uint32_t lcdID = ReadData();

	lcdID  = (ReadData() & 0x00ff) << 16;
	lcdID += (ReadData() & 0x00ff) << 8;
	lcdID += (ReadData() & 0x00ff);

	return lcdID;
}


/// @brief ILI9488 write reg
inline void ILI9488::WriteCmd(uint16_t reg)
{
	lcdmap->reg = reg;
}


/// @brief ILI9488 write data
inline void ILI9488::WriteData(uint16_t data)
{
	lcdmap->ram = data;
}


/// @brief ILI9488 read data
inline uint16_t ILI9488::ReadData()
{
	return lcdmap->ram;
}


/// @brief ILI9488 write reg
inline void ILI9488::WriteReg(uint16_t reg, uint16_t value)
{
	lcdmap->reg = reg;
	lcdmap->ram = value;
}


/// @brief ILI9488 read reg
inline uint16_t ILI9488::ReadRegData(uint16_t reg)
{
	WriteCmd(reg);
	return ReadData();
}


/// @brief ILI9488 prepare write gram
inline void ILI9488::PrepareWriteRAM()
{
	lcdmap->reg = lcd.wRamCmd;
}


/// @brief ILI9488 write gram
inline void ILI9488::WriteRAM(uint16_t rgbVal)
{
	lcdmap->ram = rgbVal;
}


/// @brief ILI9488 Setup
bool ILI9488::Setup()
{
	PinConfig();

	fsmc.Initialize();

	kernel->system.DelayMs(50);

	DeviceConfig();

	if (lcd.id == ReadID())
	{
		DisplayConfig();
		Clear();
		BackLightOn();
		return true;
	}

	return false;
}


/// @brief Config lcd info
void ILI9488::DeviceConfig()
{
	lcd.id = 0x548066;
	lcd.setXCmd = 0x2A;
	lcd.setYCmd = 0x2B;
	lcd.wRamCmd = 0X2C;
	lcd.rRamCmd = 0x2E;

	lcd.dir = _Up;
	//lcd.dir = _Down;
	lcd.width = 320;
	lcd.height = 480;

	////lcd.dir = _Left;
	//lcd.dir = _Right;
	//lcd.width = 480;
	//lcd.height = 320;

	info.width = lcd.width;
	info.height = lcd.height;
	info.bitdepth = 16; // 16 bpp
}


/// @brief ILI9488 display config
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
	SetDirection(lcd.dir);

	// Interface Pixel Format (3Ah)
	WriteCmd(0x3A);
	WriteData(0x55);/* 0x55 : 16 bits/pixel  */

	// Sleep Out (11h)
	WriteCmd(0x11);
	kernel->system.DelayMs(120);

	// Display On
	WriteCmd(0x29);
}


/// @brief ILI9488 display on
void ILI9488::BackLightOn()
{
	blGpio.Set();
}


/// @brief ILI9488 display off
void ILI9488::BackLightOff()
{
	blGpio.Clear();
}


/// @brief ILI9488 display on
void ILI9488::DisplayOn()
{
	WriteCmd(0x29);
}


/// @brief ILI9488 display off
void ILI9488::DisplayOff()
{
	WriteCmd(0x28);
}


/// @brief ILI9488 set direction
void ILI9488::SetDirection(Direction dir)
{
	switch (dir)
	{
	case _Up:
		WriteCmd(0x36);
		WriteData(0x08);
		break;

	case _Right:
		WriteCmd(0x36);
		WriteData(0x68);
		break;

	case _Down:
		WriteCmd(0x36);
		WriteData(0xC8);
		break;

	case _Left:
		WriteCmd(0x36);
		WriteData(0xA8);
		break;
	}

	WriteCmd(lcd.setXCmd);
	// x start
	WriteData(0x00);
	WriteData(0x00);
	// x end
	WriteData((lcd.width - 1) >> 8);
	WriteData((lcd.width - 1) & 0xff);

	WriteCmd(lcd.setYCmd);
	// y start
	WriteData(0x00);
	WriteData(0x00);
	// y end
	WriteData((lcd.height - 1) >> 8);
	WriteData((lcd.height - 1) & 0xff);
}


/// @brief ILI9488 open window
void ILI9488::OpenWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	WriteCmd(lcd.setXCmd);
	WriteData(x >> 8);
	WriteData(x & 0XFF);
	WriteData((x + width - 1) >> 8);
	WriteData((x + width - 1) & 0xff);

	WriteCmd(lcd.setYCmd);
	WriteData(y >> 8);
	WriteData(y & 0XFF);
	WriteData((y + height - 1) >> 8);
	WriteData((y + height - 1) & 0xff);
}


/// @brief ILI9488 set cursor
void ILI9488::SetCursor(uint32_t x, uint32_t y)
{
	OpenWindow(x, y, 1, 1);
}


/// @brief ILI9488 draw point
void ILI9488::DrawPoint(uint32_t x, uint32_t y, uint32_t color)
{
	SetCursor(x, y);
	WriteReg(lcd.wRamCmd, color);
}


/// @brief ILI9488 read point
uint32_t ILI9488::ReadPoint()
{
	uint32_t usR = 0, usG = 0, usB = 0;

	WriteCmd(lcd.rRamCmd);

	usR = ReadData();
	usR = ReadData();
	usB = ReadData();
	usG = ReadData();

	return (((usR >> 11) << 11) | ((usG >> 10) << 5) | (usB >> 11));
}


/// @brief ILI9488 read point
uint32_t ILI9488::ReadPoint(uint32_t x, uint32_t y)
{
	uint32_t usPixelData;

	SetCursor(x, y);

	usPixelData = ReadPoint();

	return usPixelData;
}


/// @brief ILI9488 fill color
void ILI9488::Fill(uint32_t sx, uint32_t sy, uint32_t ex, uint32_t ey, uint32_t color)
{
	uint16_t width = labs(sx - ex) + 1;
	uint16_t height = labs(sy - ey) + 1;
	OpenWindow(sx, sy, width, height);
	Fill(width * height, color);
}


/// @brief ILI9488 clear
void ILI9488::Clear(uint32_t color)
{
	OpenWindow(0, 0, lcd.width, lcd.height);
	uint32_t totalpoint = lcd.width * lcd.height;
	Fill(totalpoint, color);
}


/// @brief ILI9488 Exit
void ILI9488::Exit()
{

}


/// @brief Open
bool ILI9488::Open()
{
	return Setup();
}


/// @brief IOCtrl
/// @param cmd 
/// @param data 
/// @return 
int ILI9488::IOCtrl(uint8_t cmd, void* data)
{
	FBDriver** fbdev = (FBDriver**)data;

	*fbdev = this;

	return 0;
}


/// @brief close
void ILI9488::Close()
{
	Exit();
}


/// @brief Probe
/// @param device 
/// @return 
bool ILI9488Drv::Probe(PlatDevice* device)
{
	ILI9488* ili9488 = new ILI9488(); 
	ili9488->SetID(DriverID::_framebuffer);
	ili9488->SetName(device->GetDriverName());
	ili9488->SetData(device->GetDriverData());
	device->SetDriver(ili9488);
	kernel->device.RegisterFBDevice((FBDriver*)device->GetDriver());
	return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool ILI9488Drv::Remove(PlatDevice* device)
{
	kernel->device.UnregisterFBDevice((FBDriver*)device->GetDriver());
	delete (ILI9488*)device->GetDriver();
	device->SetDriver(NULL);
	return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new ILI9488Drv(), ili9488, ili9488Drv);
