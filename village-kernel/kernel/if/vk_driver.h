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
    BlockDriver() { SetID(DriverID::_block); }

    //Destructor
    virtual ~BlockDriver() {}
};


/// @brief CharDriver
class CharDriver : public Base, public Fopts
{
public:
    //Constructor
    CharDriver() { SetID(DriverID::_character); }

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
    FBDriver()  { SetID(DriverID::_framebuffer); }

    //Destructor
    virtual ~FBDriver() {}

    //Methods
    virtual bool Setup() = 0;
    virtual void DrawPoint(uint32_t x, uint32_t y, uint32_t color) = 0;
    virtual uint32_t ReadPoint(uint32_t x, uint32_t y) = 0;
    virtual void Fill(uint32_t sx, uint32_t sy, uint32_t ex, uint32_t ey, uint32_t color) = 0;
    virtual void Clear(uint32_t color) = 0;
    virtual void Exit() = 0;
};


/// @brief InputDriver
class InputDriver : public Base, public Fopts
{
public:
    //Constructor
    InputDriver() { SetID(DriverID::_input); }

    //Destructor
    virtual ~InputDriver() {}
};


/// @brief NetworkDriver
class NetworkDriver : public Base
{
public:
    //Constructor
    NetworkDriver() { SetID(DriverID::_network); }

    //Destructor
    virtual ~NetworkDriver() {}
};


/// @brief MiscDriver
class MiscDriver : public Base, public Fopts
{
public:
    //Constructor
    MiscDriver() { SetID(DriverID::_miscellaneous); }

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
    /// @brief Attach
    /// @param driver 
    void Attach(void* driver)
    {
        this->driver = driver;
        ((Base*)driver)->SetName(driverName);
        ((Base*)driver)->SetData(driverData);
    }

    /// @brief Detach
    void Detach()
    {
        driver = NULL;
    }

    /// @brief GetDriver
    /// @return 
    void* GetDriver()
    {
        return driver;
    }
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
