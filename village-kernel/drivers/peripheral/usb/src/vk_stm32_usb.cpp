 //###########################################################################
// vk_stm32_usb.cpp
// Definitions of the functions that manage stm32 usb
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_stm32_usb.h"
#include "vk_kernel.h"


/// @brief Constructor
Stm32Usb::Stm32Usb()
	:isUsed(false)
{
}


/// @brief Destructor
Stm32Usb::~Stm32Usb()
{
}


/// @brief Set dasta
/// @param data 
void Stm32Usb::SetData(void* data)
{
	config = *((Config*)data);
}


/// @brief Pin config
void Stm32Usb::PinConfig()
{

}


/// @brief Open
bool Stm32Usb::Open()
{
	//Return when is used
	if (isUsed) return true;
	
	//Pin config
	PinConfig();

	//Configure usb
	usb.Initialize();
	
	//Set isUsed flag
	isUsed = true;

	return true;
}


/// @brief Close
void Stm32Usb::Close()
{
	isUsed = false;
}


/// @brief Probe
/// @param device 
/// @return 
bool Stm32UsbDrv::Probe(PlatDevice* device)
{
	Stm32Usb* stm32Usb = new Stm32Usb(); 
	stm32Usb->SetID(DriverID::_character);
	stm32Usb->SetName(device->GetDriverName());
	stm32Usb->SetData(device->GetDriverData());
	device->SetDriver(stm32Usb);
	kernel->device.RegisterCharDevice((CharDriver*)device->GetDriver());
	return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool Stm32UsbDrv::Remove(PlatDevice* device)
{
	kernel->device.UnregisterCharDevice((CharDriver*)device->GetDriver());
	delete (Stm32Usb*)device->GetDriver();
	device->SetDriver(NULL);
	return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new Stm32UsbDrv(), stm32Usb, stm32UsbDrv);
