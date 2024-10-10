//###########################################################################
// MsgBox.h
// Declarations of the functions that manage message box
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_MSG_BOX_H__
#define __VK_MSG_BOX_H__

#include "Wedget.h"


/// @brief MsgBox
class MsgBox : public Wedget
{
public:
	//Methods
	MsgBox();
	~MsgBox();

	void InitContent();
	void DrawContent();
};

#endif //!__VK_MSG_BOX_H__
