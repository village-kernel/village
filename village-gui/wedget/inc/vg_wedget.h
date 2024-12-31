//###########################################################################
// vg_wedget.h
// Declarations of the functions that manage wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_WEDGET_H__
#define __VG_WEDGET_H__

#include "vg_list.h"
#include "vg_layer.h"
#include "vg_devices.h"
#include "vg_input_cmd.h"
#include "vg_draw_rect.h"


/// @brief Wedget
class Wedget
{
protected:
	//Members
	VgDevices* devices;

	//Area members
	DrawArea layerArea;
	
	//Attribute members
	char* title;
	int bgColor;
	bool hidden;
	bool enable;
	bool fixed;
	bool update;

	//Binding members
	ICommand* cmd;

	//Wedget members
	VgList<Wedget*> wedgets;

	//Members
	Layer    layer;
	DrawRect rect;
public:
	//Methods
	Wedget();
	virtual ~Wedget();

	//Area methods
	virtual void MoveTo(int x, int y);
	virtual void AxisMove(int axisx, int axisy);
	virtual void SetSize(int width, int height);
	virtual bool IsInArea(int x, int y);
	virtual int GetX();
	virtual int GetY();
	virtual int GetWidth();
	virtual int GetHeight();
	virtual DrawArea GetLayerArea();
	virtual DrawAreas GetUpdateAreas();
	virtual DrawAreas RedrawWedgetAreas(Wedget* wedget, DrawAreas areas);
	
	//Attribute methods
	virtual void SetTitle(char* title);
	virtual char* GetTitle();

	virtual void SetBgColor(int color);
	virtual int GetBgColor();

	virtual void SetHidden(bool hidden);
	virtual bool IsHidden();
	
	virtual void SetEnable(bool enable);
	virtual bool IsEnable();

	virtual void SetFixed(bool fixed);
	virtual bool IsFixed();

	virtual void UpdateRequest(bool request);
	virtual bool IsUpdateRequest();

	//Binding methods
	virtual void BindingCommand(ICommand* cmd);

	//Wedget methods
	virtual void AddWedget(Wedget* wedget);

	//Methods
	virtual void Initiate(VgDevices* devices);
	virtual void Execute(IndevData input);
	virtual void Redraw(DrawArea drawArea);
	virtual void Redraw(DrawAreas drawAreas);
	virtual void Show();
};

#endif //!__VG_WEDGET_H__
