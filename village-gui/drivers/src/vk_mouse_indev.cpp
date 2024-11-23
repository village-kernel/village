//###########################################################################
// vk_mouse_indev.cpp
// Definitions of the functions that manage mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_mouse_indev.h"
#include "vk_event_codes.h"
#include "vk_kernel.h"


/// @brief Setup
void VkMouse::Setup()
{
	//Set indev type
	SetType(IndevType::_Mouse);

	//Attach input event
	kernel->event.Attach(Event::_InputKey,  (Method)&VkMouse::KeyReceiver, this);
	kernel->event.Attach(Event::_InputAxis, (Method)&VkMouse::AxisReceiver, this);
}


/// @brief Exit
void VkMouse::Exit()
{
	//Detach input event
	kernel->event.Detach(Event::_InputKey,  (Method)&VkMouse::KeyReceiver, this);
	kernel->event.Detach(Event::_InputAxis, (Method)&VkMouse::AxisReceiver, this);
}


/// @brief key input receiver
void VkMouse::KeyReceiver(Event::InputKey* input)
{
	if ((EventCode::_BtnLeft   == input->code) ||
	 	(EventCode::_BtnRight  == input->code) ||
		(EventCode::_BtnMiddle == input->code))
	{
		//Get the current key
		data.key = input->code;

		//Get whether the keyboard button is pressed or released
		if(KeyStatus::_KeyPressed == input->status)
			data.state = KeyState::_Pressed;
		else
			data.state = KeyState::_Pressed;

		//Set the ready flag
		SetReady();
	}
}


/// @brief Axis input receiver
void VkMouse::AxisReceiver(Event::InputAxis* input)
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

	//Set the ready flag
	SetReady();
}


/// @brief Read
IndevData VkMouse::Read()
{
	return data;
}
