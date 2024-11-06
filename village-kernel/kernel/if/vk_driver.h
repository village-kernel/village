//###########################################################################
// vk_driver.h
// Specifies the interface for all classes that contain driver logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRIVER_INTERFACE_H__
#define __VK_DRIVER_INTERFACE_H__

#include "vk_defines.h"
#include "vk_class.h"


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


/// @brief BlockDriver
class BlockDriver : public Base, public Fopts
{
public:
	//Constructor
	BlockDriver() {}

	//Destructor
	virtual ~BlockDriver() {}
};


/// @brief CharDriver
class CharDriver : public Base, public Fopts
{
public:
	//Constructor
	CharDriver() {}

	//Destructor
	virtual ~CharDriver() {}
};


/// @brief FBDriver
class FBDriver : public Base, public Fopts
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
	FBInfo info;
public:
	//Constructor
	FBDriver()  {}

	//Destructor
	virtual ~FBDriver() {}

	//Methods
	virtual bool Setup() = 0;
	virtual void DrawPoint(uint32_t x, uint32_t y, uint32_t color) = 0;
	virtual uint32_t ReadPoint(uint32_t x, uint32_t y) = 0;
	virtual void Fill(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color) = 0;
	virtual void Clear(uint32_t color) = 0;
	virtual void Exit() = 0;
};


/// @brief InputDriver
class InputDriver : public Base, public Fopts
{
public:
	//Constructor
	InputDriver() {}

	//Destructor
	virtual ~InputDriver() {}
};


/// @brief NetworkDriver
class NetworkDriver : public Base
{
public:
	//Constructor
	NetworkDriver() {}

	//Destructor
	virtual ~NetworkDriver() {}
};


/// @brief MiscDriver
class MiscDriver : public Base, public Fopts
{
public:
	//Constructor
	MiscDriver() {}

	//Destructor
	virtual ~MiscDriver() {}
};


/// @brief PlatDevice
class PlatDevice : public Base
{
protected:
	//Members
	void* driver;
	void* driverData;
	char* driverName;
public:
	//Driver Methods, platform driver using
	void  SetDriver(void* driver)  { this->driver = driver; }
	void* GetDriver()              { return this->driver;   }
	void* GetDriverData()          { return this->driverData; }
	char* GetDriverName()          { return this->driverName; }
public:
	//Constructor
	PlatDevice() :driver(NULL), driverData(NULL), driverName(NULL) {}

	//Destructor
	virtual ~PlatDevice() {}

	//Methods
	virtual void Config()  {}
	virtual void Release() {}
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


#endif // !__VK_DRIVER_INTERFACE_H__
