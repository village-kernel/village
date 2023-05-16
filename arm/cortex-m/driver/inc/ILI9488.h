//###########################################################################
// ILI8488.h
// Declarations of the functions that manage ILI9488
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ILI9488_H__
#define __ILI9488_H__

#include "HalHeaders.h"
#include "LcdDriver.h"
#include "Driver.h"
#include "Gpo.h"
#include "Fsmc.h"


///ILI9488
class ILI9488 : public Driver, public LcdDriver
{
public:
	struct Config
	{
		Fsmc::Config fsmcConfig;
		Gpio::GpioChannel backLightCh;
		uint16_t backLightPin;
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
	Gpo backLight;
	Config config;
	DriverInfo lcd;
	LCDMap *lcdmap = (LCDMap*)(uint32_t)(0x6C000000 | 0x0000007E);

	//Methods
	void WriteCmd(uint16_t reg);
	void WriteData(uint16_t data);
	uint16_t ReadData();
	void WriteReg(uint16_t reg, uint16_t value);
	uint16_t ReadRegData(uint16_t reg);
	void PrepareWriteRAM();
	void WriteRAM(uint16_t rgbVal);
	
	//Device methods
	void InitConfig();
	void DeviceConfig();
	void DisplayConfig();
	uint32_t ReadID();

	//Display methods
	uint16_t ReadPoint();
	void Fill(uint32_t pointSizes, uint16_t color);
public:
	//Device Methods
	ILI9488();
	void Initialize();
	void BackLightOn();
	void BackLightOff();
	void DisplayOn();
	void DisplayOff();
	
	//Display methods
	void OpenWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
	void SetCursor(uint16_t x, uint16_t y);
	void SetDirection(Direction dir);
	void DrawPoint(uint16_t x, uint16_t y, uint16_t color);
	uint16_t ReadPoint(uint16_t x, uint16_t y);
	void Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
	void Clear(uint16_t color = 0);
};

#endif //!__ILI9488_H__
