//###########################################################################
// vg_msgbox.h
// Declarations of the functions that manage message box
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_MSG_BOX_H__
#define __VG_MSG_BOX_H__

#include "vg_wedget.h"


/// @brief VgMsgBox
class VgMsgBox : public VgWedget
{
public:
	//Methods
	VgMsgBox();
	~VgMsgBox();
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_MSG_BOX_H__
