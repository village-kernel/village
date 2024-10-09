//###########################################################################
// TextBox.cpp
// Definitions of the functions that manage text box
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "TextBox.h"
#include "string.h"
#include "Regex.h"


/// @brief Constructor
TextBox::TextBox()
	:isOverflow(false),
	locX(0),
	locY(0),
	colSize(0),
	rowSize(0),
	buffCol(0),
	buffRow(0),
	dispCol(0),
	dispRow(0),
	buff(NULL),
	vertScrollbar(NULL),
	horiScrollbar(NULL)
{
	fifo.Setup(fifo_size);
}


/// @brief Destructor
TextBox::~TextBox()
{
	FreeBuff();
	fifo.Exit();
}


/// @brief AllocBuff
void TextBox::AllocBuff()
{
	buff = new char*[rowSize]();

	for (int i = 0; i < rowSize; i++)
	{
		buff[i] = new char[colSize]();
	}
}


/// @brief FreeBuff
void TextBox::FreeBuff()
{
	if (NULL == buff) return;

	for (int i = 0; i < rowSize; i++)
	{
		delete buff[i];
	}
	
	delete[] buff;
}


/// @brief ClearBuff
void TextBox::ClearBuff()
{
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			buff[i][j] = ' ';
		}
	}
}


/// @brief InitContent
void TextBox::InitContent()
{
	vertScrollbar = new Scrollbar();
	vertScrollbar->SetSize(0, GetHeight() - 5, GetWidth(), 5);	
	vertScrollbar->SetDirection(Scrollbar::_Vertical);
	AddWedget(vertScrollbar);
	
	horiScrollbar = new Scrollbar();
	horiScrollbar->SetSize(GetWidth() - 5, 0, 5, GetHeight());
	horiScrollbar->SetDirection(Scrollbar::_Horizontal);
	AddWedget(horiScrollbar);
	
	isOverflow = false;
	buffCol = 0;
	buffRow = 0;
	dispCol = 0;
	dispRow = 0;

	locX = GetLocX() + 1;
	locY = GetLocY() + 1;
	limitX = GetLocX() + GetWidth() - 8;
	colSize = (GetWidth() - 2) / 8;
	rowSize = (GetHeight() - 2) / 16;

	AllocBuff();
	ClearBuff();
}


/// @brief DrawContent
void TextBox::DrawContent()
{
	static const int fontSize = DrawingDefs::Font16;

	int dethaRow = buffRow - dispRow;

	if (0 == dethaRow)
	{
		int dethaCol = buffCol - dispCol;

		if (0 != dethaCol)
		{
			int yoff = isOverflow ? rowSize - 1 : dispRow;
			ShowString(locX, locY + (fontSize * yoff), buff[dispRow], colSize);
			dispCol = buffCol;
		}
	}
	else
	{
		int index = isOverflow ? 0 : dispRow;
		int size  = isOverflow ? rowSize : buffRow + 1;
		
		for (int i = index; i < size; i++)
		{
			dispRow = isOverflow ? i + buffRow + 1 : i;
			if (dispRow >= rowSize) dispRow = dispRow - rowSize;
			ShowString(locX, locY + (fontSize * i), buff[dispRow], colSize);
		}

		dispCol = buffCol;
	}
}


/// @brief ShowString
/// @param x 
/// @param y 
/// @param str 
/// @param size 
void TextBox::ShowString(int x, int y, char* str, int size)
{
	bool isVaild = true;
	int xOffset = x;
	int yOffset = y;
	DrawingDefs::FontSize fontSize = DrawingDefs::Font16;

	for (int i = 0; i < size; i++)
	{
		char chr = (str[i] <= '~') && (str[i] >= ' ') ? str[i] : ' ';

		if (str[i] == '\0') isVaild = false;

		if (false == isVaild) chr = ' ';

		drawing->chr.Set(xOffset, yOffset, chr, fontSize, DrawingDefs::NotMultiply, DrawingDefs::Black);

		xOffset += fontSize >> 1;

		if (xOffset > limitX)
		{
			xOffset = 0;
			yOffset += fontSize;
		}
	}
}


/// @brief 
/// @param text 
int TextBox::SetText(char* text, int size)
{
	if (NULL != buff)
	{
		ClearBuff();
		return AppendText(text, size);
	}
	return 0;
}


/// @brief 
/// @param text 
int TextBox::AppendText(char* text, int size)
{
	if (0 == size) size = strlen(text);

	for (int i = 0; i < size; i++)
	{
		if ((text[i] <= '~') && (text[i] >= ' '))
		{
			buff[buffRow][buffCol] = text[i];
		}
		else if (text[i] == '\n')
		{
			buff[buffRow][buffCol] = '\0';
		}

		if ((text[i] == '\b'))
		{
			buffCol--;
		}
		else
		{
			if ((++buffCol >= colSize) || (text[i] == '\n'))
			{
				buffCol = 0;
				if (++buffRow >= rowSize) { buffRow = 0; isOverflow = true; }
				if (isOverflow) { memset(buff[buffRow], ' ', 120); }
			}
		}
	}

	isChange = (0 != size);

	return size;
}


/// @brief 
/// @param data 
/// @param size 
void TextBox::InputData(char* data, int size)
{
	fifo.Put(data, size);
}


/// @brief 
/// @param data 
/// @param size 
/// @return 
int TextBox::OutputData(char* data, int size)
{
	return fifo.Pop(data, size);
}
