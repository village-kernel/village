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

/// @brief Driver
class Driver : public Class
{
private:
	//Members
	char* name;   //driver name
public:
	//Constructor
	Driver()  {}

	//Destructor
	virtual ~Driver() {}

	//Methods
	virtual void Initialize()       {}
	virtual void UpdateParams()     {}
	virtual void Execute()          {}
	virtual void FailSafe(int arg)  {}
	virtual void Exit()             {}
	virtual void SetName(char* name){ this->name = name; }
	virtual char* GetName()         { return this->name; }

	//IO ctrl methods
	virtual int Write(uint8_t* data, uint32_t size = 0, uint32_t offset = 0) { return 0; }
	virtual int Read(uint8_t* data, uint32_t size = 0, uint32_t offset = 0)  { return 0; }
	virtual void* IOCtrl(uint8_t cmd, ...) { return 0; }
};


/// @brief FBDriver
class FBDriver
{
public:
	//Structures
	struct DeviceInfo
	{
		uint32_t  width;
		uint32_t  height;
		uint32_t  bitdepth;
	};

	//Members
	DeviceInfo device;
public:
	//Constructor
	FBDriver()  {}

	//Destructor
	virtual ~FBDriver() {}

	//Methods
	virtual void DrawPoint(uint32_t x, uint32_t y, uint32_t color) = 0;
	virtual uint32_t ReadPoint(uint32_t x, uint32_t y) = 0;
	virtual void Fill(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color) = 0;
	virtual void Clear(uint32_t color) = 0;
};

#endif // !__DRIVER_INTERFACE_H__
