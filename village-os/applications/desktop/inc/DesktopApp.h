//###########################################################################
// DesktopApp.h
// Declarations of the desktop app
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DESKTOP_APP_H__
#define __DESKTOP_APP_H__

#include "DesktopUI.h"
#include "Kernel.h"


/// @brief DesktopApp
class DesktopApp
{
private:
	//Members
	DesktopUI ui;
public:
	//Methods
	DesktopApp();
	~DesktopApp();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__DESKTOP_APP_H__