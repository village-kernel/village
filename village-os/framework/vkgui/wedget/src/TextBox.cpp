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
	buff(NULL)
{
}


/// @brief Destructor
TextBox::~TextBox()
{
	FreeBuff();
}


/// @brief 
void TextBox::Setup()
{
	isOverflow = false;
	locX = 0;
	locY = 0;
	colSize = 0;
	rowSize = 0;
	buffCol = 0;
	buffRow = 0;
	dispCol = 0;
	dispRow = 0;
}


/// @brief 
/// @param text 
void TextBox::SetText(char* text)
{
	if (NULL != buff)
	{
		ClearBuff();
		AppendText(text);
	}
}


/// @brief 
/// @param text 
void TextBox::AppendText(char* text)
{
	int size = 0;

	if (NULL != text)
	{
		while ('\0' != text[size])
		{
			if ((text[size] <= '~') && (text[size] >= ' '))
			{
				buff[buffRow][buffCol] = text[size];
			}
			else if (text[size] == '\n')
			{
				buff[buffRow][buffCol] = '\0';
			}

			if ((text[size] == '\b'))
			{
				buffCol--;
			}
			else
			{
				if ((++buffCol >= colSize) || (text[size] == '\n'))
				{
					buffCol = 0;
					if (++buffRow >= rowSize) { buffRow = 0; isOverflow = true; }
					if (isOverflow) { memset(buff[buffRow], ' ', 120); }
				}
			}

			size++;
		}
	}
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


/// @brief Show
void TextBox::Show()
{
	locX = GetLocX();
	locY = GetLocY();
	colSize = width / 8;
	rowSize = height / 16;

	AllocBuff();
	ClearBuff();

	Wedget::Show();
}


/// @brief Refresh
void TextBox::Refresh()
{
	static const int fontSize = Display::Font16;

	lock.Lock();

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

	lock.Unlock();

	Wedget::Refresh();
}


/// @brief ShowString
/// @param x 
/// @param y 
/// @param str 
/// @param size 
void TextBox::ShowString(uint32_t x, uint32_t y, char* str, uint32_t size)
{
	bool isVaild = true;
	uint32_t xOffset = x;
	uint32_t yOffset = y;
	uint32_t limitX = GetLocX() + GetWidth();
	Display::FontSize fontSize = Display::Font16;

	for (uint32_t i = 0; i < size; i++)
	{
		char chr = (str[i] <= '~') && (str[i] >= ' ') ? str[i] : ' ';

		if (str[i] == '\0') isVaild = false;

		if (false == isVaild) chr = ' ';

		display->ShowChar(xOffset, yOffset, chr, fontSize, Display::NotMultiply, Display::Black);

		xOffset += fontSize >> 1;

		if (xOffset > limitX)
		{
			xOffset = 0;
			yOffset += fontSize;
		}
	}
}
