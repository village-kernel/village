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
#define CREATE_DRIVER(drv, name)        static struct _DRV_##name{_DRV_##name(){drv;}} const _drv_##name;

///Driver register macro
#define REGISTER_DRIVER(drv, id, name)  CREATE_DRIVER(Device::RegisterDriver(drv, id), name)

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
	static void Initialize();
	static void UpdateParams();
	static void Execute();
	static void FailSafe(int arg);
	static void RegisterDriver(Driver* driver, uint32_t id);
	static void DeregisterDriver(Driver* driver, uint32_t id);
	static void GetDriver(Driver* driver, uint32_t id);
};

#endif // !__DEVICE_H__
