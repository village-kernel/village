//###########################################################################
// dock_model.h
// Declarations of the dock view model
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DOCK_MODEL_H__
#define __DOCK_MODEL_H__

#include "vg_gui.h"


/// @brief DockModel
class DockModel : public Class
{
public:
	////Data
	//char*      StartText;
	//Collection StartMenuLists;
	//Collection TaskbarLists;

	//Command
	ICommand*  StartBtnCmd;
	ICommand*  StartMenuCmd;
	ICommand*  TaskbarCmd;
public:
	//Methods
	DockModel();
	~DockModel();
private:
	//Command Methods
	void OpenApplication(const char* name);
	void ExitApplication(const char* name);
};

#endif //!__DOCK_MODEL_H__
