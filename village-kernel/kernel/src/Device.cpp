//###########################################################################
// Device.cpp
// Definitions of the functions that manage driver
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Device.h"


/// @brief Constructor
ConcreteDevice::ConcreteDevice()
	:isRuntime(false)
{
}


/// @brief Destructor
ConcreteDevice::~ConcreteDevice()
{
}


/// @brief Device Setup
void ConcreteDevice::Setup()
{
	//Clear flag
	isRuntime = false;

	//Platform probe
	PlatformProbe();

	//Input device setup
	InputDevSetup();

	//Set flag
	isRuntime = true;

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
/// @param driver 
/// @return 
inline bool ConcreteDevice::PlatformMatch(PlatDevice* device, PlatDriver* driver)
{
	return (0 == strcmp(device->GetName(), driver->GetName()));
}


/// @brief Platform probe
/// @param device 
/// @param driver 
/// @return 
inline bool ConcreteDevice::PlatformProbe(PlatDevice* device, PlatDriver* driver)
{
	if (PlatformMatch(device, driver))
	{
		if (NULL == device->GetDriver())
		{
			device->Config();
	
			if (!driver->Probe(device))
			{
				device->Release();
			}
		}
		return true;
	}
	return false;
}


/// @brief Platform remove
/// @param device 
/// @param driver 
/// @return 
inline bool ConcreteDevice::PlatformRemove(PlatDevice* device, PlatDriver* driver)
{
	if (PlatformMatch(device, driver))
	{
		if (NULL != device->GetDriver())
		{
			driver->Remove(device);
			device->Release();
		}
		return true;
	}
	return false;
}


/// @brief Platform device probe
/// @param driver 
inline void ConcreteDevice::PlatformDeviceProbe(PlatDriver* driver)
{
	for (platDevs.Begin(); !platDevs.IsEnd(); platDevs.Next())
	{
		PlatformProbe(platDevs.Item(), driver);
	}
}


/// @brief Platform device remove
/// @param driver 
inline void ConcreteDevice::PlatformDeviceRemove(PlatDriver* driver)
{
	for (platDevs.Begin(); !platDevs.IsEnd(); platDevs.Next())
	{
		PlatformRemove(platDevs.Item(), driver);
	}
}


/// @brief Platform driver probe
/// @param device 
inline void ConcreteDevice::PlatformDriverProbe(PlatDevice* device)
{
	for (platDrvs.Begin(); !platDrvs.IsEnd(); platDrvs.Next())
	{
		if (PlatformProbe(device, platDrvs.Item())) break;
	}
}


/// @brief Platform driver remove
/// @param device 
inline void ConcreteDevice::PlatformDriverRemove(PlatDevice* device)
{
	for (platDrvs.Begin(); !platDrvs.IsEnd(); platDrvs.Next())
	{
		if (PlatformRemove(device, platDrvs.Item())) break;
	}
}


/// @brief Platform probe
inline void ConcreteDevice::PlatformProbe()
{
	for (platDevs.Begin(); !platDevs.IsEnd(); platDevs.Next())
	{
		PlatformDriverProbe(platDevs.Item());
	}
}


/// @brief Platform remove
inline void ConcreteDevice::PlatformRemove()
{
	for (platDevs.End(); !platDevs.IsBegin(); platDevs.Prev())
	{
		PlatformDriverRemove(platDevs.Item());
	}
}


/// @brief Input device setup
inline void ConcreteDevice::InputDevSetup()
{
	for (inDevs.Begin(); !inDevs.IsEnd(); inDevs.Next())
	{
		inDevs.Item()->Open();
	}
}


/// @brief Input device exit
inline void ConcreteDevice::InputDevExit()
{
	for (inDevs.End(); !inDevs.IsBegin(); inDevs.Prev())
	{
		inDevs.Item()->Close();
	}
}


/// @brief Release devices
inline void ConcreteDevice::DevicesRelease()
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
/// @param driver driver pointer
void ConcreteDevice::RegisterBlockDevice(BlockDriver* driver)
{
	blockDevs.Add(driver, driver->GetName());
	if (isRuntime) kernel->filesys.MountHardDrive(driver->GetName());
}


/// @brief Unregister block device object
/// @param driver driver pointer
void ConcreteDevice::UnregisterBlockDevice(BlockDriver* driver)
{
	if (isRuntime) kernel->filesys.UnmountHardDrive(driver->GetName());
	blockDevs.Remove(driver);
}


/// @brief Register char device object
/// @param driver driver pointer
void ConcreteDevice::RegisterCharDevice(CharDriver* driver)
{
	charDevs.Add(driver, driver->GetName());
}


/// @brief Unregister char device object
/// @param driver driver pointer
void ConcreteDevice::UnregisterCharDevice(CharDriver* driver)
{
	charDevs.Remove(driver);
}


/// @brief Register fb device object
/// @param driver driver pointer
void ConcreteDevice::RegisterFBDevice(FBDriver* driver)
{
	fbDevs.Add(driver, driver->GetName());
}


/// @brief Unregister fb device object
/// @param driver driver pointer
void ConcreteDevice::UnregisterFBDevice(FBDriver* driver)
{
	fbDevs.Remove(driver);
}


/// @brief Register input device object
/// @param driver device pointer
void ConcreteDevice::RegisterInputDevice(InputDriver* driver)
{
	inDevs.Add(driver, driver->GetName());
	if (isRuntime) driver->Open();
}


/// @brief Unregister input device object
/// @param driver driver pointer
void ConcreteDevice::UnregisterInputDevice(InputDriver* driver)
{
	if (isRuntime) driver->Close();
	inDevs.Remove(driver);
}


/// @brief Register nt device object
/// @param driver driver pointer
void ConcreteDevice::RegisterNetworkDevice(NetworkDriver* driver)
{
	ntDevs.Add(driver, driver->GetName());
}


/// @brief Unregister nt device object
/// @param driver driver pointer
void ConcreteDevice::UnregisterNetworkDevice(NetworkDriver* driver)
{
	ntDevs.Remove(driver);
}


/// @brief Register misc device object
/// @param driver driver pointer
void ConcreteDevice::RegisterMiscDevice(MiscDriver* driver)
{
	miscDevs.Add(driver, driver->GetName());
}


/// @brief Unregister misc device object
/// @param driver driver pointer
void ConcreteDevice::UnregisterMiscDevice(MiscDriver* driver)
{
	miscDevs.Remove(driver);
}


/// @brief Register plat device object
/// @param device device pointer
void ConcreteDevice::RegisterPlatDevice(PlatDevice* device)
{
	platDevs.Add(device, device->GetName());
	if (isRuntime) PlatformDriverProbe(device);
}


/// @brief Unregister plat device object
/// @param device device pointer
void ConcreteDevice::UnregisterPlatDevice(PlatDevice* device)
{
	if (isRuntime) PlatformDriverRemove(device);
	platDevs.Remove(device);
}


/// @brief Register plat driver object
/// @param driver driver pointer
void ConcreteDevice::RegisterPlatDriver(PlatDriver* driver)
{
	platDrvs.Add(driver, driver->GetName());
	if (isRuntime) PlatformDeviceProbe(driver);
}


/// @brief Unregister plat device object
/// @param driver driver pointer
void ConcreteDevice::UnregisterPlatDriver(PlatDriver* driver)
{
	if (isRuntime) PlatformDeviceRemove(driver);
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
