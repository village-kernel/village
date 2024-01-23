//###########################################################################
// Device.h
// Declarations of the functions that manage device
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "Driver.h"
#include "Templates.h"


/// @brief Devic
class Device
{
private:
	//Members
	States        status;
	List<Driver*> drivers;

	//Methods
	void RegisterInRuntime(Driver* driver);
	void DeregisterInRuntime(Driver* driver);
public:
	//Methods
	Device();
	~Device();
	void Initialize();
	void UpdateParams();
	void Execute();
	void FailSafe(int arg);
	void RegisterDriver(Driver* driver, uint32_t id);
	void DeregisterDriver(Driver* driver, uint32_t id);
	Driver* GetDriver(uint32_t id);
	Driver* GetDriverByName(const char* name);
};

#endif // !__DEVICE_H__
