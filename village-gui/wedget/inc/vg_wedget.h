//###########################################################################
// vg_wedget.h
// Declarations of the functions that manage wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_WEDGET_H__
#define __VG_WEDGET_H__

#include "vk_list.h"
#include "vg_data.h"


/// @brief Wedget
class Wedget
{
protected:
	//Members
	List<Wedget*> wedgets;
public:
	//Members
	DrawArea area;
public:
	//Content methods
	virtual void InitContent() = 0;
	virtual void DrawContent() = 0;
public:
	//Methods
	Wedget();
	virtual ~Wedget();
	
	//Wedgets methods
	void SetSize(int x, int y, int width, int height);
	bool IsCanSelecte(int x, int y);
	void AddWedget(Wedget* wedget);
	void Show();
};

#endif //!__VG_WEDGET_H__
