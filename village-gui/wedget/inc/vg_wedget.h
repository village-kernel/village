//###########################################################################
// vg_wedget.h
// Declarations of the functions that manage wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_WEDGET_H__
#define __VG_WEDGET_H__

#include "vk_list.h"
#include "vg_devices.h"
#include "vg_input_cmd.h"
#include "vg_draw_rect.h"
#include "vg_draw_mask.h"


/// @brief Wedget
class Wedget
{
protected:
	//Members
	GraphicsDevices*  devices;
	DrawArea          layerArea;
	List<Wedget*>     wedgets;
	ICommand*         cmd;

	//Members
	DrawRect          rect;
	DrawMask          mask;
public:
	//Methods
	Wedget();
	virtual ~Wedget();

	//Area methods
	void SetSize(int x, int y, int width, int height);
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	DrawArea GetArea();

	//Wedget methods
	void AddWedget(Wedget* wedget);
	void ShowWedgets();

	//Binding methods
	void SetCommand(ICommand* cmd);

	//Methods
	virtual void Initiate(GraphicsDevices* devices);
	virtual void Execute(IndevData input);
	virtual void Drawing(DrawArea drawArea);
	virtual void Show();
};

#endif //!__VG_WEDGET_H__
