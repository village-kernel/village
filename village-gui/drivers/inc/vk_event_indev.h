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
	//Methods
	void TextReceiver(Event::OutputText* input);
	void AxisReceiver(Event::OutputAxis* input);
public:
	//Methods
	void Setup();
	void Exit();

	//Data Methods
	void Read(IndevData* data);
};

#endif //!__VK_EVENT_INDEV_H__
