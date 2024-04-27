//###########################################################################
// TextBox.cpp
// Definitions of the functions that manage text box
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "TextBox.h"


/// @brief 
void TextBox::Setup()
{
	text = NULL;
}


/// @brief 
void TextBox::Show()
{
	int locX = GetLocX();
	int locY = GetLocY();
	display->DrawRectangle(locX, locY, locX + width, locY + height);
	if (text) display->ShowString(locX, locY, (uint8_t*)text);
	Wedget::Show();
}


/// @brief 
/// @param text 
void TextBox::SetText(char* text)
{
	this->text = text;
}


/// @brief 
/// @param text 
void TextBox::AppendText(char* text)
{
	lock.Lock();

	static Display::FontSize fontSize = Display::Font16;
	static uint32_t xOffset = GetLocX() + 1;
	static uint32_t yOffset = GetLocY() + 1;

	uint32_t limitX = GetLocX() + width;
	uint32_t limitY = GetLocY() + height;

	while ('\0' != *text)
	{
		//New line
		if ((xOffset + (fontSize >> 1) > limitX) || ('\n' == *text))
		{
			xOffset  = GetLocX() + 1;
			yOffset += fontSize;
		}

		//Move up
		if (yOffset + fontSize > limitY)
		{
			uint32_t y0 = (yOffset + fontSize) - limitY;
			for (uint32_t y = GetLocY() + 1 + y0; y < limitY; y++)
			{
				for (uint32_t x = GetLocX() + 1; x < limitX; x++)
				{
					uint32_t color = display->ReadPoint(x, y);
					display->DrawPoint(x, y - y0, color);
				}
			}

			xOffset = GetLocX() + 1;
			yOffset = limitY - fontSize;
			
			for (uint32_t y = yOffset; y < limitY; y++)
			{
				for (uint32_t x = GetLocX() + 1; x < limitX; x++)
				{
					display->DrawPoint(x, y, Display::White);
				}
			}
		}

		//Backspace one character 
		if (*text == '\b') xOffset -= (fontSize >> 1);

		//Normal display
		if ((*text <= '~') && (*text >= ' '))
		{
			display->ShowChar(xOffset, yOffset, *text, fontSize, Display::NotMultiply, Display::Black);

			xOffset += fontSize >> 1;
		}

		text++;
	}
	lock.Unlock();
}
