//###########################################################################
// Device.cpp
// Definitions of the functions that manage driver
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Device.h"
#include "Environment.h"


/// @brief Constructor
Device::Device()
	:isRuntime(false)
{
}


/// @brief Fini constructor
Device::~Device()
{
}


/// @brief Singleton Instance
/// @return Device instance
Device& Device::Instance()
{
	static Device instance;
	return instance;
}
EXPORT_SYMBOL(Device::Instance, _ZN6Device8InstanceEv);


/// @brief Definitions device
Device& device = Device::Instance();
static Device* pdevice = &device;
EXPORT_SYMBOL(pdevice, device);


/// @brief Execute device object->Initialize
void Device::Initialize()
{
	for (Driver* driver = drivers.Begin(); !drivers.IsEnd(); driver = drivers.Next())
	{
		driver->Initialize();
	}
}


/// @brief Execute device object->UpdateParams
void Device::UpdateParams()
{
	for (Driver* driver = drivers.Begin(); !drivers.IsEnd(); driver = drivers.Next())
	{
		driver->UpdateParams();
	}
}


/// @brief Device execute
void Device::Execute()
{
	isRuntime = true;
}


/// @brief Execute device object->FailSafe
void Device::FailSafe(int arg)
{
	for (Driver* driver = drivers.Begin(); !drivers.IsEnd(); driver = drivers.Next())
	{
		driver->FailSafe(arg);
	}
}


/// @brief Register runtime
/// @param module 
void Device::RegisterRuntime(Driver* driver)
{
	if (true == isRuntime)
	{
		driver->Initialize();
		driver->UpdateParams();
	}
}


/// @brief Register driver object
/// @param driver driver pointer
/// @param id driver id
void Device::RegisterDriver(Driver* driver, uint32_t id)
{
	drivers.Insert(driver, id);
	RegisterRuntime(driver);
}
EXPORT_SYMBOL(Device::RegisterDriver, _ZN6Device14RegisterDriverEP6Driverm);



/// @brief Deregister exit
/// @param driver 
void Device::DeregisterExit(Driver* driver)
{
	driver->Exit();
}


/// @brief Deregister driver object
/// @param driver driver pointer
/// @param id driver id
void Device::DeregisterDriver(Driver* driver, uint32_t id)
{
	drivers.Remove(driver, id);
}
EXPORT_SYMBOL(Device::DeregisterDriver, _ZN6Device16DeregisterDriverEP6Driverm);


/// @brief Get the driver object
/// @param id driver id
/// @return driver
Driver* Device::GetDriver(uint32_t id)
{
	return drivers.GetItem(id);
}
EXPORT_SYMBOL(Device::GetDriver, _ZN6Device9GetDriverEm);


/// @brief Get the driver object by name
/// @param name driver name
/// @return driver
Driver* Device::GetDriverByName(const char* name)
{
	return drivers.GetItemByName(name);
}
EXPORT_SYMBOL(Device::GetDriverByName, _ZN6Device15GetDriverByNameEPKc);
