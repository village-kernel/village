//###########################################################################
// TerminalApp.h
// Declarations of the terminal app
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TERMINAL_APP_H__
#define __TERMINAL_APP_H__

#include "TerminalDrv.h"
#include "TerminalUI.h"


/// @brief TerminalAPP
class TerminalAPP
{
private:
	//Members
	TerminalDrv drv;
	TerminalUI  ui;
public:
	//Methods
	TerminalAPP();
	~TerminalAPP();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__TERMINAL_APP_H__
