//###########################################################################
// manager_app.h
// Declarations of the manager app
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MANAGER_APP_H__
#define __MANAGER_APP_H__

#include "manager_view.h"


/// @brief ManagerApp
class ManagerApp
{
private:
	//Members
	VillageGUI*  vkgui;
	Window*      mainwin;

	//Members
	ManagerView view;
public:
	//Methods
	ManagerApp();
	~ManagerApp();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__MANAGER_APP_H__
