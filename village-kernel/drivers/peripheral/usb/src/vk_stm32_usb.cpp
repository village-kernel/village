 //###########################################################################
// vk_stm32_usb.cpp
// Definitions of the functions that manage stm32 usb
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_stm32_usb.h"
#include "vk_kernel.h"


/// @brief Constructor
Stm32Usb::Stm32Usb()
    :isUsed(false)
{
}


/// @brief Destructor
Stm32Usb::~Stm32Usb()
{
}


/// @brief Set dasta
/// @param data 
void Stm32Usb::SetData(void* data)
{
    config = *((Config*)data);
}


/// @brief Pin config
void Stm32Usb::PinConfig()
{
    Gpio gpio;

    gpio.Initialize(config.dmGpio);
    gpio.Initialize(config.dpGpio);
}


/// @brief UsbHandler
void Stm32Usb::UsbHandler()
{
    usb.IRQHandler();
}


/// @brief Open
bool Stm32Usb::Open()
{
    //Return when is used
    if (isUsed) return true;
    
    //Pin config
    PinConfig();

    //Configure usb
    usb.Initialize();
    usb.ConfigRxFifo(0x80);
    usb.ConfigTxFifo(0, 0x40);
    usb.ConfigTxFifo(1, 0x80);
    usb.Start();

    //Configure nvic
    nvic.Initialize((IRQn_Type)config.irq);
    nvic.SetPriority(0, 0);
    nvic.EnableInterrupt();

    //Set interrupt serivces
    kernel->interrupt.SetISR(config.irq, (Method)(&Stm32Usb::UsbHandler), this);
    
    //Set isUsed flag
    isUsed = true;

    return true;
}


/// @brief Close
void Stm32Usb::Close()
{
    kernel->interrupt.RemoveISR(config.irq, (Method)(&Stm32Usb::UsbHandler), this);

    isUsed = false;
}


/// @brief Probe
/// @param device 
/// @return 
bool Stm32UsbDrv::Probe(PlatDevice* device)
{
    device->Attach(new Stm32Usb());
    kernel->device.RegisterCharDevice((CharDriver*)device->GetDriver());
    return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool Stm32UsbDrv::Remove(PlatDevice* device)
{
    kernel->device.UnregisterCharDevice((CharDriver*)device->GetDriver());
    delete (Stm32Usb*)device->GetDriver();
    device->Detach();
    return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new Stm32UsbDrv(), stm32Usb, stm32UsbDrv);
