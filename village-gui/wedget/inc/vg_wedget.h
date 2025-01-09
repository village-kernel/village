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
class VgWedget
{
protected:
	//Members
	VgDevices* devices;

	//Area members
	VgLayer    layer;
	VgDrawArea layerArea;
	
	//Attribute members
	char* title;
	int   bgColor;
	bool  hidden;
	bool  enable;
	bool  fixed;
	bool  multiply;
	bool  focus;
	bool  floatable;
	bool  update;

	//Binding attribute members
	IData<char*>* bTitle;
	IData<int>*   bBgColor;
	IData<bool>*  bHidden;
	IData<bool>*  bEnable;
	IData<bool>*  bFixed;
	IData<bool>*  bMultiply;
	IData<bool>*  bFocus;
	IData<bool>*  bFloatable;
	IData<bool>*  bUpdata;

	//Binding command members
	ICommand* cmd;

	//Wedget members
	VgList<VgWedget*> wedgets;

	//Members
	VgDrawRect drawRect;
public:
	//Methods
	VgWedget();
	virtual ~VgWedget();

	//Area methods
	virtual void MoveTo(int x, int y);
	virtual void AxisMove(int axisx, int axisy);
	virtual void SetSize(int width, int height);
	virtual bool IsInLayerArea(int x, int y);
	virtual bool IsLayerAreaValid();
	virtual int GetX();
	virtual int GetY();
	virtual int GetWidth();
	virtual int GetHeight();
	virtual VgDrawArea GetLayerArea();
	virtual VgDrawAreas GetFloatAreas();
	virtual VgDrawAreas GetUpdateAreas();
	virtual VgDrawAreas RedrawFloats(VgDrawAreas areas);
	virtual VgDrawAreas RedrawFloatAreas(VgDrawAreas areas);
	virtual VgDrawAreas RedrawFloatAreas(VgWedget* wedget, VgDrawAreas areas);
	virtual VgDrawAreas RedrawWedgets(VgDrawAreas areas);
	virtual VgDrawAreas RedrawWedgetAreas(VgDrawAreas areas);
	virtual VgDrawAreas RedrawWedgetAreas(VgWedget* wedget, VgDrawAreas areas);
	virtual void RedrawMultiplys(VgDrawAreas areas);
	virtual void RedrawMultiplyAreas(VgDrawAreas areas);
	virtual void RedrawMultiplyAreas(VgWedget* wedget, VgDrawAreas areas);
	virtual void RedrawBackgroundAreas(VgDrawAreas areas);
	
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
	virtual void ExecuteCommand(VgInputData input, void* args = NULL);

	//Wedget methods
	virtual void AddWedget(VgWedget* wedget);
private:
	//Methods
	virtual void InitContent(VgDevices* devices) = 0;
	virtual void ExecContent(VgInputData input) = 0;
	virtual void DrawContent(VgDrawArea drawArea) = 0;
public:
	//Methods
	virtual void Initiate(VgDevices* devices);
	virtual void Execute(VgInputData input);
	virtual void Redraw(VgDrawArea drawArea);
	virtual void Redraw(VgDrawAreas drawAreas);
	virtual void Show();
};

#endif //!__VG_WEDGET_H__
