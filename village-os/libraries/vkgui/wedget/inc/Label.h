//###########################################################################
// Label.h
// Declarations of the functions that manage label
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_LABEL_H__
#define __VK_LABEL_H__

#include "Wedget.h"


/// @brief Label
class Label : public Wedget
{
private:
	//Memebers
	char* label;
public:
	//Methods
	void SetText(char* text);
	void DrawContent();
};

#endif //!__VK_LABEL_H__
