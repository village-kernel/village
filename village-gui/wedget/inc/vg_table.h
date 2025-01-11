//###########################################################################
// vg_table.h
// Declarations of the functions that manage table
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_TABLE_H__
#define __VG_TABLE_H__

#include "vg_menu.h"


/// @brief VgTable
class VgTable : public VgMenu
{
public:
	//Methods
	VgTable();
	~VgTable();
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_TABLE_H__
