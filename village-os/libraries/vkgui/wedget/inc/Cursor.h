//###########################################################################
// Cursor.h
// Declarations of the functions that manage cursor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_CURSOR_H__
#define __VK_CURSOR_H__

#include "Wedget.h"


/// @brief Cursor
class Cursor : public Wedget
{
private:
	//Members
	int locX;
	int locY;

	//Methods
	void Read(uint32_t x, uint32_t y, uint32_t* data);
	void Draw(uint32_t x, uint32_t y, uint32_t* data);
public:
	//Methods
	Cursor();
	~Cursor();
	
	void InitContent();
	void DrawContent();

	void InputAxis(int axisX, int axisY, int axisZ);
};

#endif //!__VK_CURSOR_H__
