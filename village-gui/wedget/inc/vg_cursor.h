//###########################################################################
// vg_cursor.h
// Declarations of the functions that manage cursor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_CURSOR_H__
#define __VG_CURSOR_H__

#include "vg_wedget.h"


/// @brief Cursor
class Cursor : public Wedget
{
public:
	//Methods
	Cursor();
	~Cursor();
	
	void InitContent();
	void DrawContent();
};

#endif //!__VG_CURSOR_H__
