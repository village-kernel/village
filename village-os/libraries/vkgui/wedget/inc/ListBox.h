//###########################################################################
// ListBox.h
// Declarations of the functions that manage list box
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_LIST_BOX_H__
#define __VK_LIST_BOX_H__

#include "Wedget.h"


/// @brief ListBox
class ListBox : public Wedget
{
public:
	//Methods
	ListBox();
	~ListBox();

	void InitContent();
	void DrawContent();
};

#endif //!__VK_LIST_BOX_H__
