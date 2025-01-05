//###########################################################################
// vg_draw_text.cpp
// Definitions of the functions that manage draw text
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_draw_text.h"
#include "vg_ascii_font.h"


/// @brief Constructor
DrawText::DrawText()
	:fontSize(DrawDefs::_Font16),
	 fontWidth(fontSize >> 1),
	 fontHeight(fontSize),
	 fontColor(DrawDefs::_Black)
{
}


/// @brief Destructor
DrawText::~DrawText()
{
}


/// @brief Set font size
/// @param font 
void DrawText::SetFontSize(int font)
{
	this->fontSize   = font;
	this->fontWidth  = font >> 1;
	this->fontHeight = font;
}


/// @brief Set font color
/// @param color 
void DrawText::SetFontColor(int color)
{
	this->fontColor = color;
}


/// @brief Get font index
/// @param chr 
/// @return 
inline int DrawText::GetFontIndex(int chr)
{
	return chr - ' ';
}


/// @brief Get font matrix
/// @param index 
/// @param row 
/// @return 
inline int DrawText::GetFontMatrix(int index, int row)
{
	int matrix = 0;

	if (DrawDefs::_Font16 == fontSize)
	{
		matrix = ASCII_16[index][row];
	}
	else if (DrawDefs::_Font24 == fontSize)
	{
		matrix  = (ASCII_24[index][row * 2 + 0] & 0x00ff) << 0;
		matrix += (ASCII_24[index][row * 2 + 1] & 0x00ff) << 8;
	}

	return matrix;
}


/// @brief DrawText Initiate
/// @param devices 
void DrawText::Initiate(VgDevices* devices)
{
	this->devices = devices;
}


/// @brief DrawText Execute
/// @param layerArea 
/// @param drawArea 
/// @param chr 
/// @param color 
void DrawText::Execute(DrawArea layerArea, DrawArea drawArea, char chr)
{
	int maxX = devices->lcddev->GetWidth() - 1;
	int maxY = devices->lcddev->GetHeight() - 1;
	int ecol = layerArea.sx + fontWidth - 1;
	int erow = layerArea.sy + fontHeight - 1;
	int sx = math.Sat(               math.Max(drawArea.sx, layerArea.sx) , 0, maxX);
	int ex = math.Sat(math.Min(ecol, math.Min(drawArea.ex, layerArea.ex)), 0, maxX);
	int sy = math.Sat(               math.Max(drawArea.sy, layerArea.sy) , 0, maxY);
	int ey = math.Sat(math.Min(erow, math.Min(drawArea.ey, layerArea.ey)), 0, maxY);

	int fontIdx = GetFontIndex(chr);

	for (int y = sy; y <= ey; y++)
	{
		int matrixIdx = y - layerArea.sy;

		int matrix = GetFontMatrix(fontIdx, matrixIdx);
		
		for (int x = sx; x <= ex; x++)
		{
			int matrixPos = x - layerArea.sx;

			if (matrix & (1 << matrixPos))
			{
				devices->lcddev->Point(x, y, fontColor);
			}
		}
	}
}


/// @brief DrawText Execute
/// @param layerArea 
/// @param drawArea 
/// @param text 
/// @param color 
void DrawText::Execute(DrawArea layerArea, DrawArea drawArea, char* str)
{
	if (NULL == str) return;

	int sidx = (drawArea.sx - layerArea.sx) / fontWidth;
	int eidx = (drawArea.ex - layerArea.sx) / fontWidth;
	int slen = strlen(str); if (eidx >= slen) eidx = slen - 1;
	
	layerArea.sx += sidx * fontWidth;

	for (int idx = sidx; idx <= eidx; idx++)
	{
		Execute(layerArea, drawArea, str[idx]);

		layerArea.sx += fontWidth;
	}
}
