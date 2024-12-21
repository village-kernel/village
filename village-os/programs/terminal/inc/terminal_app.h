//###########################################################################
// TerminalApp.h
// Declarations of the terminal app
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TERMINAL_APP_H__
#define __TERMINAL_APP_H__

#include "terminal_view.h"


/// @brief TerminalAPP
class TerminalAPP : public Class
{
private:
	//Members
	int          tid;
	ICommand*    closeCmd;

	//Members
	VillageGUI*  vkgui;
	Window*      mainwin;

	//Members
	TerminalView view;
public:
	//Methods
	TerminalAPP();
	~TerminalAPP();
	void Setup();
	void Execute();
	void Close();
	void Exit();
};

#endif //!__TERMINAL_APP_H__
