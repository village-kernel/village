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
	int GetLocX();
	int GetLocY();
	int GetWidth();
	int GetHeight();
public:
	//Wedget methods
	virtual void SetDrawing(Drawing* drawing);
	virtual void SetSize(int x, int y, int width, int height);
	virtual void SetOffset(int xoff, int yoff);

	//Content methods
	virtual void InitContent();
	virtual void DrawContent();
	virtual void DrawBorder();
public:
	//Input methods
	void SetIndev(Indev* indev);
	void InputData(char* data, int size);
	void InputAxis(int axisX, int axisY, int axisZ);
public:
	//Methods
	Wedget();
	virtual ~Wedget();

	//Wedgets methods
	void AddWedget(Wedget* wedget);
	void Showing();
	void Refresh();
};

#endif //!__VK_WEDGET_H__
