//###########################################################################
// Dispaly.h
// Declarations of the functions that about display algorithm
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "ASCIIFont.h"
#include "Driver.h"
#include "Mutex.h"

///Display
class Display
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
		Multiply = 0,
		NotMultiply = 1,
	};
private:
	//Static constants
	static const uint32_t buf_size = 100;
	static const uint32_t defStrokeColor = Color16::Black;
	static const uint32_t defBackgroundColor = Color16::White;

	//Members
	FBDriver*  fbdev;
	Mutex      lock;
	uint32_t   limitX;
	uint32_t   limitY;
	char       data[buf_size];
public:
	//Methods
	Display();
	~Display();
	void Initialize(FBDriver* fbdev);
	
	void DrawPoint(uint32_t x, uint32_t y, uint32_t color = defStrokeColor);
	uint32_t ReadPoint(uint32_t x, uint32_t y);
	uint32_t ReadDrawPoint(uint32_t x, uint32_t y, uint32_t color = defStrokeColor);
	void Clear(uint32_t color = defBackgroundColor);
	
	void DrawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color = defStrokeColor);
	void DrawRectangle(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color = defStrokeColor);
	
	void DrawCircle(uint32_t x, uint32_t y, uint32_t r, uint32_t* colors = NULL);
	void ReadCircle(uint32_t x, uint32_t y, uint32_t r, uint32_t* colors = NULL);

	void ShowChar(uint32_t x, uint32_t y, uint8_t charVal, FontSize fontSize = Font16, DisplayMode mode = Multiply, uint32_t color = defStrokeColor);
	void ShowString(uint32_t x, uint32_t y, uint8_t* str, FontSize fontSize = Font16, DisplayMode mode = Multiply, uint32_t color = defStrokeColor);
	void ShowString(uint8_t* str, FontSize fontSize = Font16, DisplayMode mode = Multiply, uint32_t color = defStrokeColor);
	
	void ShowArea(uint32_t* area, uint32_t x = 0, uint32_t y = 0, uint32_t width = 0, uint32_t height = 0);
	
	void Printf(const char* format, ...);
};

#endif //!__DISPLAY_H__
