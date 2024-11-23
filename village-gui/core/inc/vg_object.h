//###########################################################################
// vg_object.h
// Declarations of the functions that manage object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_OBJECT_H__
#define __VG_OBJECT_H__

#include "vg_devices.h"
#include "vg_layer.h"
#include "vg_window.h"
#include "vk_list.h"


/// @brief GraphicsObject
class GraphicsObject
{
private:
	//Members
	GraphicsDevices&   devices;
	List<Wedget*>      wedgets;
	Wedget*            actWedget;
	Layer              layer;
private:
	//Methods
	bool IsActWedgetChange(IndevData input);
	bool IsActWedgetMove(IndevData input);
	List<DrawArea> GetActWedgetOverlapAreas();
	List<DrawArea> CutActWedgetOverlapAreas(List<DrawArea> areas);
	List<DrawArea> InciseActWedgetOverlapAreas(List<DrawArea> areas);
	void RedrawActWedgetArea(List<DrawArea> areas);
	void RedrawActWedgetOverlapAreas();
public:
	//Methods
	GraphicsObject(GraphicsDevices& devices);
	~GraphicsObject();
	void Setup();
	void Execute();
	void Exit();

	//Methods
	Wedget* Create();
	bool Destroy(Wedget* win);
};

#endif //!__VG_GROUP_H__
