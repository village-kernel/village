//###########################################################################
// VkGuiService.h
// Declarations of the village gui service
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_GUI_SERVICE_H__
#define __VK_GUI_SERVICE_H__

#include "Module.h"
#include "Kernel.h"
#include "VkGUI.h"


/// @brief VkGuiService
class VkGuiService : public Module
{
private:
	//Members
	VkGUI vkgui;

	//Methods
	void TextReceiver(InputEvent::OutputText* input);
	void AxisReceiver(InputEvent::OutputAxis* input);
public:
	//Methods
	VkGuiService();
	~VkGuiService();
	bool  Setup();
	void  Exit();
	void* GetData();
};

#endif //!__VK_GUI_SERVICE_H__
