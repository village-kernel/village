//###########################################################################
// vk_event_indev.h
// Declarations of the functions that manage event
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_EVENT_INDEV_H__
#define __VK_EVENT_INDEV_H__

#include "vg_indev.h"
#include "vg_data.h"
#include "vk_class.h"
#include "vk_kernel.h"


/// @brief VkEvent
class VkEvent : public Indev, public Class
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
	IndevData* Read();
};

#endif //!__VK_EVENT_INDEV_H__
