//###########################################################################
// VkGUI.h
// Declarations of the functions that manage VkGUI
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_GUI_H__
#define __VK_GUI_H__

#include "Module.h"
#include "Display.h"
#include "Wedgets.h"


/// @brief VkGUI
class VkGUI : public Module
{
private:
	//Members
	FBDriver*   fbdev;
	Display*    display;
	Wedget*     mainwin;
public:
	//Methods
	VkGUI();
	~VkGUI();
	bool Setup();
	void Exit();
	Wedget* CreateMainWindow();
};

#endif //!__VK_GUI_H__
