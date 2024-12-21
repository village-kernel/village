//###########################################################################
// desk_view.h
// Declarations of the desk view
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DESK_VIEW_H__
#define __DESK_VIEW_H__

#include "desk_model.h"


/// @brief DeskView
class DeskView
{
private:
	//Members
	DeskModel model;
public:
	//Methods
	void InitComponent(Wedget* parent);
};

#endif //!__DESK_VIEW_H__
