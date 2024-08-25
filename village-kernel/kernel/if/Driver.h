//###########################################################################
// Driver.h
// Specifies the interface for all classes that contain driver logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRIVER_INTERFACE_H__
#define __DRIVER_INTERFACE_H__

#include "Defines.h"
#include "Class.h"


/// @brief Fopts
class Fopts
{
public:
	//Opts methods
	virtual bool Open() = 0;
	virtual int Write(uint8_t* data, uint32_t size = 0, uint32_t offset = 0) { return 0; }
	virtual int Read(uint8_t* data, uint32_t size = 0, uint32_t offset = 0)  { return 0; }
	virtual int IOCtrl(uint8_t cmd, void* data) { return 0; }
	virtual void Close() = 0;
};


/// @brief BlockDevice
class BlockDevice : public Base, public Fopts
{
public:
	//Constructor
	BlockDevice() {}

	//Destructor
	virtual ~BlockDevice() {}
};


/// @brief CharDevice
class CharDevice : public Base, public Fopts
{
public:
	//Constructor
	CharDevice() {}

	//Destructor
	virtual ~CharDevice() {}
};


/// @brief FBDevice
class FBDevice : public Base, public Fopts
{
public:
	//Structures
	struct FBInfo
	{
		uint32_t  width;
		uint32_t  height;
		uint32_t  bitdepth;
	};

	//Members
	FBInfo fbinfo;
public:
	//Constructor
	FBDevice()  {}

	//Destructor
	virtual ~FBDevice() {}

	//Methods
	virtual bool Setup() = 0;
	virtual void DrawPoint(uint32_t x, uint32_t y, uint32_t color) = 0;
	virtual uint32_t ReadPoint(uint32_t x, uint32_t y) = 0;
	virtual void Fill(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color) = 0;
	virtual void Clear(uint32_t color) = 0;
	virtual void Exit() = 0;
};


/// @brief InputDevice
class InputDevice : public Base, public Fopts
{
public:
	//Constructor
	InputDevice() {}

	//Destructor
	virtual ~InputDevice() {}
};


/// @brief NetworkDevice
class NetworkDevice : public Base
{
public:
	//Constructor
	NetworkDevice() {}

	//Destructor
	virtual ~NetworkDevice() {}
};


/// @brief MiscDevice
class MiscDevice : public Base, public Fopts
{
public:
	//Constructor
	MiscDevice() {}

	//Destructor
	virtual ~MiscDevice() {}
};


/// @brief PlatDevice
class PlatDevice : public Base
{
private:
	//Members
	void* driver;
	char* driverName;
	void* driverData;
public:
	//Driver Methods
	void SetDriver(void* driver)   { this->driver = driver; }
	void* GetDriver()              { return this->driver;   }

	//Driver Name Methods
	void SetDriverName(char* name) { this->driverName = name; }
	char* GetDriverName()          { return this->driverName; }

	//Driver Data Methods
	void SetDriverData(void* data) { this->driverData = data; }
	void* GetDriverData()          { return this->driverData; }
public:
	//Constructor
	PlatDevice() {}

	//Destructor
	virtual ~PlatDevice() {}

	//Methods
	virtual void Config()  {};
	virtual void Release() {};
};


/// @brief PlatDriver
class PlatDriver : public Base
{
public:
	//Constructor
	PlatDriver() {}

	//Destructor
	virtual ~PlatDriver() {}

	//Methods
	virtual bool Probe(PlatDevice* device) = 0;
	virtual bool Remove(PlatDevice* device) = 0;
};


#endif // !__DRIVER_INTERFACE_H__
