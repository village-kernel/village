//###########################################################################
// vk_ia32legacy_devices.cpp
// Definitions of the functions that manage devices config
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_ia32legacy_devices.h"
#include "vk_kernel.h"


/// @brief AtaLbaDiskDev
void AtaLbaDiskDev::Config()
{
	config = {
		.drv = 1,
	};
	driverData = (void*)&config;
	driverName = (char*)"disk0";
}
REGISTER_PLAT_DEVICE(new AtaLbaDiskDev(), ataLbaDisk, ataLbaDiskDev);


/// @brief BochsVBEDev
void BochsVBEDev::Config()
{
	config = {
		.vmap = (uint16_t*)0xA00000,
	};
	driverData = (void*)&config;
	driverName = (char*)"display0";
}
REGISTER_PLAT_DEVICE(new BochsVBEDev(), bochsVBE, bochsVBEDev);


/// @brief PS2KeyBoardDev
void PS2KeyBoardDev::Config()
{
	config = {
		.irq = Keyboard_Controller_IRQn,
	};
	driverData = (void*)&config;
	driverName = (char*)"keyboard0";
}
REGISTER_PLAT_DEVICE(new PS2KeyBoardDev(), ps2keyboard, ps2keyboardDev);


/// @brief PS2MouseDev
void PS2MouseDev::Config()
{
	config = {
		.irq = Mouse_Controller_IRQn,
	};
	driverData = (void*)&config;
	driverName = (char*)"mouse0";
}
REGISTER_PLAT_DEVICE(new PS2MouseDev(), ps2mouse, ps2mouseDev);


/// @brief Pic32UartDev
void Pic32UartDev::Config()
{
	config = {
		.port = 0,
	};
	driverData = (void*)&config;
	driverName = (char*)"serial0";
}
REGISTER_PLAT_DEVICE(new Pic32UartDev(), pic32uart, pic32uartDev);


/// @brief Pit32TimerDev
void Pit32TimerDev::Config()
{
	config = {
		.timer = 0,
	};
	driverData = (void*)&config;
	driverName = (char*)"timer0";
}
REGISTER_PLAT_DEVICE(new Pit32TimerDev(), pit32timer, pit32timerDev);
