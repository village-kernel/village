//###########################################################################
// vg_draw_label.cpp
// Definitions of the functions that manage draw label
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_draw_label.h"
#include "vg_ascii_font.h"


/// @brief Initiate
/// @param devices 
void DrawLabel::Initiate(GraphicsDevices* devices)
{
	this->devices = devices;
}


/// @brief Draw arc
/// @param layerArea 
/// @param drawArea 
/// @param color 
void DrawLabel::Execute(DrawArea layerArea, DrawArea drawArea, int color)
{

}



///// @brief draw char set
///// @param x 
///// @param y 
///// @param chr 
///// @param font 
///// @param mode 
///// @param color 
//void DrawChar::Execute(int x, int y, char chr, int font, int mode, int color)
//{
//	//const uint16_t PointMask = 0x0001;

//	//uint16_t charLine = 0;
//	//uint16_t charIndex = chr - ' ';
//	//uint8_t rowSize = font;
//	//uint8_t colSize = font >> 1;

//	//for (uint8_t row = 0; row < rowSize; row++)
//	//{
//	//	if (DrawDefs::Font16 == font)
//	//	{
//	//		charLine = ASCII_16[charIndex][row];
//	//	}
//	//	else
//	//	{
//	//		charLine  = (ASCII_24[charIndex][row * 2 + 0] & 0x00ff) << 0;
//	//		charLine += (ASCII_24[charIndex][row * 2 + 1] & 0x00ff) << 8;
//	//	}
			
//	//	for (uint8_t col = 0; col < colSize; col++)
//	//	{
//	//		if (charLine & PointMask)
//	//		{
//	//			draw->point.Set(x + col, y + row, color);
//	//		}
//	//		else if (DrawDefs::NotMultiply == mode)
//	//		{ 
//	//			draw->point.Set(x + col, y + row, DrawDefs::defBgColor);
//	//		}

//	//		charLine >>= 1;
				
//	//		if ((x + col) > limitX) return;
//	//	}

//	//	if ((y + row) > limitY) return;
//	//}
//}


/// @brief Draw string set
/// @param x 
/// @param y 
/// @param str 
/// @param font 
/// @param mode 
/// @param color 
//void DrawLabel::Execute(int x, int y, char* str, int font, int mode, int color)
//{
	//int xOffset = x;
	//int yOffset = y;

	//if (NULL != str)
	//{
	//	while ((*str <= '~') && (*str >= ' '))
	//	{
	//		draw->chr.Set(xOffset, yOffset, *str, font, mode, color);

	//		xOffset += font >> 1;

	//		if (xOffset > limitX)
	//		{
	//			xOffset = 0;
	//			yOffset += font;
	//		}

	//		str++;
	//	}
	//}
//}
