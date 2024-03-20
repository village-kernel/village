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
