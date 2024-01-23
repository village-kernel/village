//###########################################################################
// Device.cpp
// Definitions of the functions that manage driver
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Device.h"
#include "Kernel.h"


/// @brief Constructor
Device::Device()
	:status(_NoneStates)
{
}


/// @brief Fini constructor
Device::~Device()
{
}


/// @brief Execute device object->Initialize
void Device::Initialize()
{
	status = _StartInitialize;
	for (Driver* driver = drivers.Begin(); !drivers.IsEnd(); driver = drivers.Next())
	{
		driver->Initialize();
	}
	status = _EndedInitialize;
}


/// @brief Execute device object->UpdateParams
void Device::UpdateParams()
{
	status = _StartUpdateParams;
	for (Driver* driver = drivers.Begin(); !drivers.IsEnd(); driver = drivers.Next())
	{
		driver->UpdateParams();
	}
	status = _EndedUpdateParms;
}


/// @brief Device execute
void Device::Execute()
{
	status = _StartExecute;
	status = _EndedExecute;
}


/// @brief Execute device object->FailSafe
void Device::FailSafe(int arg)
{
	for (Driver* driver = drivers.Begin(); !drivers.IsEnd(); driver = drivers.Next())
	{
		driver->FailSafe(arg);
	}
}


/// @brief Register in runtime
/// @param module 
void Device::RegisterInRuntime(Driver* driver)
{
	if (status >= _EndedInitialize)
		driver->Initialize();
	if (status >= _EndedUpdateParms)
		driver->UpdateParams();
}


/// @brief Deregister in runtime
/// @param driver 
void Device::DeregisterInRuntime(Driver* driver)
{
	if (status >= _EndedExecute)
	{
		driver->Exit();
	}
}


/// @brief Register driver object
/// @param driver driver pointer
/// @param id driver id
void Device::RegisterDriver(Driver* driver, uint32_t id)
{
	drivers.Insert(driver, id, driver->GetName());
	RegisterInRuntime(driver);
}
EXPORT_SYMBOL(_ZN6Device14RegisterDriverEP6Driverm);


/// @brief Deregister driver object
/// @param driver driver pointer
/// @param id driver id
void Device::DeregisterDriver(Driver* driver, uint32_t id)
{
	DeregisterInRuntime(driver);
	drivers.Remove(driver, id);
}
EXPORT_SYMBOL(_ZN6Device16DeregisterDriverEP6Driverm);


/// @brief Get the driver object
/// @param id driver id
/// @return driver
Driver* Device::GetDriver(uint32_t id)
{
	return drivers.GetItem(id);
}
EXPORT_SYMBOL(_ZN6Device9GetDriverEm);


/// @brief Get the driver object by name
/// @param name driver name
/// @return driver
Driver* Device::GetDriver(const char* name)
{
	return drivers.GetItemByName(name);
}
EXPORT_SYMBOL(_ZN6Device9GetDriverEPKc);
