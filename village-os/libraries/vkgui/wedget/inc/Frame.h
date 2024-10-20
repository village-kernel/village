//###########################################################################
// Frame.h
// Declarations of the functions that manage stack frame
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_FRAME_H__
#define __VK_FRAME_H__

#include "Wedget.h"


/// @brief Frame
class Frame : public Wedget
{
public:
	//Methods
	Frame();
	~Frame();

	void InitContent();
	void DrawContent();
};

#endif //!__VK_FRAME_H__
