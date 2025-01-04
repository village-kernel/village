//###########################################################################
// manager_view.h
// Declarations of the manager view
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MANAGER_VIEW_H__
#define __MANAGER_VIEW_H__

#include "manager_model.h"

/// @brief ManagerView
class ManagerView
{
private:
	//Members
	ManagerModel model;
public:
	//Methods
	void InitComponent(Wedget* parent);
};

#endif //!__MANAGER_VIEW_H__
