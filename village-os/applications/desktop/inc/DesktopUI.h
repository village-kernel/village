//###########################################################################
// DesktopUI.h
// Declarations of the desktop ui
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DESKTOP_UI_H__
#define __DESKTOP_UI_H__

#include "VkGUI.h"
#include "Kernel.h"


/// @brief DesktopUI
class DesktopUI : public Class
{
private:
	//Members
	Window*  mainwin;
	Toolbar* toolbar;
	Tabbar*  tabbar;
	Button*  button0;
	Button*  button1;
	Button*  button2;
	Button*  button3;
	Button*  button4;
	Cursor*  cursor;

	//Methods
	bool SetupWin();
	void UpdateAxis(InputEvent::OutputAxis* input);
public:
	//Methods
	DesktopUI();
	~DesktopUI();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__DESKTOP_UI_H__
