//###########################################################################
// Window.h
// Declarations of the functions that manage window
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_WINDOW_H__
#define __VK_WINDOW_H__

#include "Wedget.h"

///Window
class Window : public Wedget
{
public:
	//Methods
	Window();
	void Setup();
	void Show();
};

#endif //!__VK_WINDOW_H__
