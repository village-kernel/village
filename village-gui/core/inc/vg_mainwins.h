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
	//Members
	VgDevices&         devices;
	VgList<VgWindow*>  windows;
	VgWindow*          defaultWin;
	VgWindow*          activedWin;
	VgWindow*          cursorWin;
	VgLayer            layer;
	VgInputData        input;
private:
	//Methods
	void UpdataInput();

	//Common Methods
	VgDrawAreas GetWindowUpperAreas(VgWindow* window);
	VgDrawAreas RedrawFloatWindowAreas(VgDrawAreas areas, VgWindow* window);
	VgDrawAreas RedrawOtherWindowAreas(VgDrawAreas areas, VgWindow* window, VgWindow::Place place);
	void RedrawOtherWindowAreas(VgDrawAreas overlaps, VgWindow* window);
	void RedrawSelfWindowAreas(VgDrawAreas overlaps, VgWindow* window);

	//Cursor Methods
	void UpdateCursor();
	void RedrawCursorWindowArea(VgWindow* window);

	//Resize Methods
	bool IsActWindowResize();
	void RedrawResizeWindowOverlapAreas(VgWindow* window);
	void DestroyCloseWindow(VgWindow* window);

	//Select Methods
	bool IsActWindowSelect();
	VgWindow* SelectActWindow();
	VgDrawAreas GetSelWindowOverlapAreas(VgWindow* window);
	void RedrawSelWindowOverlapAreas(VgWindow* window);
	void SwapActWindowListNode(VgWindow* window);
	void AlwaysFocusWindowExecute(VgWindow* window);

	//Update Methods
	void ExecuteWindow();
	void UpdateWindow();
	void RedrawWindowUpdateOverlapAreas(VgWindow* window);
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
