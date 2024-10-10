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
#include "Fifo.h"
#include "Scrollbar.h"


/// @brief TextBox
class TextBox : public Wedget
{
private:
	static const int fifo_size = 100;

	Mutex lock;
	bool isOverflow;
	int locX;
	int locY;
	int limitX;
	int colSize;
	int rowSize;
	int buffCol;
	int buffRow;
	int dispCol;
	int dispRow;
	char** buff;

	Fifo<char> fifo;

	//Members
	Scrollbar* vertScrollbar;
	Scrollbar* horiScrollbar;

	//Methods
	void AllocBuff();
	void FreeBuff();
	void ClearBuff();
	void ShowString(int x, int y, char* str, int size);
public:
	//Methods
	TextBox();
	~TextBox();
	
	void InitContent();
	void DrawContent();

	int SetText(char* text, int size = 0);
	int AppendText(char* text, int size = 0);

	void InputData(char* data, int size = 0);
	int OutputData(char* data, int size = 0);
};

#endif //!__VK_TEXT_BOX_H__
