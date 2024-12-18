//###########################################################################
// vk_mouse_indev.h
// Declarations of the functions that manage mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_MOUSE_INDEV_H__
#define __VK_MOUSE_INDEV_H__

#include "vg_indev.h"
#include "vg_math.h"
#include "vk_class.h"
#include "vk_kernel.h"


/// @brief VkMouse
class VkMouse : public Indev, public Class
{
private:
	//Members
	VgDevices* devices;

	//Members
	Math math;

	//Members
	IndevData data;
	Window* cursor;

	//Methods
	void KeyReceiver(Event::InputKey* input);
	void AxisReceiver(Event::InputAxis* input);
public:
	//Methods
	VkMouse();
	~VkMouse();
	void Setup(VgDevices* devices);
	void Exit();

	//Mouse Methods
	Window* Cursor();

	//Data Methods
	IndevData Read();
};

#endif //!__VK_MOUSE_INDEV_H__
