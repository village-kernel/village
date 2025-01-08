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
#include "vg_input_data.h"
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
	int  bgColor;
	bool hidden;
	bool enable;
	bool fixed;
	bool multiply;
	bool focus;
	bool floatable;
	bool update;
	IData<char*>* bTitle;
	IData<int>*  bBgColor;
	IData<bool>* bHidden;
	IData<bool>* bEnable;
	IData<bool>* bFixed;
	IData<bool>* bMultiply;
	IData<bool>* bFocus;
	IData<bool>* bFloatable;
	IData<bool>* bUpdata;

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
	virtual bool IsAreaValid();
	virtual int GetX();
	virtual int GetY();
	virtual int GetWidth();
	virtual int GetHeight();
	virtual DrawArea GetLayerArea();
	virtual DrawAreas GetFloatAreas();
	virtual DrawAreas GetUpdateAreas();
	virtual DrawAreas RedrawFloats(DrawAreas areas);
	virtual DrawAreas RedrawFloatAreas(DrawAreas areas);
	virtual DrawAreas RedrawFloatAreas(Wedget* wedget, DrawAreas areas);
	virtual DrawAreas RedrawWedgets(DrawAreas areas);
	virtual DrawAreas RedrawWedgetAreas(DrawAreas areas);
	virtual DrawAreas RedrawWedgetAreas(Wedget* wedget, DrawAreas areas);
	virtual void RedrawMultiplys(DrawAreas areas);
	virtual void RedrawMultiplyAreas(DrawAreas areas);
	virtual void RedrawMultiplyAreas(Wedget* wedget, DrawAreas areas);
	
	//Attribute methods
	virtual void BindingTitle(IData<char*>* title);
	virtual void SetTitle(char* title);
	virtual char* GetTitle();

	virtual void BindingBgColor(IData<int>* color);
	virtual void SetBgColor(int color);
	virtual int GetBgColor();

	virtual void BindingHidden(IData<bool>* hidden);
	virtual void SetHidden(bool hidden);
	virtual bool IsHidden();
	
	virtual void BindingEnable(IData<bool>* enable);
	virtual void SetEnable(bool enable);
	virtual bool IsEnable();

	virtual void BindingFixed(IData<bool>* fixed);
	virtual void SetFixed(bool fixed);
	virtual bool IsFixed();

	virtual void BindingMultiply(IData<bool>* multiply);
	virtual void SetMultiply(bool multiply);
	virtual bool IsMultiply();

	virtual void BindingFocus(IData<bool>* focus);
	virtual void SetFocus(bool focus);
	virtual bool IsFocus();

	virtual void BindingFloatable(IData<bool>* floatable);
	virtual void SetFloatable(bool floatable);
	virtual bool IsFloatable();

	virtual void BindingUpdateRequest(IData<bool>* request);
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
