//###########################################################################
// vk_signal.cpp
// Definitions of the functions that manage signal
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_signal.h"


/// @brief Constructor
ConcreteSignal::ConcreteSignal()
{
}


/// @brief Destructor
ConcreteSignal::~ConcreteSignal()
{
}


/// @brief Signal setup
void ConcreteSignal::Setup()
{
    //Output debug info
    kernel->debug.Info("Signal setup done!");
}


/// @brief Signal exit
void ConcreteSignal::Exit()
{

}


/// @brief Raising
/// @param signal 
void ConcreteSignal::Raising(int signal)
{
    kernel->system.DisableIRQ();

    switch (signal)
    {
        case Signals::_Sleep: 
            kernel->system.Sleep();
            break;
        
        case Signals::_Standby:
            kernel->system.Standby();
            break;

        case Signals::_Shutdown:
            kernel->Exit();
            kernel->system.Shutdown();
            break;

        case Signals::_Reboot:
            kernel->Exit();
            kernel->system.Reboot();
            break;
        
        default: break;
    };

    kernel->system.EnableIRQ();
}
