//###########################################################################
// Driver.h
// Specifies the interface for all classes that contain driver logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRIVER_INTERFACE_H__
#define __DRIVER_INTERFACE_H__

#include "Defines.h"

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

	//IO ctrl methods
	virtual int Write(uint8_t* data, uint32_t size, uint32_t offset) { return 0; }
	virtual int Read(uint8_t* data, uint32_t size, uint32_t offset)  { return 0; }

	///Set the driver id
	inline void SetID(uint32_t id) { ID = id; }

	///Get the driver id
	inline uint32_t GetID() { return ID; }
};

#endif // !__DRIVER_INTERFACE_H__
