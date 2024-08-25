//###########################################################################
// IA32legacyDevices.cpp
// Definitions of the functions that manage devices config
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "IA32legacyDevices.h"
#include "Kernel.h"


/// @brief AtaLbaDiskDev
void AtaLbaDiskDev::Config()
{
	config = {
		.drv = 1,
	};
	SetDriverData((void*)&config);
	SetDriverName((char*)"disk0");
}
REGISTER_PLAT_DEVICE(new AtaLbaDiskDev(), ataLbaDisk);


/// @brief BochsVBEDev
void BochsVBEDev::Config()
{
	config = {
		.vmap = (uint16_t*)0xA00000,
	};
	SetDriverData((void*)&config);
	SetDriverName((char*)"display0");
}
REGISTER_PLAT_DEVICE(new BochsVBEDev(), bochsVBE);


/// @brief PS2KeyBoardDev
void PS2KeyBoardDev::Config()
{
	config = {
		.irq = Keyboard_Controller_IRQn,
	};
	SetDriverData((void*)&config);
	SetDriverName((char*)"keyboard0");
}
REGISTER_PLAT_DEVICE(new PS2KeyBoardDev(), ps2keyboard);


/// @brief PS2MouseDev
void PS2MouseDev::Config()
{
	config = {
		.irq = Mouse_Controller_IRQn,
	};
	SetDriverData((void*)&config);
	SetDriverName((char*)"mouse0");
}
REGISTER_PLAT_DEVICE(new PS2MouseDev(), ps2mouse);


/// @brief Pic32UartDev
void Pic32UartDev::Config()
{
	config = {
		.port = 0,
	};
	SetDriverData((void*)&config);
	SetDriverName((char*)"serial0");
}
REGISTER_PLAT_DEVICE(new Pic32UartDev(), pic32uart);


/// @brief Pit32TimerDev
void Pit32TimerDev::Config()
{
	config = {
		.timer = 0,
	};
	SetDriverData((void*)&config);
	SetDriverName((char*)"timer0");
}
REGISTER_PLAT_DEVICE(new Pit32TimerDev(), pit32Timer);
