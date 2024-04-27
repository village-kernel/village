//###########################################################################
// Label.h
// Declarations of the functions that manage label
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_LABEL_H__
#define __VK_LABEL_H__

#include "Wedget.h"

///Label
class Label : public Wedget
{
private:
	//Memebers
	char* label;
public:
	//Methods
	void Setup();
	void Show();
	void SetLabel(char* label);
};

#endif //!__VK_LABEL_H__
