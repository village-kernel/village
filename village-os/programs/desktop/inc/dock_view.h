//###########################################################################
// dock_view.h
// Declarations of the desktop view
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DOCK_VIEW_H__
#define __DOCK_VIEW_H__

#include "dock_model.h"


/// @brief DockView
class DockView
{
private:
	//Members
	DockModel model;
public:
	//Methods
	void InitComponent(Wedget* parent);
};

#endif //!__DOCK_VIEW_H__
