 //###########################################################################
// vk_pit32_timer.cpp
// Definitions of the functions that manage pit32 timer
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_pit32_timer.h"
#include "vk_kernel.h"


/// @brief Constructor
Pit32Timer::Pit32Timer()
{
}


/// @brief Destructor
Pit32Timer::~Pit32Timer()
{
}


/// @brief Set dasta
/// @param data 
void Pit32Timer::SetData(void* data)
{
    config = *((Config*)data);

    if (config.timer < 0 || config.timer > 3)
    {
        config.timer = 0;
    }
}


/// @brief Open
bool Pit32Timer::Open()
{
    //uint32_t freq = 1000; //1000hz, 1ms
    //uint32_t divider = 1193182 / freq;
    //uint8_t low  = low_8(divider);
    //uint8_t high = high_8(divider);

    //PortByteOut(TIMERX[config.timer], 0x36); //Command port
    //PortByteOut(TIMERX[config.timer], low);
    //PortByteOut(TIMERX[config.timer], high);
}


/// @brief Close
void Pit32Timer::Close()
{

}


/// @brief Probe
/// @param device 
/// @return 
bool Pit32TimerDrv::Probe(PlatDevice* device)
{
    device->Attach(new Pit32Timer());
    kernel->device.RegisterMiscDevice((MiscDriver*)device->GetDriver());
    return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool Pit32TimerDrv::Remove(PlatDevice* device)
{
    kernel->device.UnregisterMiscDevice((MiscDriver*)device->GetDriver());
    delete (Pit32Timer*)device->GetDriver();
    device->Detach();
    return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new Pit32TimerDrv(), pit32timer, pit32timerDrv);
