//###########################################################################
// Device.h
// Declarations of the functions that manage device
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "Component.h"
#include "Driver.h"


/// @brief Devic
class Device : public Component
{
public:
	//Methods
	virtual void RegisterDriver(Driver* driver) = 0;
	virtual void DeregisterDriver(Driver* driver) = 0;
	virtual Driver* GetDriver(uint32_t id) = 0;
	virtual Driver* GetDriver(const char* name) = 0;
};

#endif // !__DEVICE_H__
