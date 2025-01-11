//###########################################################################
// vg_context.h
// Declarations of the functions that manage context
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_CONTEXT_H__
#define __VG_CONTEXT_H__

#include "vg_menu.h"


/// @brief VgContext
class VgContext : public VgMenu
{
private:
	//Members
	VgDrawArea oldArea;
public:
	//Methods
	VgContext();
	~VgContext();

	//Area methods
	VgDrawAreas GetUpdateAreas();

	//Attribute methods
	void SetFocus(bool focus);
private:
	//Methods
	void UpdateActive(bool active);
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_CONTEXT_H__
