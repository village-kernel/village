 //###########################################################################
// vk_stm32_usbd_fs.cpp
// Definitions of the functions that manage stm32 usbd fs
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_stm32_usbd_fs.h"
#include "vk_kernel.h"


/// @brief Constructor
Stm32UsbdFS::Stm32UsbdFS()
{
}


/// @brief Destructor
Stm32UsbdFS::~Stm32UsbdFS()
{
}


/// @brief Set dasta
/// @param data 
void Stm32UsbdFS::SetData(void* data)
{
	config = *((Config*)data);

	if (config.usb < 0 || config.usb > 3)
	{
		config.usb = 0;
	}
}


/// @brief Open
bool Stm32UsbdFS::Open()
{
	return true;
}


/// @brief Close
void Stm32UsbdFS::Close()
{

}


/// @brief Probe
/// @param device 
/// @return 
bool Stm32UsbdFSDrv::Probe(PlatDevice* device)
{
	Stm32UsbdFS* stm32UsbdFS = new Stm32UsbdFS(); 
	stm32UsbdFS->SetID(DriverID::_network);
	stm32UsbdFS->SetName(device->GetDriverName());
	stm32UsbdFS->SetData(device->GetDriverData());
	device->SetDriver(stm32UsbdFS);
	kernel->device.RegisterNetworkDevice((NetworkDriver*)device->GetDriver());
	return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool Stm32UsbdFSDrv::Remove(PlatDevice* device)
{
	kernel->device.UnregisterNetworkDevice((NetworkDriver*)device->GetDriver());
	delete (Stm32UsbdFS*)device->GetDriver();
	device->SetDriver(NULL);
	return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new Stm32UsbdFSDrv(), stm32UsbdFS, stm32UsbdFSDrv);
