//###########################################################################
// vk_sdram_w9825g6.cpp
// Definitions of the functions that manage sdram w9825g6
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_sdram_w9825g6.h"


/// @brief Constructor
W9825G6::W9825G6()
{
}


/// @brief Destructor
W9825G6::~W9825G6()
{
}


/// @brief SetData
/// @param data 
void W9825G6::SetData(void * data)
{
    config = *((Config*)data);
}


/// @brief PinConfig
void W9825G6::PinConfig()
{
    Gpio pin;
    pin.Initialize(config.ckeGpio);
    pin.Initialize(config.clkGpio);
    pin.Initialize(config.casGpio);
    pin.Initialize(config.rasGpio);
    pin.Initialize(config.weGpio);
    pin.Initialize(config.csGpio);

    pin.Initialize(config.ba0Gpio);
    pin.Initialize(config.ba1Gpio);
    pin.Initialize(config.bl0Gpio);
    pin.Initialize(config.bl1Gpio);

    pin.Initialize(config.a0Gpio);
    pin.Initialize(config.a1Gpio);
    pin.Initialize(config.a2Gpio);
    pin.Initialize(config.a3Gpio);
    pin.Initialize(config.a4Gpio);
    pin.Initialize(config.a5Gpio);
    pin.Initialize(config.a6Gpio);
    pin.Initialize(config.a7Gpio);
    pin.Initialize(config.a8Gpio);
    pin.Initialize(config.a9Gpio);
    pin.Initialize(config.a10Gpio);
    pin.Initialize(config.a11Gpio);
    pin.Initialize(config.a12Gpio);

    pin.Initialize(config.db0Gpio);
    pin.Initialize(config.db1Gpio);
    pin.Initialize(config.db2Gpio);
    pin.Initialize(config.db3Gpio);
    pin.Initialize(config.db4Gpio);
    pin.Initialize(config.db5Gpio);
    pin.Initialize(config.db6Gpio);
    pin.Initialize(config.db7Gpio);
    pin.Initialize(config.db8Gpio);
    pin.Initialize(config.db9Gpio);
    pin.Initialize(config.db10Gpio);
    pin.Initialize(config.db11Gpio);
    pin.Initialize(config.db12Gpio);
    pin.Initialize(config.db13Gpio);
    pin.Initialize(config.db14Gpio);
    pin.Initialize(config.db15Gpio);
}


/// @brief Open
/// @return 
bool W9825G6::Open()
{
    PinConfig();

    sdram.Initialize();
    sdram.InitSequece();
    sdram.ConfigRefreshRate(839);

    uint8_t writebuff[100] = { 0 };
    uint8_t readbuff[100] = { 0 };

    for (int i = 0; i < 100; i++)
    {
        writebuff[i] = i;
    }

    sdram.Write(writebuff, 100, 0);
    sdram.Read(readbuff, 100, 0);

    return true;
}


/// @brief Close
void W9825G6::Close()
{

}


/// @brief Probe
/// @param device 
/// @return 
bool W9825G6Drv::Probe(PlatDevice* device)
{
    device->Attach(new W9825G6());
    kernel->device.RegisterCharDevice((CharDriver*)device->GetDriver());
    ((CharDriver*)device->GetDriver())->Open();
    return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool W9825G6Drv::Remove(PlatDevice* device)
{
    ((CharDriver*)device->GetDriver())->Close();
    kernel->device.UnregisterCharDevice((CharDriver*)device->GetDriver());
    delete (W9825G6*)device->GetDriver();
    device->Detach();
    return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new W9825G6Drv(), w9825g6, w9825g6Drv);
