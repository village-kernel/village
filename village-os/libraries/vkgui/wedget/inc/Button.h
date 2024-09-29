//###########################################################################
// Button.h
// Declarations of the functions that manage button
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_BUTTON_H__
#define __VK_BUTTON_H__

#include "Wedget.h"

///Button
class Button : public Wedget
{
private:
	//Members
	char* text;
public:
	//Methods
	Button();
	~Button();
	void Setup();
	void Show();
	void SetText(char* text);
};

#endif //!__VK_BUTTON_H__
