 //###########################################################################
// Pit32Timer.cpp
// Definitions of the functions that manage pit32 timer
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Pit32Timer.h"
#include "Kernel.h"


/// @brief Constructor
Pit32Timer::Pit32Timer()
{
}


/// @brief Destructor
Pit32Timer::~Pit32Timer()
{
}


/// @brief Set dasta
/// @param data 
void Pit32Timer::SetData(void* data)
{
	config = *((Config*)data);

	if (config.timer < 0 || config.timer > 3)
	{
		config.timer = 0;
	}
}


/// @brief Open
bool Pit32Timer::Open()
{
	//uint32_t freq = 1000; //1000hz, 1ms
	//uint32_t divider = 1193182 / freq;
	//uint8_t low  = low_8(divider);
	//uint8_t high = high_8(divider);

	//PortByteOut(TIMERX[config.timer], 0x36); //Command port
	//PortByteOut(TIMERX[config.timer], low);
	//PortByteOut(TIMERX[config.timer], high);
}


/// @brief Close
void Pit32Timer::Close()
{

}


/// @brief Probe
/// @param device 
/// @return 
bool Pit32TimerDrv::Probe(PlatDevice* device)
{
	Pit32Timer* pit32Timer = new Pit32Timer(); 
	pit32Timer->SetID(DriverID::_miscellaneous);
	pit32Timer->SetName(device->GetDriverName());
	pit32Timer->SetData(device->GetDriverData());
	device->SetDriver(pit32Timer);
	kernel->device.RegisterMiscDevice((MiscDevice*)device->GetDriver());
	return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool Pit32TimerDrv::Remove(PlatDevice* device)
{
	kernel->device.UnregisterMiscDevice((MiscDevice*)device->GetDriver());
	return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new Pit32TimerDrv(), pit32timer);
