//###########################################################################
// GuiService.h
// Declarations of the gui service
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __GUI_SERVICE_H__
#define __GUI_SERVICE_H__

#include "Kernel.h"
#include "VkGUI.h"


/// @brief GuiService
class GuiService
{
private:
	//Members
	VkGUI vkgui;
public:
	//Methods
	GuiService();
	~GuiService();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__GUI_SERVICE_H__
