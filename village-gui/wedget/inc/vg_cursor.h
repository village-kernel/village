//###########################################################################
// vg_cursor.h
// Declarations of the functions that manage cursor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_CURSOR_H__
#define __VG_CURSOR_H__

#include "vg_window.h"


/// @brief VgCursor
class VgCursor : public VgWindow
{
public:
	//Methods
	VgCursor();
	~VgCursor();
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_CURSOR_H__
