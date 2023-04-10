//###########################################################################
// Device.cpp
// Definitions of the functions that manage driver
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Device.h"
#include "Environment.h"


///Constructor
Device::Device()
{
}


///Singleton instance
Device& Device::Instance()
{
	static Device instance;
	return instance;
}
EXPORT_SYMBOL(Device::Instance, _ZN6Device8InstanceEv);


//Definitions device
Device& device = Device::Instance();
static Device* pdevice = &device;
EXPORT_SYMBOL(pdevice, device);


///Execute device object->Initialize
void Device::Initialize()
{
	for (drivers.Begin(); !drivers.End(); drivers.Next())
	{
		drivers.Item()->Initialize();
	}
}


///Execute device object->UpdateParams
void Device::UpdateParams()
{
	for (drivers.Begin(); !drivers.End(); drivers.Next())
	{
		drivers.Item()->UpdateParams();
	}
}


///Execute device object->FailSafe
void Device::FailSafe(int arg)
{
	for (drivers.Begin(); !drivers.End(); drivers.Next())
	{
		drivers.Item()->FailSafe(arg);
	}
}


///Register driver object
void Device::RegisterDriver(Driver* driver, uint32_t id)
{
	drivers.Insert(driver, id);
}
EXPORT_SYMBOL(Device::RegisterDriver, _ZN6Device14RegisterDriverEP6Driverm);


///Deregister driver object
void Device::DeregisterDriver(Driver* driver, uint32_t id)
{
	drivers.Remove(driver, id);
}
EXPORT_SYMBOL(Device::DeregisterDriver, _ZN6Device16DeregisterDriverEP6Driverm);


///Get the driver object
Driver* Device::GetDriver(uint32_t id)
{
	return drivers.GetItem(id);
}
EXPORT_SYMBOL(Device::GetDriver, _ZN6Device9GetDriverEm);
