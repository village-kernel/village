//###########################################################################
// vk_gui_service.h
// Declarations of the village gui service
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_GUI_SERVICE_H__
#define __VK_GUI_SERVICE_H__

#include "vk_module.h"
#include "vk_kernel.h"
#include "vg_villageui.h"


/// @brief VkGuiService
class VkGuiService : public Module
{
private:
	//Members
	bool       isReady;
	VillageGUI vkgui;
public:
	//Methods
	VkGuiService();
	~VkGuiService();
	bool Setup();
	void Execute();
	void Exit();
	void* GetData();
};

#endif //!__VK_GUI_SERVICE_H__
