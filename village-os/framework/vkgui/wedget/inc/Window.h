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
private:
	//Members
	int locX;
	int locY;
	int locZ;
	Wedget* cursor;
public:
	//Methods
	Window();
	void Initialize();
	void UpdateKey(int code, int status);
	void UpdateCursor(int axisX, int axisY, int axisZ);
	void Show();
};

#endif //!__VK_WINDOW_H__
