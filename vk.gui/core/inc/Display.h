//###########################################################################
// Dispaly.h
// Declarations of the functions that about display algorithm
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "ASCIIFont.h"
#include "LcdDriver.h"
#include "Mutex.h"

///Display
class Display
{
public:
	//Enums
	enum Color8
	{
		White      = 0x1F,
		Black      = 0x10,	  
		Blue       = 0x1F,  
		Bred       = 0X1F,
		Gred       = 0XE0,
		Gblue      = 0XFF,
		Red        = 0x00,
		Magenta    = 0x1F,
		Green      = 0xE0,
		Cyan       = 0xFF,
		Yellow     = 0xE0,
		Brown      = 0X40,
		Brred      = 0X07,
		Gray       = 0X30,
		Darkblue   = 0XCF,
		Lightblue  = 0X7C, 
		Grayblue   = 0X58,
		Lightgreen = 0X1F,
		Lgray      = 0X18,
		Lgrayblue  = 0X51,
		Lbblue     = 0X12,
	};

	//enum Color16
	//{
	//	White      = 0xFFFF,
	//	Black      = 0x0000,	  
	//	Blue       = 0x001F,  
	//	Bred       = 0XF81F,
	//	Gred       = 0XFFE0,
	//	Gblue      = 0X07FF,
	//	Red        = 0xF800,
	//	Magenta    = 0xF81F,
	//	Green      = 0x07E0,
	//	Cyan       = 0x7FFF,
	//	Yellow     = 0xFFE0,
	//	Brown      = 0XBC40,
	//	Brred      = 0XFC07,
	//	Gray       = 0X8430,
	//	Darkblue   = 0X01CF,
	//	Lightblue  = 0X7D7C, 
	//	Grayblue   = 0X5458,
	//	Lightgreen = 0X841F,
	//	Lgray      = 0XC618,
	//	Lgrayblue  = 0XA651,
	//	Lbblue     = 0X2B12,
	//};

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
	static const uint16_t buf_size = 100;
	static const uint16_t defStrokeColor = Color8::Black;
	static const uint16_t defBackgroundColor = Color8::White;
	//static const uint16_t defStrokeColor = Color16::Black;
	//static const uint16_t defBackgroundColor = Color16::White;

	//Members
	LcdDriver* lcd;
	Mutex      lock;
	char       data[buf_size];
public:
	//Methods
	Display();
	~Display();
	void Initialize(LcdDriver* lcd);
	void DrawPoint(uint16_t x, uint16_t y, uint16_t color = defStrokeColor);
	uint16_t ReadPoint(uint16_t x, uint16_t y);
	void Clear(uint16_t color = defBackgroundColor);
	void DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color = defStrokeColor);
	void DrawRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color = defStrokeColor);
	void DrawCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color = defStrokeColor);
	void ShowChar(uint16_t x, uint16_t y, uint8_t charVal, FontSize fontSize = Font16, DisplayMode mode = Multiply, uint16_t color = defStrokeColor);
	void ShowString(uint16_t x, uint16_t y, uint8_t* str, FontSize fontSize = Font16, DisplayMode mode = Multiply, uint16_t color = defStrokeColor);
	void ShowString(uint8_t* str, FontSize fontSize = Font16, DisplayMode mode = Multiply, uint16_t color = defStrokeColor);
	void ShowPicture(uint8_t *picture, uint16_t x = 0, uint16_t y = 0, uint16_t width = 0, uint16_t height = 0);
	
	//Methods
	void Printf(const char* format, ...);
};

#endif //!__DISPLAY_H__
