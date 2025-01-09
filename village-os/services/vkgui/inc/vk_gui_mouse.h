//###########################################################################
// vk_gui_mouse.h
// Declarations of the functions that manage mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_GUI_MOUSE_H__
#define __VK_GUI_MOUSE_H__

#include "vg_indev.h"
#include "vg_math.h"
#include "vk_class.h"
#include "vk_kernel.h"


/// @brief VkMouse
class VkMouse : public VgIndev, public Class
{
private:
	//Members
	VgDevices* devices;

	//Members
	VgMath math;

	//Members
	VgInputData data;
	VgWindow* cursor;

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
	VgWindow* Cursor();

	//Data Methods
	VgInputData Read();
};

#endif //!__VK_GUI_MOUSE_H__
