//###########################################################################
// vg_button.h
// Declarations of the functions that manage button
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_BUTTON_H__
#define __VG_BUTTON_H__

#include "vg_wedget.h"
#include "vg_label.h"


/// @brief Button
class Button : public Wedget
{
private:
	//Members
	char* text;
	IData<char*>* bText;

	//Members
	Label label;
public:
	//Methods
	Button();
	~Button();

	//Binding Methods
	void BindingText(IData<char*>* text);
	void SetText(char* text);
	char* GetText();

	//Methods
	void Initiate(VgDevices* devices);
	void Execute(IndevData input);
};

#endif //!__VG_BUTTON_H__
