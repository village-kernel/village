//###########################################################################
// vk_ia32legacy_devices.h
// Declarations of the functions that manage ia32legacy devices
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_IA32LEGACY_DEVICE_H__
#define __VK_IA32LEGACY_DEVICE_H__

#include "vk_ata_lba_disk.h"
#include "vk_bochs_vbe.h"
#include "vk_ps2_keyboard.h"
#include "vk_ps2_mouse.h"
#include "vk_pic32_uart.h"
#include "vk_pit32_timer.h"


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

#endif //!__VK_IA32LEGACY_DEVICE_H__
