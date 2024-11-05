//###########################################################################
// desktop_view.h
// Declarations of the desktop view
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DESKTOP_VIEW_H__
#define __DESKTOP_VIEW_H__

#include "vg_graphics.h"
#include "desktop_model.h"


/// @brief DesktopView
class DesktopView
{
private:
	//Members
	DesktopModel model;
public:
	//Methods
	void InitComponent(Wedget* parent);
};

#endif //!__DESKTOP_VIEW_H__
