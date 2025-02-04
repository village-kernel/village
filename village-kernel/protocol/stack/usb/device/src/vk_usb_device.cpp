//###########################################################################
// vk_usb_device.cpp
// Definitions of the functions that manage usb device
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_usb_device.h"


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
    usb.Open("usb0");
}


/// @brief Exit
void UsbDevice::Exit()
{

}


//Register protocol stack
REGISTER_PROTOCOL_STACK(new UsbDevice(), usbDevice);
