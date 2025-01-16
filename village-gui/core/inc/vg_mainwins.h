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
#include "vg_cursor.h"
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
	VgWindow*          selectedWin;
	VgWindow*          cursorWin;
	VgLayer            layer;
	VgInputData        input;
private:
	//Methods
	void UpdataInput();
	void UpdateCursor();
	void UpdateWindow();
	void SelectedWindow();
	bool IsActWindowChange();

	//Common Methods
	VgDrawAreas GetWindowUpperAreas(VgWindow* window);
	VgDrawAreas RedrawFloatWindowAreas(VgDrawAreas areas, VgWindow* window);
	VgDrawAreas RedrawOtherWindowAreas(VgDrawAreas areas, VgWindow* window, VgWindow::Place place);
	void RedrawOtherWindowAreas(VgDrawAreas overlaps, VgWindow* window);
	void RedrawSelfWindowAreas(VgDrawAreas overlaps, VgWindow* window);

	//Update Methods
	void RedrawWindowUpdateOverlapAreas(VgWindow* window);

	//Resize Methods
	void RedrawResizeWindowOverlapAreas(VgWindow* window);
	void DestroyCloseWindow(VgWindow* window);

	//Select Methods
	VgDrawAreas GetSelWindowOverlapAreas(VgWindow* window);
	void RedrawSelWindowOverlapAreas(VgWindow* window);
	void SwapActWindowListNode(VgWindow* window);
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
