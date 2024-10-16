//###########################################################################
// Graphics.h
// Declarations of the functions that manage Graphics
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "Display.h"
#include "Wedgets.h"

/// @brief Graphics
class Graphics
{
private:
	//Members
	FBDriver*   fbdev;
	Display*    display;
	Wedget*     mainwin;
public:
	//Methods
	Graphics();
	~Graphics();
	bool Setup();
	void Exit();
	Wedget* CreateMainWindow();
};

#endif //!__GRAPHICS_H__
