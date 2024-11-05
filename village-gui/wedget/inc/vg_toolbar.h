//###########################################################################
// vg_toolbar.h
// Declarations of the functions that manage tool bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_TOOL_BAR_H__
#define __VG_TOOL_BAR_H__

#include "vg_wedget.h"
#include "vg_button.h"


/// @brief Toolbar
class Toolbar : public Wedget
{
public:
	//Methods
	Toolbar();
	~Toolbar();

	void InitContent();
	void DrawContent();
};

#endif //!__VG_TOOL_BAR_H__
