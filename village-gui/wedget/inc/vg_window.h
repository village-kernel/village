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
public:
	//Methods
	Window();
	~Window();
	
	//Methods
	void Initiate(GraphicsDevices* devices);
	void Execute(IndevData input);
};

#endif //!__VG_WINDOW_H__
