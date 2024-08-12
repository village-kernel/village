//###########################################################################
// Device.h
// Declarations of the functions that manage device
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "Kernel.h"
#include "Driver.h"
#include "List.h"


/// @brief ConcreteDevice
class ConcreteDevice : public Device
{
private:
	/// @brief Members
	List<Driver*> drivers;
public:
	/// @brief Methods
	ConcreteDevice();
	~ConcreteDevice();
	void Setup();
	void Exit();

	/// @brief Register Methods
	void RegisterDriver(Driver* driver);
	void DeregisterDriver(Driver* driver);
	
	/// @brief Data Methods
	Driver* GetDriver(const char* name);
	List<Driver*> GetDrivers(DriverID id);
};

#endif // !__DEVICE_H__
