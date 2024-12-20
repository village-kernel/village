//###########################################################################
// vg_group.h
// Declarations of the functions that manage window group
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_GROUP_H__
#define __VG_GROUP_H__

#include "vg_devices.h"
#include "vg_layer.h"
#include "vg_window.h"
#include "vg_list.h"


/// @brief VgGroup
class VgGroup
{
private:
	//Enumerations
	enum ResizeMethod
	{
		_None = 0,
		_Move,
		_Adjust,
		_Maximize,
		_Minimize,
		_Close,
	};

	//Members
	VgDevices&       devices;
	VgList<Window*>  windows;
	Window*          defWindow;
	Window*          actWindow;
	Window*          curWindow;
	Layer            layer;
	IndevData        input;
	IndevData        axis;
	ResizeMethod     resizeMethod;
private:
	//Methods
	void UpdataInput();
	bool IsCurWindowMove();
	bool IsActWindowResize();
	bool IsActWindowSelect();
	
	//Common Methods
	DrawAreas GetWindowUpperAreas(Window* window);
	DrawAreas RedrawOtherWindowAreas(DrawAreas areas, Window* window, Window::Place place);
	void RedrawOtherWindowAreas(DrawAreas areas, Window* window);
	void RedrawSelfWindowAreas(Window* window);

	//Resize Methods
	DrawAreas GetResizeWindowOverlapAreas(Window* window);
	void RedrawResizeWindowOverlapAreas(Window* window);
	void ResizeWindowExecute(Window* window);
	void DestroyCloseWindow(Window* window);

	//Focus Methods
	DrawAreas GetSelWindowOverlapAreas(Window* window);
	void RedrawSelWindowOverlapAreas(Window* window);
	void SwapActWindowListNode(Window* window);
	void AlwaysFocusWindowExecute(Window* window);
public:
	//Methods
	VgGroup(VgDevices& devices);
	~VgGroup();
	void Setup();
	void Execute();
	void Exit();

	//Methods
	Window* Create();
	bool Destroy(Window* win);
};

#endif //!__VG_GROUP_H__
