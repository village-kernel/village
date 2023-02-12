//###########################################################################
// Device.h
// Declarations of the functions that manage device
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "Driver.h"

///Driver create macro
#define CREATE_DRIVER(drv)        static struct DRV{DRV(){drv;}} const drv;

///Driver register macro
#define REGISTER_MODULE(drv, id)  CREATE_DRIVER(Device::RegisterDriver(drv, id))

///Device
class Device
{
private:
	//Structures
	struct DriverNode
	{
		Driver* driver;
		DriverNode* next;

		DriverNode(Driver* driver = NULL) :
			driver(driver),
			next(NULL)
		{}
	};

	//Members
	static DriverNode* list;
public:
	//Methods
	Device();
	static void RegisterDriver(Driver* driver, uint32_t id);
	static void DeregisterDriver(Driver* driver, uint32_t id);
	static void GetDriver(Driver* driver, uint32_t id);
};

#endif // !__DEVICE_H__
