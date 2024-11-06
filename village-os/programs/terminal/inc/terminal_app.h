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
class TerminalAPP
{
private:
	//Members
	TerminalView view;
public:
	//Methods
	TerminalAPP();
	~TerminalAPP();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__TERMINAL_APP_H__
