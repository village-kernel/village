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

///Driver section, avoid being optimized by the compiler
#define DRIVER_SECTION                  __attribute__((used,__section__(".drivers")))

///Driver create macro
#define CREATE_DRIVER(drv, name)        static struct _DRV_##name{_DRV_##name(){drv;}} const _drv_##name

///Driver register macro
#define REGISTER_DRIVER(drv, id, name)  CREATE_DRIVER(Device::Instance().RegisterDriver(drv, id), name) DRIVER_SECTION

///Devic
class Device
{
private:
	//Members
	List<Driver> drivers;

	//Methods
	Device();
	~Device();
public:
	//Methods
	void Initialize();
	void UpdateParams();
	void FailSafe(int arg);
	void RegisterDriver(Driver* driver, uint32_t id);
	void DeregisterDriver(Driver* driver, uint32_t id);
	Driver* GetDriver(uint32_t id);
	Driver* GetDriverByName(const char* name);

	//Singleton Instance
	static Device& Instance();
};

///Declarations device reference
extern Device& device;

#endif // !__DEVICE_H__
