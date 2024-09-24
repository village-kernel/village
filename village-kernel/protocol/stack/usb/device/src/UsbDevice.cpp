//###########################################################################
// UsbDevice.cpp
// Definitions of the functions that manage usb device
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "UsbDevice.h"


/// @brief Constructor
UsbDevice::UsbDevice()
{
}


/// @brief Destructor
UsbDevice::~UsbDevice()
{
}


/// @brief Setup
void UsbDevice::Setup()
{

}


/// @brief Exit
void UsbDevice::Exit()
{

}


//Register protocol stack
REGISTER_PROTOCOL_STACK(new UsbDevice(), usbDevice);
