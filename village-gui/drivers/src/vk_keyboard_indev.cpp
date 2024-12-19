//###########################################################################
// vk_keyboard_indev.cpp
// Definitions of the functions that manage keyboard
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_keyboard_indev.h"
#include "vk_event_codes.h"
#include "vk_kernel.h"


/// @brief Setup
void VkKeyBoard::Setup(VgDevices* devices)
{
	//Set indev type
	SetType(IndevType::_Keyboard);

	//Attach input event
	kernel->event.Attach(Event::_InputKey,  (Method)&VkKeyBoard::KeyReceiver, this);
}


/// @brief Exit
void VkKeyBoard::Exit()
{
	//Detach input event
	kernel->event.Detach(Event::_InputKey,  (Method)&VkKeyBoard::KeyReceiver, this);
}


/// @brief key input receiver
void VkKeyBoard::KeyReceiver(Event::InputKey* input)
{
	if (input->code <= EventCode::_KeyMicMute)
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


/// @brief Read
IndevData VkKeyBoard::Read()
{
	return data;
}
