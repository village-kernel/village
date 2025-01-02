//###########################################################################
// vk_gui_mouse.cpp
// Definitions of the functions that manage mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_gui_mouse.h"
#include "vk_event_codes.h"
#include "vk_kernel.h"
#include "vg_window.h"


/// @brief Constructor
VkMouse::VkMouse()
	:cursor(NULL)
{
}


/// @brief Destructor
VkMouse::~VkMouse()
{
}


/// @brief Setup
void VkMouse::Setup(VgDevices* devices)
{
	this->devices = devices;

	//Set indev type
	SetType(IndevType::_Mouse);

	//Create an cursor
	cursor = new Window();
	cursor->SetSize(8, 8);
	cursor->SetBgColor(DrawDefs::_Black);
	cursor->SetHiddenNavbar(true);
	cursor->Initiate(devices);

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
			data.state = KeyState::_Released;

		//Set the ready flag
		SetReady();
	}
}


/// @brief Axis input receiver
void VkMouse::AxisReceiver(Event::InputAxis* input)
{
	static Point point;

	//Get the limit x y
	int maxX = devices->lcddev->GetWidth() - 1;
	int maxY = devices->lcddev->GetHeight() - 1;

	//Update point x
	point.x += input->axisX;
	point.x  = math.Sat(point.x, 0, maxX);
	
	//Update point y
	point.y -= input->axisY;
	point.y  = math.Sat(point.y, 0, maxY);

	//Set the data point
	data.point = point;

	//Set the ready flag
	SetReady();
}


/// @brief Cursor
/// @return 
Window* VkMouse::Cursor()
{
	return cursor;
}


/// @brief Read
IndevData VkMouse::Read()
{
	return data;
}
