//###########################################################################
// Device.cpp
// Definitions of the functions that manage driver
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Device.h"


/// @brief Constructor
ConcreteDevice::ConcreteDevice()
{
}


/// @brief Destructor
ConcreteDevice::~ConcreteDevice()
{
}


/// @brief Device Setup
void ConcreteDevice::Setup()
{
	//Output debug info
	kernel->debug.Info("Device setup done!");
}


/// @brief Device Exit
void ConcreteDevice::Exit()
{
	blockDevs.Release();
	charDevs.Release();
	fbDevs.Release();
	ntDevs.Release();
	miscDevs.Release();
	platDevs.Release();
	platDrvs.Release();
}


/// @brief Register block device object
/// @param device device pointer
void ConcreteDevice::RegisterBlockDevice(BlockDevice* device)
{
	blockDevs.Add(device, device->GetName());
}


/// @brief Deregister block device object
/// @param device device pointer
void ConcreteDevice::DeregisterBlockDevice(BlockDevice* device)
{
	blockDevs.Remove(device);
}


/// @brief Register char device object
/// @param device device pointer
void ConcreteDevice::RegisterCharDevice(CharDevice* device)
{
	charDevs.Add(device, device->GetName());
}


/// @brief Deregister char device object
/// @param device device pointer
void ConcreteDevice::DeregisterCharDevice(CharDevice* device)
{
	charDevs.Remove(device);
}


/// @brief Register fb device object
/// @param device device pointer
void ConcreteDevice::RegisterFBDevice(FBDevice* device)
{
	fbDevs.Add(device, device->GetName());
}


/// @brief Deregister fb device object
/// @param device device pointer
void ConcreteDevice::DeregisterFBDevice(FBDevice* device)
{
	fbDevs.Remove(device);
}


/// @brief Register nt device object
/// @param device device pointer
void ConcreteDevice::RegisterNetworkDevice(NetworkDevice* device)
{
	ntDevs.Add(device, device->GetName());
}


/// @brief Deregister nt device object
/// @param device device pointer
void ConcreteDevice::DeregisterNetworkDevice(NetworkDevice* device)
{
	ntDevs.Remove(device);
}


/// @brief Register misc device object
/// @param device device pointer
void ConcreteDevice::RegisterMiscDevice(MiscDevice* device)
{
	miscDevs.Add(device, device->GetName());
}


/// @brief Deregister misc device object
/// @param device device pointer
void ConcreteDevice::DeregisterMiscDevice(MiscDevice* device)
{
	miscDevs.Remove(device);
}


/// @brief Register plat device object
/// @param device device pointer
void ConcreteDevice::RegisterPlatDevice(PlatDevice* device)
{
	platDevs.Add(device, device->GetName());
}


/// @brief Deregister plat device object
/// @param device device pointer
void ConcreteDevice::DeregisterPlatDevice(PlatDevice* device)
{
	platDevs.Remove(device);
}


/// @brief Register plat driver object
/// @param driver driver pointer
void ConcreteDevice::RegisterPlatDriver(PlatDriver* driver)
{
	platDrvs.Add(driver, driver->GetName());
}


/// @brief Deregister plat device object
/// @param driver driver pointer
void ConcreteDevice::DeregisterPlatDriver(PlatDriver* driver)
{
	platDrvs.Remove(driver);
}


/// @brief Get the device fopts
/// @param name 
/// @return 
Fopts* ConcreteDevice::GetDeviceFopts(const char* name)
{
	Fopts* fopts = NULL;

	fopts = blockDevs.GetItemByName(name);
	if (NULL != fopts) return fopts;

	fopts = charDevs.GetItemByName(name);
	if (NULL != fopts) return fopts;

	fopts = fbDevs.GetItemByName(name);
	if (NULL != fopts) return fopts;

	fopts = miscDevs.GetItemByName(name);
	if (NULL != fopts) return fopts;

	return fopts;
}


/// @brief Get the device name list by driver id
/// @param id 
/// @return 
List<Base*> ConcreteDevice::GetDevices(DriverID id)
{
	if (id >= DriverID::_block && id < DriverID::_dirverIdSize)
	{
		List<Base*> lists[DriverID::_dirverIdSize] = {
			(List<Base*>&)blockDevs, 
			(List<Base*>&)charDevs, 
			(List<Base*>&)fbDevs, 
			(List<Base*>&)ntDevs, 
			(List<Base*>&)miscDevs, 
			(List<Base*>&)platDevs, 
			(List<Base*>&)platDrvs
		};

		return lists[id];
	}
	return List<Base*>();
}
