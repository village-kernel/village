//###########################################################################
// vg_label.h
// Declarations of the functions that manage label
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_LABEL_H__
#define __VG_LABEL_H__

#include "vg_wedget.h"
#include "vg_draw_label.h"


/// @brief Label
class Label : public Wedget
{
private:
	//Memebers
	char* 	  label;
	DrawLabel drawlab;
public:
	//Methods
	Label();
	~Label();

	//Attribute Methods
	void SetText(char* text);

	//Methods
	void Initiate(VgDevices* devices);
	void Redraw(DrawArea drawArea);
};

#endif //!__VG_LABEL_H__
