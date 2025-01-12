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
	VgDevices&         devices;
	VgList<VgWindow*>  windows;
	VgWindow*          defWindow;
	VgWindow*          actWindow;
	VgWindow*          curWindow;
	VgLayer            layer;
	VgInputData        input;
	VgInputData        axis;
private:
	//Methods
	void UpdataInput();
	void UpdateCursor();
	void ExecuteWindow();
	void UpdateWindow();
	bool IsActWindowResize(ResizeMethod& resizeMethod);
	bool IsActWindowSelect();
	VgWindow* SelectActWindow();
	ResizeMethod CheckResizeMethod(VgPoint input, VgPoint axis);

	//Common Methods
	VgDrawAreas GetWindowUpperAreas(VgWindow* window);
	VgDrawAreas RedrawFloatWindowAreas(VgDrawAreas areas, VgWindow* window);
	VgDrawAreas RedrawOtherWindowAreas(VgDrawAreas areas, VgWindow* window, VgWindow::Place place);
	void RedrawOtherWindowAreas(VgDrawAreas overlaps, VgWindow* window);
	void RedrawSelfWindowAreas(VgDrawAreas overlaps, VgWindow* window);

	//Resize Methods
	VgDrawAreas GetResizeOtherWindowAreas(VgWindow* window, ResizeMethod resizeMethod);
	void RedrawResizeWindowOverlapAreas(VgWindow* window, ResizeMethod resizeMethod);
	void ResizeWindowExecute(VgWindow* window, ResizeMethod resizeMethod);
	void DestroyCloseWindow(VgWindow* window, ResizeMethod resizeMethod);

	//Update Methods
	VgDrawAreas GetOtherWindowUpdateAreas(VgWindow* window);
	void RedrawWindowUpdateOverlapAreas(VgWindow* window);

	//Focus Methods
	VgDrawAreas GetSelWindowOverlapAreas(VgWindow* window);
	void RedrawSelWindowOverlapAreas(VgWindow* window);
	void SwapActWindowListNode(VgWindow* window);
	void AlwaysFocusWindowExecute(VgWindow* window);
public:
	//Methods
	VgMainWins(VgDevices& devices);
	~VgMainWins();
	void Setup();
	void Execute();
	void Exit();

	//Methods
	VgWindow* Create();
	bool Destroy(VgWindow* window);
	bool IsExist(VgWindow* window);
};

#endif //!__VG_MAINWINS_H__
