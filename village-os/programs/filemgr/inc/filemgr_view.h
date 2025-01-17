//###########################################################################
// filemgr_view.h
// Declarations of the filemgr view
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILEMGR_VIEW_H__
#define __FILEMGR_VIEW_H__

#include "filemgr_model.h"

/// @brief FilemgrView
class FilemgrView
{
private:
	//Members
	FilemgrModel model;
public:
	//Methods
	void InitComponent(VgWedget* parent);
};

#endif //!__FILEMGR_VIEW_H__
