//###########################################################################
// Driver.h
// Specifies the interface for all classes that contain driver logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRIVER_INTERFACE_H__
#define __DRIVER_INTERFACE_H__

#include "Defines.h"
#include "Templates.h"

///Driver
class Driver : public Class
{
public:
	//Constructor
	Driver()  {}

	//Deconstructor
	virtual ~Driver() {}

	//Methods
	virtual void Initialize()       {}
	virtual void UpdateParams()     {}
	virtual void Execute()          {}
	virtual void FailSafe(int arg)  {}

	//IO ctrl methods
	virtual int Write(uint8_t* data, uint32_t size = 0, uint32_t offset = 0) { return 0; }
	virtual int Read(uint8_t* data, uint32_t size = 0, uint32_t offset = 0)  { return 0; }
	virtual int IOCtrl(uint8_t cmd, void* data) { return 0; }
};

#endif // !__DRIVER_INTERFACE_H__
