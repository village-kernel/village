//###########################################################################
// filemgr_app.h
// Declarations of the filemgr app
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILEMGR_APP_H__
#define __FILEMGR_APP_H__

#include "filemgr_view.h"


/// @brief FilemgrApp
class FilemgrApp
{
private:
	//Members
	VillageGUI*  vkgui;
	VgWindow*      mainwin;

	//Members
	FilemgrView view;
public:
	//Methods
	FilemgrApp();
	~FilemgrApp();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__FILEMGR_APP_H__
