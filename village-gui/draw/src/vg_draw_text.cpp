//###########################################################################
// vg_draw_text.cpp
// Definitions of the functions that manage draw text
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_draw_text.h"
#include "vg_ascii_font.h"


/// @brief Constructor
VgDrawText::VgDrawText()
	:fontSize(VgDrawDefs::_Font16),
	 fontWidth(fontSize >> 1),
	 fontHeight(fontSize),
	 fontColor(VgDrawDefs::_Black),
	 alignment(VgDrawText::_AlignCenter)
{
}


/// @brief Destructor
VgDrawText::~VgDrawText()
{
}


/// @brief Set font size
/// @param font 
void VgDrawText::SetFontSize(int font)
{
	this->fontSize   = font;
	this->fontWidth  = font >> 1;
	this->fontHeight = font;
}


/// @brief Set font color
/// @param color 
void VgDrawText::SetFontColor(int color)
{
	this->fontColor = color;
}


/// @brief Set alignment
/// @param align 
void VgDrawText::SetAlignment(Alignment align)
{
	this->alignment = align;
}


/// @brief Get font index
/// @param chr 
/// @return 
inline int VgDrawText::GetFontIndex(int chr)
{
	return chr - ' ';
}


/// @brief Get font matrix
/// @param index 
/// @param row 
/// @return 
inline int VgDrawText::GetFontMatrix(int index, int row)
{
	int matrix = 0;

	if (VgDrawDefs::_Font16 == fontSize)
	{
		matrix = VgAscii16[index][row];
	}
	else if (VgDrawDefs::_Font24 == fontSize)
	{
		matrix  = (VgAscii24[index][row * 2 + 0] & 0x00ff) << 0;
		matrix += (VgAscii24[index][row * 2 + 1] & 0x00ff) << 8;
	}

	return matrix;
}


/// @brief VgDrawText Initiate
/// @param devices 
void VgDrawText::Initiate(VgDevices* devices)
{
	this->devices = devices;
}


/// @brief VgDrawText Execute
/// @param layerArea 
/// @param drawArea 
/// @param chr 
/// @param color 
void VgDrawText::Execute(VgDrawArea layerArea, VgDrawArea drawArea, char chr)
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


/// @brief VgDrawText Execute
/// @param layerArea 
/// @param drawArea 
/// @param text 
/// @param color 
void VgDrawText::Execute(VgDrawArea layerArea, VgDrawArea drawArea, char* str)
{
	if (NULL == str) return;

	//Update layer area
	if (VgDrawText::_AlignCenter == alignment)
	{
		int halfWidth  = (layerArea.ex - layerArea.sx + 1) >> 1;
		int halfHeight = (layerArea.ey - layerArea.sy + 1) >> 1;
		layerArea.sx = layerArea.sx + halfWidth  - (strlen(str) * fontWidth >> 1);
		layerArea.sy = layerArea.sy + halfHeight - (fontHeight >> 1);
	}

	//Update draw area
	drawArea.sx = math.Max(drawArea.sx, layerArea.sx);
	drawArea.ex = math.Min(drawArea.ex, layerArea.ex);
	drawArea.sy = math.Max(drawArea.sy, layerArea.sy);
	drawArea.ey = math.Min(drawArea.ey, layerArea.ey);

	//Clac string index
	int sidx = (drawArea.sx - layerArea.sx) / fontWidth;
	int eidx = (drawArea.ex - layerArea.sx) / fontWidth;
	int slen = strlen(str); if (eidx >= slen) eidx = slen - 1;
	
	//Offset layer area sx
	layerArea.sx += sidx * fontWidth;

	//Draw string
	for (int idx = sidx; idx <= eidx; idx++)
	{
		Execute(layerArea, drawArea, str[idx]);

		layerArea.sx += fontWidth;
	}
}
