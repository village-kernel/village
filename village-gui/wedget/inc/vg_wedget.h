//###########################################################################
// vg_wedget.h
// Declarations of the functions that manage wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_WEDGET_H__
#define __VG_WEDGET_H__

#include "vk_list.h"
#include "vg_layer.h"
#include "vg_devices.h"
#include "vg_input_cmd.h"
#include "vg_draw_rect.h"


/// @brief Wedget
class Wedget
{
protected:
	//Members
	GraphicsDevices* devices;

	//Area members
	DrawArea layerArea;
	
	//Attribute members
	char* title;
	int bgColor;
	bool hidden;
	bool enable;
	bool fixed;
	bool bottom;
	bool top;

	//Binding members
	ICommand* cmd;

	//Wedget members
	List<Wedget*> wedgets;

	//Members
	Layer    layer;
	DrawRect rect;
public:
	//Methods
	Wedget();
	virtual ~Wedget();

	//Area methods
	void SetSize(int x, int y, int width, int height);
	void Move(int axisx, int axisy);
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	DrawArea GetArea();

	//Attribute methods
	void SetTitle(char* title);
	char* GetTitle();

	void SetBgColor(int color);
	int GetBgColor();

	void SetHidden(bool hidden);
	bool IsHidden();
	
	void SetEnable(bool enable);
	bool IsEnable();

	void SetFixed(bool fixed);
	bool IsFixed();

	void SetOnBottom(bool bottom);
	bool IsOnBottom();

	void SetOnTop(bool top);
	bool IsOnTop();

	//Binding methods
	void BindingCommand(ICommand* cmd);

	//Wedget methods
	void AddWedget(Wedget* wedget);
	void ExecuteWedgets(IndevData input);
	void DrawWedgets(DrawArea drawArea);
	void ShowWedgets();

	//Methods
	virtual void Initiate(GraphicsDevices* devices);
	virtual void Execute(IndevData input);
	virtual void Redraw(DrawArea drawArea);
	virtual void Redraw(List<DrawArea> drawAreas);
	virtual void Show();
};

#endif //!__VG_WEDGET_H__
