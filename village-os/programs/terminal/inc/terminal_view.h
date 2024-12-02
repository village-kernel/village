//###########################################################################
// terminal_view.h
// Declarations of the terminal view
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TERMINAL_VIEW_H__
#define __TERMINAL_VIEW_H__

#include "terminal_model.h"


/// @brief TerminalView
class TerminalView
{
private:
	//Members
	TerminalModel model;
public:
	//Methods
	void InitComponent(Wedget* parent);
};

#endif //!__TERMINAL_VIEW_H__
