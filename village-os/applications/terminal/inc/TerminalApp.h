//###########################################################################
// TerminalApp.h
// Declarations of the terminal app
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TERMINAL_APP_H__
#define __TERMINAL_APP_H__

#include "TerminalDrv.h"
#include "TerminalView.h"


/// @brief TerminalAPP
class TerminalAPP
{
private:
	//Members
	TerminalDrv drv;
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
