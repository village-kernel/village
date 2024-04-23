//###########################################################################
// TextBox.h
// Declarations of the functions that manage text box
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_TEXT_BOX_H__
#define __VK_TEXT_BOX_H__

#include "Wedget.h"
#include "Mutex.h"

///TextBox
class TextBox : public Wedget
{
private:
	char* text;
	Mutex lock;
public:
	void Initialize();
	void Show();
	void SetText(char* text);
	void AppendText(char* text);
};

#endif //!__VK_TEXT_BOX_H__
