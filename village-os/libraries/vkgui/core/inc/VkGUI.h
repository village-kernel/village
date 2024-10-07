//###########################################################################
// VkGUI.h
// Declarations of the functions that manage VkGUI
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_GUI_H__
#define __VK_GUI_H__

#include "Wedgets.h"
#include "Drawing.h"
#include "Indev.h"
#include "List.h"


/// @brief VkGUI
class VkGUI
{
private:
	//Members
	FBDriver*     fbdev;
	Drawing*      drawing;
	Indev*        indev;
	Wedget*       cursor;
	List<Wedget*> wedgets;
public:
	//Methods
	VkGUI();
	~VkGUI();
	bool Setup(FBDriver* fbdev);
	void Execute();
	void Exit();

	//Input Methods
	void InputText(char* data, int size);
	void InputAxis(int axisX, int axisY, int axisZ);

	//GUI Methods
	Wedget* CreateMainWindow();
	bool DestroyMainWindow(Wedget* mainwin);
	void EnableCursor();
	void DisableCursor();
};

#endif //!__VK_GUI_H__
