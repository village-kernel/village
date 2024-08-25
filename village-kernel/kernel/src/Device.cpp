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
	//Platform probe
	PlatformProbe();

	//Input device setup
	InputDevSetup();

	//Output debug info
	kernel->debug.Info("Device setup done!");
}


/// @brief Device Exit
void ConcreteDevice::Exit()
{
	//Input device exit
	InputDevExit();

	//Platform remove
	PlatformRemove();

	//Release devices
	DevicesRelease();
}


/// @brief Platform match
/// @param device 
/// @return 
PlatDriver* ConcreteDevice::PlatformMatch(PlatDevice* device)
{
	return platDrvs.GetItemByName(device->GetName());
}


/// @brief Platform probe
void ConcreteDevice::PlatformProbe()
{
	for (platDevs.Begin(); !platDevs.IsEnd(); platDevs.Next())
	{
		PlatDevice* device = platDevs.Item();
		PlatDriver* driver = PlatformMatch(device);
		
		if (NULL != driver)
		{
			device->Config();
			
			if (!driver->Probe(device))
			{
				device->Release();
			}
		}
	}
}


/// @brief Platform remove
void ConcreteDevice::PlatformRemove()
{
	for (platDevs.End(); !platDevs.IsBegin(); platDevs.Prev())
	{
		PlatDevice* device = platDevs.Item();
		PlatDriver* driver = PlatformMatch(device);
	
		if (NULL != driver)
		{
			driver->Remove(device);
			device->Release();
		}
	}
}


/// @brief Input device setup
void ConcreteDevice::InputDevSetup()
{
	for (inDevs.Begin(); !inDevs.IsEnd(); inDevs.Next())
	{
		inDevs.Item()->Open();
	}
}


/// @brief Input device exit
void ConcreteDevice::InputDevExit()
{
	for (inDevs.End(); !inDevs.IsBegin(); inDevs.Prev())
	{
		inDevs.Item()->Close();
	}
}


/// @brief Release devices
void ConcreteDevice::DevicesRelease()
{
	blockDevs.Release();
	charDevs.Release();
	fbDevs.Release();
	inDevs.Release();
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


/// @brief Unregister block device object
/// @param device device pointer
void ConcreteDevice::UnregisterBlockDevice(BlockDevice* device)
{
	blockDevs.Remove(device);
}


/// @brief Register char device object
/// @param device device pointer
void ConcreteDevice::RegisterCharDevice(CharDevice* device)
{
	charDevs.Add(device, device->GetName());
}


/// @brief Unregister char device object
/// @param device device pointer
void ConcreteDevice::UnregisterCharDevice(CharDevice* device)
{
	charDevs.Remove(device);
}


/// @brief Register fb device object
/// @param device device pointer
void ConcreteDevice::RegisterFBDevice(FBDevice* device)
{
	fbDevs.Add(device, device->GetName());
}


/// @brief Unregister fb device object
/// @param device device pointer
void ConcreteDevice::UnregisterFBDevice(FBDevice* device)
{
	fbDevs.Remove(device);
}


/// @brief Register input device object
/// @param device device pointer
void ConcreteDevice::RegisterInputDevice(InputDevice* device)
{
	inDevs.Add(device, device->GetName());
}


/// @brief Unregister input device object
/// @param device device pointer
void ConcreteDevice::UnregisterInputDevice(InputDevice* device)
{
	inDevs.Remove(device);
}


/// @brief Register nt device object
/// @param device device pointer
void ConcreteDevice::RegisterNetworkDevice(NetworkDevice* device)
{
	ntDevs.Add(device, device->GetName());
}


/// @brief Unregister nt device object
/// @param device device pointer
void ConcreteDevice::UnregisterNetworkDevice(NetworkDevice* device)
{
	ntDevs.Remove(device);
}


/// @brief Register misc device object
/// @param device device pointer
void ConcreteDevice::RegisterMiscDevice(MiscDevice* device)
{
	miscDevs.Add(device, device->GetName());
}


/// @brief Unregister misc device object
/// @param device device pointer
void ConcreteDevice::UnregisterMiscDevice(MiscDevice* device)
{
	miscDevs.Remove(device);
}


/// @brief Register plat device object
/// @param device device pointer
void ConcreteDevice::RegisterPlatDevice(PlatDevice* device)
{
	platDevs.Add(device, device->GetName());
}


/// @brief Unregister plat device object
/// @param device device pointer
void ConcreteDevice::UnregisterPlatDevice(PlatDevice* device)
{
	platDevs.Remove(device);
}


/// @brief Register plat driver object
/// @param driver driver pointer
void ConcreteDevice::RegisterPlatDriver(PlatDriver* driver)
{
	platDrvs.Add(driver, driver->GetName());
}


/// @brief Unregister plat device object
/// @param driver driver pointer
void ConcreteDevice::UnregisterPlatDriver(PlatDriver* driver)
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
			(List<Base*>&)inDevs,
			(List<Base*>&)ntDevs,
			(List<Base*>&)miscDevs,
			(List<Base*>&)platDevs,
			(List<Base*>&)platDrvs
		};

		return lists[id];
	}
	return List<Base*>();
}
