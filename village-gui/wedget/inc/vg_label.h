//###########################################################################
// vg_label.h
// Declarations of the functions that manage label
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_LABEL_H__
#define __VG_LABEL_H__

#include "vg_wedget.h"


/// @brief Label
class Label : public Wedget
{
private:
	//Memebers
	char* label;
public:
	//Methods
	Label();
	~Label();

	void SetText(char* text);
};

#endif //!__VG_LABEL_H__
