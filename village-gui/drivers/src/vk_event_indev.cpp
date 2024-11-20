//###########################################################################
// VkEvent.cpp
// Definitions of the functions that manage event
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_event_indev.h"
#include "vk_event_codes.h"
#include "vk_kernel.h"


/// @brief 
/// @return 
void VkEvent::Setup()
{
	//Attach input event
	kernel->event.Attach(Event::_InputKey,  (Method)&VkEvent::KeyReceiver, this);
	kernel->event.Attach(Event::_InputAxis, (Method)&VkEvent::AxisReceiver, this);
}


/// @brief 
void VkEvent::Exit()
{
	//Detach input event
	kernel->event.Detach(Event::_InputKey,  (Method)&VkEvent::KeyReceiver, this);
	kernel->event.Detach(Event::_InputAxis, (Method)&VkEvent::AxisReceiver, this);
}


/// @brief key input receiver
void VkEvent::KeyReceiver(Event::InputKey* input)
{
	//Get the current key
	data.key = input->code;

	//Get whether the keyboard button is pressed or released
	if(KeyStatus::_KeyPressed == input->status)
		data.state = KeyState::_Pressed;
	else
		data.state = KeyState::_Pressed;
}


/// @brief Axis input receiver
void VkEvent::AxisReceiver(Event::InputAxis* input)
{
	static Point point;

	//Get the current x and y coordinates
	point.x += input->axisX;
	point.y -= input->axisY;

	//Update point x
	if (point.x < 0) 
		point.x = 0;
	else if (point.x > 1024)
		point.x = 1024;

	//Update point y
	if (point.y < 0)
		point.y = 0;
	else if (point.y > 768)
		point.y = 768;

	//Set the data point
	data.point = point;
}


/// @brief Read
IndevData VkEvent::Read()
{
	return data;
}
