//###########################################################################
// vg_window.h
// Declarations of the functions that manage window
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_WINDOW_H__
#define __VG_WINDOW_H__

#include "vg_wedget.h"
#include "vg_draw_rect.h"


/// @brief Window
class Window : public Wedget
{
private:
	//Members
	DrawRect rect;

	//Attribute members
	bool isTop;
public:
	//Methods
	Window();
	~Window();

	//Draw methods
	void InitContent();
	void DrawContent();

	//Attribute methods
	void PlaceOnTop();
	void CancelOnTop();
	bool IsOnTop();
};

#endif //!__VG_WINDOW_H__
