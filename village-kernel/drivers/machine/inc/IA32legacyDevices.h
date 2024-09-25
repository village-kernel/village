//###########################################################################
// IA32legacyDevices.h
// Declarations of the functions that manage ia32legacy devices
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __IA32LEGACY_DEVICE_H__
#define __IA32LEGACY_DEVICE_H__

#include "AtaLbaDisk.h"
#include "BochsVBE.h"
#include "PS2KeyBoard.h"
#include "PS2Mouse.h"
#include "Pic32Uart.h"
#include "Pit32Timer.h"


/// @brief AtaLbaDiskDev
class AtaLbaDiskDev : public PlatDevice
{
private:
	/// @brief Members
	AtaLbaDisk::Config config;
public:
	/// @brief Methods
	void Config();
};


/// @brief BochsVBEDev
class BochsVBEDev : public PlatDevice
{
private:
	/// @brief Members
	BochsVBE::Config config;
public:
	/// @brief Methods
	void Config();
};


/// @brief PS2KeyBoardDev
class PS2KeyBoardDev : public PlatDevice
{
private:
	/// @brief Members
	PS2KeyBoard::Config config;
public:
	/// @brief Methods
	void Config();
};


/// @brief PS2MouseDev
class PS2MouseDev : public PlatDevice
{
private:
	/// @brief Members
	PS2Mouse::Config config;
public:
	/// @brief Methods
	void Config();
};


/// @brief Pic32UartDev
class Pic32UartDev : public PlatDevice
{
private:
	/// @brief Members
	Pic32Uart::Config config;
public:
	/// @brief Methods
	void Config();
};


/// @brief Pit32TimerDev
class Pit32TimerDev : public PlatDevice
{
private:
	/// @brief Members
	Pit32Timer::Config config;
public:
	/// @brief Methods
	void Config();
};

#endif //!__IA32LEGACY_DEVICE_H__
