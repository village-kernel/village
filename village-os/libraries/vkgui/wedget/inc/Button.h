//###########################################################################
// Button.h
// Declarations of the functions that manage button
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_BUTTON_H__
#define __VK_BUTTON_H__

#include "Wedget.h"


/// @brief Button
class Button : public Wedget
{
private:
	//Members
	int   x0;
	int   y0;
	char* text;
public:
	//Methods
	Button();
	~Button();
	
	void InitContent();
	void DrawContent();

	void SetText(char* text);
};

#endif //!__VK_BUTTON_H__
