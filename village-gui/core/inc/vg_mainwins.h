//###########################################################################
// vg_mainwins.h
// Declarations of the functions that manage mainwins
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_MAINWINS_H__
#define __VG_MAINWINS_H__

#include "vg_devices.h"
#include "vg_layer.h"
#include "vg_window.h"
#include "vg_list.h"


/// @brief VgMainWins
class VgMainWins
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
private:
	//Methods
	void UpdataInput();
	void UpdateCursor();
	void ExecuteWindow();
	void UpdateWindow();
	bool IsActWindowResize(ResizeMethod& resizeMethod);
	bool IsActWindowSelect();
	Window* SelectActWindow();
	ResizeMethod CheckResizeMethod(Point input, Point axis);
	
	//Common Methods
	DrawAreas GetWindowUpperAreas(Window* window);
	DrawAreas RedrawFloatWindowAreas(DrawAreas areas, Window* window);
	DrawAreas RedrawOtherWindowAreas(DrawAreas areas, Window* window, Window::Place place);
	void RedrawOtherWindowAreas(DrawAreas areas, Window* window);
	void RedrawSelfWindowAreas(Window* window);
	void RedrawWindowUpdateAreas(Window* window);

	//Resize Methods
	DrawAreas GetResizeWindowOverlapAreas(Window* window, ResizeMethod resizeMethod);
	void RedrawResizeWindowOverlapAreas(Window* window, ResizeMethod resizeMethod);
	void ResizeWindowExecute(Window* window, ResizeMethod resizeMethod);
	void DestroyCloseWindow(Window* window, ResizeMethod resizeMethod);

	//Focus Methods
	DrawAreas GetSelWindowOverlapAreas(Window* window);
	void RedrawSelWindowOverlapAreas(Window* window);
	void SwapActWindowListNode(Window* window);
	void AlwaysFocusWindowExecute(Window* window);
public:
	//Methods
	VgMainWins(VgDevices& devices);
	~VgMainWins();
	void Setup();
	void Execute();
	void Exit();

	//Methods
	Window* Create();
	bool Destroy(Window* window);
	bool IsExist(Window* window);
};

#endif //!__VG_MAINWINS_H__