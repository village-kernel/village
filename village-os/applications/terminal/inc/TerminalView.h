//###########################################################################
// TerminalView.h
// Declarations of the terminal view
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TERMINAL_VIEW_H__
#define __TERMINAL_VIEW_H__

#include "VkGUI.h"

/// @brief TerminalView
class TerminalView
{
private:
	//Members
	Window*  mainwin;
	Navbar*  navbar;
	TextBox* textbox;
public:
	//Methods
	TerminalView();
	~TerminalView();
	void Setup();
	void Execute();
	void Exit();

	int Input(uint8_t* data, uint32_t size);
	int Output(uint8_t* data, uint32_t size);
};

#endif //!__TERMINAL_VIEW_H__
