//###########################################################################
// vg_object.h
// Declarations of the functions that manage object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_OBJECT_H__
#define __VG_OBJECT_H__

#include "vg_data.h"
#include "vg_layer.h"
#include "vg_window.h"
#include "vk_list.h"


/// @brief GraphicsObject
class GraphicsObject
{
private:
	//Members
	SystemInfo&    sysinfo;
	List<Window*>  mainwins;
	Window*        activedwin;
	Layer          layer;
private:
	//Methods
	bool IsActivedWinChange(IndevData input);
	bool IsActivedWinMove(IndevData input);
	void RedrawActivedWinOverlapAreas();
	List<DrawArea> GetActivedWinOverlapAreas();
	List<DrawArea> CutActivedWinOverlapAreas(List<DrawArea> areas);
	List<DrawArea> InciseActivedWinOverlapAreas(List<DrawArea> areas);
public:
	//Methods
	GraphicsObject(SystemInfo& sysinfo);
	~GraphicsObject();
	void Setup();
	void Execute();
	void Exit();

	//Methods
	Window* Create();
	bool Destroy(Window* win);
};

#endif //!__VG_GROUP_H__
