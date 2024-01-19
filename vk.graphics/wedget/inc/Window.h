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
	void Update(int axisX, int axisY, int axisZ);
	void Show();
};

#endif //!__VK_WINDOW_H__
