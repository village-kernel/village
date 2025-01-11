//###########################################################################
// vg_button.h
// Declarations of the functions that manage button
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_BUTTON_H__
#define __VG_BUTTON_H__

#include "vg_wedget.h"
#include "vg_draw_text.h"


/// @brief VgButton
class VgButton : public VgWedget
{
private:
	//Members
	char*         text;
	void*         args;
	IData<char*>* bText;
	IData<void*>* bArgs;

	//Members
	VgDrawText    drawText;
public:
	//Methods
	VgButton();
	~VgButton();

	//Binding Methods
	void BindingText(IData<char*>* text);
	void SetText(char* text);
	char* GetText();

	void BindingArgs(IData<void*>* args);
	void SetArgs(void* args);
	void* GetArgs();
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_BUTTON_H__
