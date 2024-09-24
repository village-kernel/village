//###########################################################################
// UsbHost.cpp
// Definitions of the functions that manage usb host
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "UsbHost.h"


/// @brief Constructor
UsbHost::UsbHost()
{
}


/// @brief Destructor
UsbHost::~UsbHost()
{
}


/// @brief Setup
void UsbHost::Setup()
{

}


/// @brief Exit
void UsbHost::Exit()
{

}


//Register protocol stack
REGISTER_PROTOCOL_STACK(new UsbHost(), usbHost);
