//###########################################################################
// Driver.h
// Specifies the interface for all classes that contain driver logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRIVER_INTERFACE_H__
#define __DRIVER_INTERFACE_H__

#include "System.h"

///Driver
class Driver
{
private:
	//Members
	uint32_t ID;
public:
	//Methods
	virtual void Initialize()       {}
	virtual void Execute()          {}
	virtual void UpdateParams()     {}
	virtual void FailSafe(int arg)  {}
	virtual void Write(uint8_t* data, uint16_t size, uint16_t offset) {}
	virtual void Read(uint8_t* data, uint16_t size, uint16_t offset)  {}

	///Set the driver id
	inline void SetID(uint32_t id) { ID = id; }

	///Get the driver id
	inline uint32_t GetID() { return ID; }
};

#endif // !__DRIVER_INTERFACE_H__
