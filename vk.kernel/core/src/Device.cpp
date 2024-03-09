//###########################################################################
// Device.cpp
// Definitions of the functions that manage driver
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Device.h"
#include "Driver.h"
#include "Kernel.h"
#include "List.h"


/// @brief ConcreteDevice
class ConcreteDevice : public Device
{
private:
	//Members
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
			drivers[i].body->SetID(drivers[i].id);
			drivers[i].body->SetName(drivers[i].name);
			RegisterDriver(drivers[i].body);
		}
	}
public:
	/// @brief Constructor
	ConcreteDevice()
	{
	}


	/// @brief Destructor
	~ConcreteDevice()
	{
	}


	/// @brief Device Setup
	void Setup()
	{
		RegisterDrivers();
	}


	/// @brief Device Exit
	void Exit()
	{
		drivers.Release();
	}


	/// @brief Register driver object
	/// @param driver driver pointer
	void RegisterDriver(Driver* driver)
	{
		drivers.Insert(driver, driver->GetID(), driver->GetName());
	}
	

	/// @brief Deregister driver object
	/// @param driver driver pointer
	void DeregisterDriver(Driver* driver)
	{
		drivers.Remove(driver);
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


///Register component
REGISTER_COMPONENT(ConcreteDevice, ComponentID::_device, device);
