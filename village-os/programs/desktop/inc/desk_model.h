//###########################################################################
// desk_model.h
// Declarations of the desk view model
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DESK_MODEL_H__
#define __DESK_MODEL_H__

#include "vg_gui.h"


/// @brief DeskModel
class DeskModel : public Class
{
public:
	////Data
	//Collection ContextMenuLists;
	//Collection ShortcutLists;

	//Command
	ICommand*  ContextMenuCmd;
	ICommand*  ShortcutCmd;
public:
	//Methods
	DeskModel();
	~DeskModel();
private:
	//Command Methods
	void OpenApplication(const char* name);
	void ExitApplication(const char* name);
};

#endif //!__DESK_VIEW_MODEL_H__
