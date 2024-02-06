//###########################################################################
// Device.cpp
// Definitions of the functions that manage driver
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Device.h"
#include "Driver.h"
#include "Kernel.h"
#include "Templates.h"


/// @brief ConcreteDevice
class ConcreteDevice : public Device
{
private:
	//Members
	States        status;
	List<Driver*> drivers;
private:
	/// @brief Register drivers
	void RegisterDrivers()
	{
		extern DriverInfo __drivers_start;
		extern DriverInfo __drivers_end;

		uint32_t count = &__drivers_end - &__drivers_start;
		DriverInfo* drivers = &__drivers_start;

		for (uint32_t i = 0; i < count; i++)
		{
			drivers[i].driver->SetName(drivers[i].name);
			RegisterDriver(drivers[i].driver, drivers[i].id);
		}
	}


	/// @brief Register in runtime
	/// @param module 
	void RegisterInRuntime(Driver* driver)
	{
		if (status >= _EndedInitialize)
			driver->Initialize();
		if (status >= _EndedUpdateParms)
			driver->UpdateParams();
	}


	/// @brief Deregister in runtime
	/// @param driver 
	void DeregisterInRuntime(Driver* driver)
	{
		if (status >= _EndedExecute)
		{
			driver->Exit();
		}
	}
public:
	/// @brief Constructor
	ConcreteDevice()
		:status(_NoneStates)
	{
	}


	/// @brief Destructor
	~ConcreteDevice()
	{
	}


	/// @brief Execute device object->Initialize
	void Initialize()
	{
		RegisterDrivers();

		status = _StartInitialize;
		for (Driver* driver = drivers.Begin(); !drivers.IsEnd(); driver = drivers.Next())
		{
			driver->Initialize();
		}
		status = _EndedInitialize;
	}


	/// @brief Execute device object->UpdateParams
	void UpdateParams()
	{
		status = _StartUpdateParams;
		for (Driver* driver = drivers.Begin(); !drivers.IsEnd(); driver = drivers.Next())
		{
			driver->UpdateParams();
		}
		status = _EndedUpdateParms;
	}


	/// @brief Device execute
	void Execute()
	{
		status = _StartExecute;
		status = _EndedExecute;
	}


	/// @brief Execute device object->FailSafe
	void FailSafe(int arg)
	{
		for (Driver* driver = drivers.Begin(); !drivers.IsEnd(); driver = drivers.Next())
		{
			driver->FailSafe(arg);
		}
	}


	/// @brief Register driver object
	/// @param driver driver pointer
	/// @param id driver id
	void RegisterDriver(Driver* driver, uint32_t id)
	{
		drivers.Insert(driver, id, driver->GetName());
		RegisterInRuntime(driver);
	}
	

	/// @brief Deregister driver object
	/// @param driver driver pointer
	/// @param id driver id
	void DeregisterDriver(Driver* driver, uint32_t id)
	{
		DeregisterInRuntime(driver);
		drivers.Remove(driver, id);
	}


	/// @brief Get the driver object
	/// @param id driver id
	/// @return driver
	Driver* GetDriver(uint32_t id)
	{
		return drivers.GetItem(id);
	}


	/// @brief Get the driver object by name
	/// @param name driver name
	/// @return driver
	Driver* GetDriver(const char* name)
	{
		return drivers.GetItemByName(name);
	}
};


///Register module
REGISTER_MODULE(ConcreteDevice, ModuleID::_device, device);
