//###########################################################################
// VkEvent.cpp
// Definitions of the functions that manage event
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_event_indev.h"
#include "vk_kernel.h"


/// @brief Text input receiver
void VkEvent::TextReceiver(Event::OutputText* input)
{

}


/// @brief Axis input receiver
void VkEvent::AxisReceiver(Event::OutputAxis* input)
{

}


/// @brief 
/// @return 
void VkEvent::Setup()
{
	//Attach input event
	kernel->event.Attach(Event::_OutputText, (Method)&VkEvent::TextReceiver, this);
	kernel->event.Attach(Event::_OutputAxis, (Method)&VkEvent::AxisReceiver, this);
}


/// @brief 
void VkEvent::Exit()
{
	//Detach input event
	kernel->event.Detach(Event::_OutputText, (Method)&VkEvent::TextReceiver, this);
	kernel->event.Detach(Event::_OutputAxis, (Method)&VkEvent::AxisReceiver, this);
}


/// @brief 
/// @param data 
void VkEvent::Read(IndevData* data)
{

}
