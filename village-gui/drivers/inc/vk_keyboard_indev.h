//###########################################################################
// vk_keyboard_indev.h
// Declarations of the functions that manage keyboard
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_KEYBOARD_INDEV_H__
#define __VK_KEYBOARD_INDEV_H__

#include "vg_indev.h"
#include "vk_class.h"
#include "vk_kernel.h"


/// @brief VkKeyBoard
class VkKeyBoard : public Indev, public Class
{
private:
	//Members
	IndevData data;

	//Methods
	void KeyReceiver(Event::InputKey* input);
public:
	//Methods
	void Setup(VgDevices* devices);
	void Exit();

	//Data Methods
	IndevData Read();
};

#endif //!__VK_KEYBOARD_INDEV_H__
