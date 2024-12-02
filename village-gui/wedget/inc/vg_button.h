//###########################################################################
// vg_button.h
// Declarations of the functions that manage button
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_BUTTON_H__
#define __VG_BUTTON_H__

#include "vg_wedget.h"


/// @brief Button
class Button : public Wedget
{
private:
	//Members
	char* text;
public:
	//Methods
	Button();
	~Button();

	//Binding Methods
	void SetText(char* text);

	//Methods
	void Execute(IndevData input);
};

#endif //!__VG_BUTTON_H__
