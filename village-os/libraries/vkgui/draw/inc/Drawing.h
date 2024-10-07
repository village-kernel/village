//###########################################################################
// Drawing.h
// Declarations of the functions that about display algorithm
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_H__
#define __DRAWING_H__

#include "ASCIIFont.h"
#include "Driver.h"
#include "Mutex.h"


/// @brief Drawing
class Drawing
{
public:
	//Enums
	enum Color16
	{
		White      = 0xFFFF,
		Black      = 0x0000,
		Blue       = 0x001F,
		Bred       = 0XF81F,
		Gred       = 0XFFE0,
		Gblue      = 0X07FF,
		Red        = 0xF800,
		Magenta    = 0xF81F,
		Green      = 0x07E0,
		Cyan       = 0x7FFF,
		Yellow     = 0xFFE0,
		Brown      = 0XBC40,
		Brred      = 0XFC07,
		Gray       = 0X8430,
		Darkblue   = 0X01CF,
		Lightblue  = 0X7D7C,
		Grayblue   = 0X5458,
		Lightgreen = 0X841F,
		Lgray      = 0XC618,
		Lgrayblue  = 0XA651,
		Lbblue     = 0X2B12,
	};

	enum FontSize
	{
		Font16 = 16,
		Font24 = 24,
	};

	enum DisplayMode
	{
		Multiply    = 0,
		NotMultiply = 1,
	};
private:
	//Static constants
	static const int defStrokeColor = Color16::Black;
	static const int defBackgroundColor = Color16::White;

	//Members
	FBDriver*  fbdev;
	Mutex      lock;
	int        limitX;
	int        limitY;
public:
	//Methods
	Drawing();
	~Drawing();
	void Setup(FBDriver* fbdev);
	void Exit();

	void Clear(int color = defBackgroundColor);
	
	void DrawingPoint(int x, int y, int color = defStrokeColor);
	int ReadingPoint(int x, int y);
	int ReadDrawPoint(int x, int y, int color = defStrokeColor);
	
	void DrawingLine(int x0, int y0, int x1, int y1, int color = defStrokeColor);
	
	void DrawingRectangle(int x0, int y0, int x1, int y1, int color = defStrokeColor);
	
	void DrawingCircle(int x, int y, int r, int* colors = NULL);
	void ReadingCircle(int x, int y, int r, int* colors = NULL);

	void DrawingChar(int x, int y, char charVal, FontSize fontSize = Font16, DisplayMode mode = Multiply, int color = defStrokeColor);
	
	void DrawingString(int x, int y, char* str, FontSize fontSize = Font16, DisplayMode mode = Multiply, int color = defStrokeColor);
	void DrawingString(char* str, FontSize fontSize = Font16, DisplayMode mode = Multiply, int color = defStrokeColor);
	
	void DrawingArea(int* area, int x = 0, int y = 0, int width = 0, int height = 0);
};

#endif //!__DRAWING_H__
