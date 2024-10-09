//###########################################################################
// Wedget.h
// Declarations of the functions that manage wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_WEDGET_H__
#define __VK_WEDGET_H__

#include "Drawing.h"
#include "Indev.h"
#include "List.h"


/// @brief Wedget
class Wedget
{
protected:
	//Members
	int x;
	int y;
	int xoff;
	int yoff;
	int width;
	int height;
	bool isChange;
protected:
	//Members
	Indev*   indev;
	Drawing* drawing;
	
	//Members
	List<Wedget*> wedgets;
public:
	//Wedget methods
	virtual int GetLocX();
	virtual int GetLocY();
	virtual int GetWidth();
	virtual int GetHeight();
public:
	//Methods
	Wedget();
	virtual ~Wedget();

	//Wedget methods
	virtual void SetIndev(Indev* indev);
	virtual void SetDrawing(Drawing* drawing);
	virtual void SetSize(int x, int y, int width, int height);
	virtual void SetOffset(int xoff, int yoff);

	//Content methods
	virtual void InitContent();
	virtual void DrawContent();
	virtual void DrawBorder();

	//Wedgets methods
	virtual void AddWedget(Wedget* wedget);
	virtual void Showing();
	virtual void Refresh();

	//Input methods
	virtual void InputData(char* data, int size);
	virtual void InputAxis(int axisX, int axisY, int axisZ);
};

#endif //!__VK_WEDGET_H__
