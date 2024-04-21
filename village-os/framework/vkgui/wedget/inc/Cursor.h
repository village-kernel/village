//###########################################################################
// Cursor.h
// Declarations of the functions that manage cursor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_CURSOR_H__
#define __VK_CURSOR_H__

#include "Wedget.h"

/// @brief Cursor
class Cursor : public Wedget
{
private:
	//Members
	int locX;
	int locY;
public:
	//Methods
	Cursor();
	void Initialize();
	void Show();
};

#endif //!__VK_CURSOR_H__
