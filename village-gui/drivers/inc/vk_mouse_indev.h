//###########################################################################
// vk_mouse_indev.h
// Declarations of the functions that manage mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_MOUSE_INDEV_H__
#define __VK_MOUSE_INDEV_H__

#include "vg_indev.h"
#include "vk_class.h"
#include "vk_kernel.h"


/// @brief VkMouse
class VkMouse : public Indev, public Class
{
private:
	//Members
	IndevData data;

	//Methods
	void KeyReceiver(Event::InputKey* input);
	void AxisReceiver(Event::InputAxis* input);
public:
	//Methods
	void Setup();
	void Exit();

	//Data Methods
	IndevData Read();
};

#endif //!__VK_MOUSE_INDEV_H__
