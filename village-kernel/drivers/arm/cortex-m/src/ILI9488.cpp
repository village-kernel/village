//###########################################################################
// ILI9488.cpp
//
// $Copyright: Copyright (C)
//###########################################################################
#include "Kernel.h"
#include "HwConfig.h"
#include "Hardware.h"
#include "stdlib.h"


/// @brief ILI9488
class ILI9488 : public FBDriver
{
public:
	//Structures
	struct Config
	{
		Gpio::Config blGpio;
		Gpio::Config csGpio;
		Gpio::Config rsGpio;
		Gpio::Config wrGpio;
		Gpio::Config rdGpio;
		Gpio::Config db0Gpio;
		Gpio::Config db1Gpio;
		Gpio::Config db2Gpio;
		Gpio::Config db3Gpio;
		Gpio::Config db4Gpio;
		Gpio::Config db5Gpio;
		Gpio::Config db6Gpio;
		Gpio::Config db7Gpio;
		Gpio::Config db8Gpio;
		Gpio::Config db9Gpio;
		Gpio::Config db10Gpio;
		Gpio::Config db11Gpio;
		Gpio::Config db12Gpio;
		Gpio::Config db13Gpio;
		Gpio::Config db14Gpio;
		Gpio::Config db15Gpio;
	};
protected:
	//Enumerates
	enum Direction
	{
		Up = 0,
		Left,
		Right,
		Down,
	};

	//Structures
	struct DriverInfo
	{
		uint32_t  id;
		uint16_t  width;
		uint16_t  height;
		uint16_t  setXCmd;
		uint16_t  setYCmd;
		uint16_t  wRamCmd;
		uint16_t  rRamCmd;
		Direction dir;
	};

	//LCD map
	struct __packed LCDMap
	{
		volatile uint16_t reg;
		volatile uint16_t ram;
	};

	//Members
	Fsmc fsmc;
	Gpio blGpio;
	Config config;
	DriverInfo lcd;
	LCDMap *lcdmap = (LCDMap*)(uint32_t)(0x6C000000 | 0x0000007E);
private:
	/// @brief Init config
	inline void InitConfig()
	{
		config = LCD_RGB565_CONFIG;
	}


	/// @brief Pin config
	inline void PinConfig()
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
private:
	/// @brief ILI9488 fill color
	/// @param pointSizes 
	/// @param color 
	void Fill(uint32_t pointSizes, uint32_t color)
	{
		PrepareWriteRAM();

		for (uint32_t i = 0; i < pointSizes; i++)
		{
			WriteData(color);
		}
	}


	/// @brief ILI9488 read id
	uint32_t ReadID()
	{
		WriteCmd(0x04);
		
		//The first pack we don't need
		uint32_t lcdID = ReadData();

		lcdID = (ReadData() & 0x00ff) << 16;
		lcdID += (ReadData() & 0x00ff) << 8;
		lcdID += (ReadData() & 0x00ff);

		return lcdID;
	}


	/// @brief ILI9488 write reg
	void WriteCmd(uint16_t reg)
	{
		lcdmap->reg = reg;
	}


	/// @brief ILI9488 write data
	void WriteData(uint16_t data)
	{
		lcdmap->ram = data;
	}


	/// @brief ILI9488 read data
	uint16_t ReadData()
	{
		return (uint16_t)lcdmap->ram;
	}


	/// @brief ILI9488 write reg
	void WriteReg(uint16_t reg, uint16_t value)
	{
		lcdmap->reg = reg;
		lcdmap->ram = value;
	}


	/// @brief ILI9488 read reg
	uint16_t ReadRegData(uint16_t reg)
	{
		WriteCmd(reg);
		return ReadData();
	}


	/// @brief ILI9488 prepare write gram
	void PrepareWriteRAM()
	{
		lcdmap->reg = lcd.wRamCmd;
	}


	/// @brief ILI9488 write gram
	void WriteRAM(uint16_t rgbVal)
	{
		lcdmap->ram = rgbVal;
	}
public:
	/// @brief Constructor
	ILI9488()
	{
	}


	/// @brief Initialize
	void Initialize()
	{
		InitConfig();

		PinConfig();

		fsmc.Initialize();

		kernel->system.DelayMs(50);

		DeviceConfig();

		if (lcd.id == ReadID())
		{
			DisplayConfig();
			Clear();
			BackLightOn();
		}
	}


	/// @brief Config lcd info
	void DeviceConfig()
	{
		lcd.id = 0x548066;
		lcd.dir = Down;
		lcd.width = 320;
		lcd.height = 480;
		lcd.setXCmd = 0x2A;
		lcd.setYCmd = 0x2B;
		lcd.wRamCmd = 0X2C;
		lcd.rRamCmd = 0x2E;

		device.width = lcd.width;
		device.height = lcd.height;
		device.bitdepth = 0x10; // 16 bpp
	}


	/// @brief ILI9488 display config
	void DisplayConfig()
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
	void BackLightOn()
	{
		blGpio.Set();
	}


	/// @brief ILI9488 display off
	void BackLightOff()
	{
		blGpio.Clear();
	}


	/// @brief ILI9488 display on
	void DisplayOn()
	{
		WriteCmd(0x29);
	}


	/// @brief ILI9488 display off
	void DisplayOff()
	{
		WriteCmd(0x28);
	}


	/// @brief ILI9488 set direction
	void SetDirection(Direction dir)
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
	void OpenWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
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
	void SetCursor(uint32_t x, uint32_t y)
	{
		OpenWindow(x, y, 1, 1);
	}


	/// @brief ILI9488 draw point
	void DrawPoint(uint32_t x, uint32_t y, uint32_t color)
	{
		SetCursor(x, y);
		WriteReg(lcd.wRamCmd, color);
	}


	/// @brief ILI9488 read point
	uint32_t ReadPoint()
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
	uint32_t ReadPoint(uint32_t x, uint32_t y)
	{
		uint32_t usPixelData;

		SetCursor(x, y);

		usPixelData = ReadPoint();

		return usPixelData;
	}


	/// @brief ILI9488 fill color
	void Fill(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
	{
		uint16_t width = labs(x0 - x1) + 1;
		uint16_t height = labs(y0 - y1) + 1;
		OpenWindow(x0, y0, width, height);
		Fill(width * height, color);
	}


	/// @brief ILI9488 clear
	void Clear(uint32_t color = 0)
	{
		OpenWindow(0, 0, lcd.width, lcd.height);
		uint32_t totalpoint = lcd.width * lcd.height;
		Fill(totalpoint, color);
	}
};


/// @brief ILI9488Drv
class ILI9488Drv : public Driver
{
private:
	//Members
	ILI9488* ili9488;
public:
	/// @brief Constructor
	ILI9488Drv()
	{
	}


	/// @brief Destructor
	~ILI9488Drv()
	{
		delete ili9488;
	}


	/// @brief 
	bool Open()
	{
		if (NULL == ili9488)
		{
			ili9488 = new ILI9488();
			ili9488->Initialize();
			return true;
		}
		return false;
	}


	/// @brief close
	void Close()
	{

	}


	/// @brief IOCtrl
	/// @param cmd 
	/// @param data 
	/// @return 
	int IOCtrl(uint8_t cmd, void* data)
	{
		FBDriver** fbdev = (FBDriver**)data;
		
		*fbdev = ili9488;

		return 0;
	}
};


///Register driver
REGISTER_DRIVER(new ILI9488Drv(), DriverID::_miscellaneous, display0);
