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
	//Members
	VgDevices&       devices;
	VgList<Window*>  windows;
	Window*          defWindow;
	Window*          actWindow;
	Window*          curWindow;
	Layer            layer;
	IndevData        input;
	IndevData        axis;
private:
	//Methods
	void UpdataInput();
	bool IsCurWindowMove();
	bool IsActWindowMove();
	bool IsActWindowResize();
	bool IsActWindowSelect();
	
	//Common Methods
	DrawAreas GetWindowUpperAreas(Window* window);
	DrawAreas RedrawOtherWindowAreas(DrawAreas areas, Window* window, Window::Place place);
	void RedrawOtherWindowAreas(DrawAreas areas, Window* window);
	void RedrawSelfWindowAreas(Window* window);

	//Move Methods
	DrawAreas GetMoveWindowOverlapAreas(Window* window);
	void RedrawMoveWindowOverlapAreas(Window* window);

	//Resize Methods
	DrawAreas GetResizeWindowOverlapAreas(Window* window);
	void RedrawResizeWindowOverlapAreas(Window* window);

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
