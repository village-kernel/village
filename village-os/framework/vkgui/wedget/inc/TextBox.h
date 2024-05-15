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
	Mutex lock;
	bool isOverflow;
	int locX;
	int locY;
	int colSize;
	int rowSize;
	int buffCol;
	int buffRow;
	int dispCol;
	int dispRow;
	char** buff;

	void AllocBuff();
	void FreeBuff();
	void ClearBuff();
	void ShowString(uint32_t x, uint32_t y, char* str, uint32_t size);
public:
	TextBox();
	~TextBox();
	void Setup();
	void Show();
	void SetText(char* text);
	void AppendText(char* text);
	void Refresh();
};

#endif //!__VK_TEXT_BOX_H__
