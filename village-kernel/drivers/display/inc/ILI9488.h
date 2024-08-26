//###########################################################################
// ILI9488.h
// Declarations of the functions that manage ili9488
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ILI9488_H__
#define __ILI9488_H__

#include "Hardware.h"
#include "Driver.h"


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

	//Enumerates
	enum Direction
	{
		_Up = 0,
		_Left,
		_Right,
		_Down,
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
	struct LCDMap
	{
		uint16_t reg;
		uint16_t ram;
	} __attribute__((packed));
private:
	//Members
	Fsmc   fsmc;
	Gpio   blGpio;
	Config config;
	DriverInfo lcd;
	volatile LCDMap *lcdmap = (LCDMap*)(uint32_t)(0x6C00007E);

	/// @brief Methods
	void PinConfig();
	void Fill(uint32_t pointSizes, uint32_t color);
	uint32_t ReadID();
	void WriteCmd(uint16_t reg);
	void WriteData(uint16_t data);
	uint16_t ReadData();
	void WriteReg(uint16_t reg, uint16_t value);
	uint16_t ReadRegData(uint16_t reg);
	void PrepareWriteRAM();
	void WriteRAM(uint16_t rgbVal);
public:
	/// @brief Methods
	ILI9488();
	~ILI9488();
	void DeviceConfig();
	void DisplayConfig();
	void BackLightOn();
	void BackLightOff();
	void DisplayOn();
	void DisplayOff();
	void SetDirection(Direction dir);
	void OpenWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	/// @brief Plat Methods
	void SetData(void* data);

	/// @brief FB Methods
	bool Setup();
	void SetCursor(uint32_t x, uint32_t y);
	void DrawPoint(uint32_t x, uint32_t y, uint32_t color);
	uint32_t ReadPoint();
	uint32_t ReadPoint(uint32_t x, uint32_t y);
	void Fill(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color);
	void Clear(uint32_t color = 0);
	void Exit();

	/// @brief Fopts Methods
	bool Open();
	int IOCtrl(uint8_t cmd, void* data);
	void Close();
};


/// @brief ILI9488Drv
class ILI9488Drv : public PlatDriver
{
public:
	/// @brief Plat Methods
	bool Probe(PlatDevice* device);
	bool Remove(PlatDevice* device);
};

#endif //!__ILI9488_H__
